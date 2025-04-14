using LibraryApp.Data;
using LibraryApp.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace LibraryApp.Windows
{
    /// <summary>
    /// Interaction logic for AddGenresWindow.xaml
    /// </summary>
    public partial class AddGenresWindow : Window
    {
        private AppDbContext _context;
        private Genre _genreToEdit;

        public AddGenresWindow(Genre genre = null)
        {
            InitializeComponent();
            _context = new AppDbContext();
            _genreToEdit = genre;

            if (_genreToEdit != null)
            {
                TitleTextBox.Text = _genreToEdit.Name;
                DescriptionComboBox.Text = _genreToEdit.Description;
            }
        }

        private void AddGenre_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrWhiteSpace(TitleTextBox.Text))
            {
                MessageBox.Show("Пожалуйста, заполните все поля.", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            if (_genreToEdit != null)
            {
                _genreToEdit.Name = TitleTextBox.Text;
                _genreToEdit.Description = DescriptionComboBox.Text;

                _context.Genres.Update(_genreToEdit);
            }
            else
            {
                var newGenre = new Genre
                {
                    Name = TitleTextBox.Text,
                    Description = DescriptionComboBox.Text
                };

                _context.Genres.Add(newGenre);
            }

            _context.SaveChanges();
            this.Close();
        }

        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}
