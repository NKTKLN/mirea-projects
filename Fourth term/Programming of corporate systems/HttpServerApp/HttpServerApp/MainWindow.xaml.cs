using System.IO;
using System.Net;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;
using System.Text.Json;
using LiveCharts.Wpf;
using LiveCharts;

namespace HttpServerApp;

/// <summary>
/// Interaction logic for MainWindow.xaml
/// </summary>
public partial class MainWindow : Window
{
    private HttpListener _listener;
    private bool _isRunning;
    private int _getRequestsCount = 0;
    private int _postRequestsCount = 0;
    private readonly List<string> _logs = new();
    private readonly object _lock = new();

    public SeriesCollection ChartData { get; set; }
    public List<string> TimeLabels { get; set; }
    private Timer _statsTimer;

    private string _logFilterMethod = "All"; // Все, GET, POST
    private string _logFilterStatus = "All"; // Все, Success, Error
    private string _graphType = "RealTime"; // RealTime, Minute, Hour

    private Timer _minuteResetTimer;
    private Timer _hourResetTimer;
    private readonly List<(string Time, int GetRequests, int PostRequests)> _minuteAggregatedRequests = new();
    private readonly List<(string Time, int GetRequests, int PostRequests)> _hourAggregatedRequests = new();
    private int _currentMinuteGetRequests = 0;
    private int _currentMinutePostRequests = 0;
    private int _currentHourGetRequests = 0;
    private int _currentHourPostRequests = 0;
    public MainWindow()
    {
        InitializeComponent();
        DataContext = this;
        ChartData = new SeriesCollection
        {
            new LineSeries { Title = "GET Запросы", Values = new ChartValues<int>() },
            new LineSeries { Title = "POST Запросы", Values = new ChartValues<int>() }
        };
        TimeLabels = new List<string>();
        _minuteResetTimer = new Timer(_ => ResetMinuteCounter(), null, TimeSpan.FromMinutes(1), TimeSpan.FromMinutes(1));
        _hourResetTimer = new Timer(_ => ResetHourCounter(), null, TimeSpan.FromHours(1), TimeSpan.FromHours(1));
        _statsTimer = new Timer(UpdateStatsGraph, null, TimeSpan.Zero, TimeSpan.FromSeconds(1));
    }

    private async void StartServerButton_Click(object sender, RoutedEventArgs e)
    {
        if (!_isRunning)
        {
            if (!int.TryParse(PortInput.Text, out int port) || port <= 0 || port > 65535)
            {
                MessageBox.Show("Пожалуйста, введите корректный номер порта!", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            _listener = new HttpListener();
            _listener.Prefixes.Add($"http://localhost:{port}/");

            try
            {
                _listener.Start();
                _isRunning = true;
                StartServerButton.Content = new Emoji.Wpf.TextBlock { Text = "Остановить сервер ⏹️", FontSize = 14 };
                Log("🚀 Сервер запущен.", "All", "Success");
                await ListenAsync();
            }
            catch (Exception ex)
            {
                Log($"❌ Ошибка при запуске сервера: {ex.Message}", "All", "Error");
            }
        }
        else
        {
            _isRunning = false;
            _listener.Stop();
            _listener.Close();
            StartServerButton.Content = new Emoji.Wpf.TextBlock { Text = "Запустить сервер 🔧", FontSize = 14 };
            Log("⏹️ Сервер остановлен.", "All", "Success");
        }
    }

    private async Task ListenAsync()
    {
        while (_isRunning)
        {
            try
            {
                var context = await _listener.GetContextAsync();
                ThreadPool.QueueUserWorkItem(async _ => await HandleRequestAsync(context));
            }
            catch (HttpListenerException)
            {
                // Слушатель остановлен
            }
            catch (Exception ex)
            {
                Log($"❌ Ошибка в слушателе: {ex.Message}", "All", "Error");
            }
        }
    }

    private void Log(string message, string method = "All", string status = "Success")
    {
        lock (_lock)
        {
            var logEntry = $"[{DateTime.Now}] [{method}] [{status}] {TranslateStatus(message)}";
            _logs.Add(logEntry);

            LogOutput.Dispatcher.Invoke(() =>
            {
                if ((_logFilterMethod == "All" || logEntry.Contains($"[{_logFilterMethod}]")) &&
                    (_logFilterStatus == "All" || logEntry.Contains($"[{TranslateStatus(_logFilterStatus)}]")))
                {
                    LogOutput.Text += logEntry + Environment.NewLine;
                }
            });

            File.AppendAllText("logs.txt", logEntry + Environment.NewLine);
        }
    }

    private string TranslateStatus(string status)
    {
        return status switch
        {
            "Success" => "Успешно",
            "Error" => "Ошибка",
            _ => status
        };
    }

    private void MethodFilterComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
    {
        var comboBox = sender as ComboBox;
        _logFilterMethod = comboBox?.SelectedIndex switch
        {
            0 => "All",
            1 => "GET",
            2 => "POST",
            _ => "All"
        };
        RefreshLogDisplay();
    }

    private void StatusFilterComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
    {
        var comboBox = sender as ComboBox;
        _logFilterStatus = comboBox?.SelectedIndex switch
        {
            0 => "All",
            1 => "Success",
            2 => "Error",
            _ => "All"
        };
        RefreshLogDisplay();
    }

    private void GraphTypeComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
    {
        var comboBox = sender as ComboBox;
        _graphType = comboBox?.SelectedIndex switch
        {
            0 => "RealTime",
            1 => "Minute",
            2 => "Hour",
            _ => "RealTime"
        };
    }

    private void RefreshLogDisplay()
    {
        Dispatcher.Invoke(() =>
        {
            if (LogOutput == null) return;

            LogOutput.Text = string.Join(Environment.NewLine,
                _logs.Where(log =>
                    (_logFilterMethod == "All" || log.Contains($"[{_logFilterMethod}]")) &&
                    (_logFilterStatus == "All" || log.Contains($"[{_logFilterStatus}]"))
                )
            );
        });
    }

    private void UpdateStatsGraph(object state)
    {
        Dispatcher.Invoke(() =>
        {
            string currentTimeLabel = DateTime.Now.ToString("HH:mm:ss");
            string currentMinuteLabel = DateTime.Now.ToString("HH:mm");
            string currentHourLabel = DateTime.Now.ToString("HH");

            switch (_graphType)
            {
                case "RealTime":
                    ((LineSeries)ChartData[0]).Values.Add(_getRequestsCount);
                    ((LineSeries)ChartData[1]).Values.Add(_postRequestsCount);
                    TimeLabels.Add(currentTimeLabel);
                    break;

                case "Minute":
                    ClearChartData();
                    foreach (var entry in _minuteAggregatedRequests)
                    {
                        TimeLabels.Add(entry.Time);
                        ((LineSeries)ChartData[0]).Values.Add(entry.GetRequests); 
                        ((LineSeries)ChartData[1]).Values.Add(entry.PostRequests); 
                    }
                    ((LineSeries)ChartData[0]).Values.Add(_getRequestsCount);
                    ((LineSeries)ChartData[1]).Values.Add(_postRequestsCount);
                    TimeLabels.Add(currentTimeLabel);
                    break;

                case "Hour":
                    ClearChartData();
                    foreach (var entry in _hourAggregatedRequests)
                    {
                        TimeLabels.Add(entry.Time);
                        ((LineSeries)ChartData[0]).Values.Add(entry.GetRequests);
                        ((LineSeries)ChartData[1]).Values.Add(entry.PostRequests);
                    }
                    ((LineSeries)ChartData[0]).Values.Add(_getRequestsCount);
                    ((LineSeries)ChartData[1]).Values.Add(_postRequestsCount);
                    TimeLabels.Add(currentTimeLabel);
                    break;
            }

            if (TimeLabels.Count > 20)
            {
                TimeLabels.RemoveAt(0);
                foreach (var series in ChartData)
                {
                    ((LineSeries)series).Values.RemoveAt(0);
                }
            }
        });
    }

    private void ClearChartData()
    {
        TimeLabels.Clear();
        foreach (var series in ChartData)
        {
            ((LineSeries)series).Values.Clear();
        }
    }

    private void ResetMinuteCounter()
    {
        lock (_lock)
        {
            _minuteAggregatedRequests.Add((DateTime.Now.ToString("HH:mm"), _currentMinuteGetRequests, _currentMinutePostRequests));
            _currentMinuteGetRequests = 0;
            _currentMinutePostRequests = 0;
        }
    }

    private void ResetHourCounter()
    {
        lock (_lock)
        {
            _hourAggregatedRequests.Add((DateTime.Now.ToString("HH"), _currentHourGetRequests, _currentHourPostRequests));
            _currentHourGetRequests = 0;
            _currentHourPostRequests = 0;
        }
    }

    private async Task HandleRequestAsync(HttpListenerContext context)
    {
        try
        {
            var request = context.Request;
            var response = context.Response;
            lock (_lock)
            {
                Log($"[{DateTime.Now}] {request.HttpMethod} {request.Url}", request.HttpMethod, "Success");
                foreach (var header in request.Headers.AllKeys)
                {
                    Log($"{header}: {request.Headers[header]}", request.HttpMethod, "Success");
                }
            }
            string responseBody;
            if (request.HttpMethod == "GET")
            {
                Interlocked.Increment(ref _getRequestsCount);
                Interlocked.Increment(ref _currentMinuteGetRequests);
                Interlocked.Increment(ref _currentHourGetRequests);
                var stats = new
                {
                    Status = "Success",
                    Message = "GET запрос обработан.",
                    TotalGetRequests = _getRequestsCount,
                    TotalPostRequests = _postRequestsCount
                };
                responseBody = JsonSerializer.Serialize(stats);
            }
            else if (request.HttpMethod == "POST")
            {
                Interlocked.Increment(ref _postRequestsCount);
                Interlocked.Increment(ref _currentMinutePostRequests);
                Interlocked.Increment(ref _currentHourPostRequests);
                using var reader = new StreamReader(request.InputStream, request.ContentEncoding);
                var body = await reader.ReadToEndAsync();
                lock (_lock)
                {
                    Log($"Тело запроса: {body}", request.HttpMethod, "Success");
                }
                var id = Guid.NewGuid().ToString();
                var result = new
                {
                    Status = "Success",
                    Message = "POST запрос обработан.",
                    RequestId = id
                };
                responseBody = JsonSerializer.Serialize(result);
            }
            else
            {
                responseBody = JsonSerializer.Serialize(new { Status = "Error", Message = "Неподдерживаемый метод HTTP." });
                Log($"❌ Неподдерживаемый метод HTTP: {request.HttpMethod}", request.HttpMethod, "Error");
            }
            var buffer = Encoding.UTF8.GetBytes(responseBody);
            response.ContentType = "application/json";
            response.ContentLength64 = buffer.Length;
            await response.OutputStream.WriteAsync(buffer, 0, buffer.Length);
            response.Close();
            Dispatcher.Invoke(() =>
            {
                GetRequestsCount.Text = _getRequestsCount.ToString();
                PostRequestsCount.Text = _postRequestsCount.ToString();
            });
        }
        catch (Exception ex)
        {
            Log($"❌ Ошибка при обработке запроса: {ex.Message}", "All", "Error");
        }
    }
}
