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

namespace WpfApp
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        // Обработчик события PasswordChanged
        private void PasswordBox_PasswordChanged(object sender, RoutedEventArgs e)
        {
            // Проверяем длину пароля
            if (PasswordBox.Password.Length < 7)
            {
                PasswordErrorLabel.Visibility = Visibility.Visible;
                PasswordBox.BorderBrush = Brushes.Red;
            }
            else
            {
                PasswordErrorLabel.Visibility = Visibility.Hidden;
                PasswordBox.BorderBrush = Brushes.LightSlateGray;
            }
        }

        private void ConfirmPasswordBox_PasswordChanged(object sender, RoutedEventArgs e)
        {
            // Проверяем длину пароля
            if (ConfirmPasswordBox.Password.Length < 7)
            {
                ConfirmPasswordErrorLabel.Visibility = Visibility.Visible;
                ConfirmPasswordBox.BorderBrush = Brushes.Red;
            }
            else
            {
                ConfirmPasswordErrorLabel.Visibility = Visibility.Hidden;
                ConfirmPasswordBox.BorderBrush = Brushes.LightSlateGray;
            }
        }
    }
}