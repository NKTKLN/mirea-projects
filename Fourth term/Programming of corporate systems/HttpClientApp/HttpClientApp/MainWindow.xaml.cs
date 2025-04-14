using System.Net.Http;
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

namespace HttpClientApp;

/// <summary>
/// Interaction logic for MainWindow.xaml
/// </summary>
public partial class MainWindow : Window
{
    private readonly HttpClient _httpClient;

    public MainWindow()
    {
        InitializeComponent();
        _httpClient = new HttpClient();
    }

    private async void SendRequestButton_Click(object sender, RoutedEventArgs e)
    {
        string url = UrlInput.Text.Trim();

        if (string.IsNullOrEmpty(url))
        {
            MessageBox.Show("Пожалуйста, введите корректный URL! 🛠️");
            return;
        }

        try
        {
            HttpResponseMessage response = null;

            int selectedIndex = MethodSelector.SelectedIndex;

            if (selectedIndex == 0) // GET
            {
                response = await _httpClient.GetAsync(url);
            }
            else if (selectedIndex == 1) // POST
            {
                string requestBody = RequestBodyInput.Text.Trim();
                if (string.IsNullOrEmpty(requestBody))
                {
                    MessageBox.Show("Пожалуйста, введите тело запроса для POST! 🛠️");
                    return;
                }

                var content = new StringContent(requestBody, Encoding.UTF8, "application/json");
                response = await _httpClient.PostAsync(url, content);
            }

            if (response != null)
            {
                string responseBody = await response.Content.ReadAsStringAsync();
                ResponseOutput.Text = $"Статус: {response.StatusCode}\n\nОтвет:\n{responseBody}";
            }
        }
        catch (Exception ex)
        {
            MessageBox.Show($"Ошибка при отправке запроса: {ex.Message} ❌", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
        }
    }
}