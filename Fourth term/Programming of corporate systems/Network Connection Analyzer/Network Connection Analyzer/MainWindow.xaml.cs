using Network_Connection_Analyzer.Data;
using Network_Connection_Analyzer.Models;
using System.Net;
using System.Net.NetworkInformation;
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

namespace Network_Connection_Analyzer;

/// <summary>
/// Interaction logic for MainWindow.xaml
/// </summary>
public partial class MainWindow : Window
{

    private AppDbContext _dbContext = new AppDbContext();

    public MainWindow()
    {
        InitializeComponent();
        InitializeDatabase();
        LoadNetworkInterfaces();
        LoadHistory();
    }

    public void InitializeDatabase()
    {
        using (var context = new AppDbContext())
        {
            context.Database.EnsureCreated();
        }
    }

    private void LoadNetworkInterfaces()
    {
        var interfaces = NetworkInterface.GetAllNetworkInterfaces()
            .Select(ni => new
            {
                Description = ni.Description,
                Name = ni.Name,
                MACAddress = ni.GetPhysicalAddress().ToString(),
                IPAddresses = ni.GetIPProperties().UnicastAddresses
                    .Where(addr => addr.Address.AddressFamily == System.Net.Sockets.AddressFamily.InterNetwork)
                    .Select(addr => addr.Address.ToString())
                    .ToList(),
                SubnetMask = ni.GetIPProperties().UnicastAddresses
                    .Where(addr => addr.Address.AddressFamily == System.Net.Sockets.AddressFamily.InterNetwork)
                    .Select(addr => addr.IPv4Mask?.ToString())
                    .FirstOrDefault(),
                Status = GetStatusEmoji(ni.OperationalStatus),
                Speed = ni.Speed / 1_000_000 + " Mbps",
                Type = ni.NetworkInterfaceType.ToString()
            }).ToList();

        NetworkInterfacesList.ItemsSource = interfaces;
    }

    private string GetStatusEmoji(OperationalStatus status)
    {
        return status switch
        {
            OperationalStatus.Up => "🟢 Включен",
            OperationalStatus.Down => "🔴 Выключен",
            OperationalStatus.Unknown => "❓ Неизвестно",
            OperationalStatus.Dormant => "🌙 Спящий",
            OperationalStatus.NotPresent => "❌ Отсутствует",
            OperationalStatus.LowerLayerDown => "⬇️ Нижний слой выключен",
            _ => "❓ Неизвестно"
        };
    }

    private void NetworkInterfacesList_SelectionChanged(object sender, System.Windows.Controls.SelectionChangedEventArgs e)
    {
        var selectedInterface = NetworkInterfacesList.SelectedItem as dynamic;
        if (selectedInterface != null)
        {
            InterfaceInfo.Text =
                $"Имя: {selectedInterface.Name}\n" +
                $"MAC-адрес: {selectedInterface.MACAddress}\n" +
                $"IP-адрес: {string.Join(", ", selectedInterface.IPAddresses)}\n" +
                $"Маска подсети: {selectedInterface.SubnetMask}\n" +
                $"Состояние: {selectedInterface.Status}\n" +
                $"Скорость: {selectedInterface.Speed}\n" +
                $"Тип: {selectedInterface.Type}";
        }
    }

    private void CheckUrl_Click(object sender, RoutedEventArgs e)
    {
        string url = UrlInput.Text;

        if (!url.StartsWith("http://") && !url.StartsWith("https://"))
        {
            url = "http://" + url;
        }

        if (Uri.TryCreate(url, UriKind.Absolute, out Uri uri))
        {
            if (uri.Scheme == "http" && IsHttpsAvailable(uri.Host))
            {
                uri = new Uri("https://" + uri.Host + uri.AbsolutePath + uri.Query + uri.Fragment);
            }

            string dnsInfo = GetDnsInfo(uri.Host);
            string addressType = GetAddressType(uri.Host);

            string results =
                $"🌐 Схема: {uri.Scheme}\n" +
                $"🏠 Хост: {uri.Host}\n" +
                $"🚪 Порт: {uri.Port}\n" +
                $"📍 Путь: {uri.AbsolutePath}\n" +
                $"📝 Параметры запроса: {uri.Query}\n" +
                $"🔗 Фрагмент: {uri.Fragment}\n" +
                $"🔍 DNS-информация: {dnsInfo}\n" +
                $"🏠 Тип адреса: {addressType}";

            UrlResults.Text = results;

            try
            {
                Ping ping = new Ping();
                PingReply reply = ping.Send(uri.Host);
                results += $"\n🏓 Ping: {(reply.Status == IPStatus.Success ? $"{reply.RoundtripTime} ms" : "Не доступен")}";
            }
            catch (Exception ex)
            {
                results += $"\n⚠️ Ошибка при проверке хоста: {ex.Message}";
            }

            UrlResults.Text = results;

            SaveToHistory(uri.ToString());
            LoadHistory();
        }
        else
        {
            MessageBox.Show("Некорректный URL", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
        }
    }

    private bool IsHttpsAvailable(string host)
    {
        try
        {
            using (var client = new WebClient())
            {
                client.DownloadString("https://" + host);
                return true;
            }
        }
        catch
        {
            return false;
        }
    }

    private string GetDnsInfo(string host)
    {
        try
        {
            IPAddress[] addresses = Dns.GetHostAddresses(host);
            return string.Join(", ", addresses.Select(addr => addr.ToString()));
        }
        catch (Exception ex)
        {
            return $"Ошибка при получении DNS-информации: {ex.Message}";
        }
    }

    private string GetAddressType(string host)
    {
        try
        {
            if (IPAddress.TryParse(host, out IPAddress ipAddress))
            {
                byte[] bytes = ipAddress.GetAddressBytes();

                if (IPAddress.IsLoopback(ipAddress))
                {
                    return "Loopback";
                }
                else if (bytes[0] == 10 ||
                         (bytes[0] == 172 && bytes[1] >= 16 && bytes[1] <= 31) ||
                         (bytes[0] == 192 && bytes[1] == 168))
                {
                    return "Локальный";
                }
                else
                {
                    return "Публичный";
                }
            }
            else
            {
                IPAddress[] addresses = Dns.GetHostAddresses(host);
                if (addresses.Length == 0)
                {
                    return "Не удалось определить IP-адрес";
                }

                ipAddress = addresses[0];
                byte[] bytes = ipAddress.GetAddressBytes();

                if (IPAddress.IsLoopback(ipAddress))
                {
                    return "Loopback";
                }
                else if (bytes[0] == 10 ||
                         (bytes[0] == 172 && bytes[1] >= 16 && bytes[1] <= 31) ||
                         (bytes[0] == 192 && bytes[1] == 168))
                {
                    return "Локальный";
                }
                else
                {
                    return "Публичный";
                }
            }
        }
        catch (Exception ex)
        {
            return $"Ошибка при определении типа адреса: {ex.Message}";
        }
    }

    private void SaveToHistory(string url)
    {
        var historyEntry = new UrlHistory
        {
            Url = url,
            CheckedAt = DateTime.Now
        };
        _dbContext.UrlHistories.Add(historyEntry);
        _dbContext.SaveChanges();
    }

    private void LoadHistory()
    {
        HistoryList.ItemsSource = _dbContext.UrlHistories.OrderByDescending(h => h.CheckedAt).ToList();
    }
}
