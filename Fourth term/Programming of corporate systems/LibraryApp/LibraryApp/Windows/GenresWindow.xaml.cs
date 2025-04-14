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
    /// Interaction logic for GenresWindow.xaml
    /// </summary>
    public partial class GenresWindow : Window
    {
        private AppDbContext _context;
        public GenresWindow()
        {
            InitializeComponent();
            _context = new AppDbContext();
            LoadGenres();
        }
        private void LoadGenres()
        {
            GenresDataGrid.ItemsSource = _context.Genres
                .Select(g => new
                {
                    g.Id,
                    g.Name,
                    g.Description
                }).ToList();
        }

        private void AddGenre_Click(object sender, RoutedEventArgs e)
        {
            var addGenreWindow = new AddGenresWindow();
            addGenreWindow.ShowDialog();
            LoadGenres();
        }

        private void EditGenre_Click(object sender, RoutedEventArgs e)
        {
            var genreId = (int)((Button)sender).Tag;
            var selectedGenre = _context.Genres.FirstOrDefault(g => g.Id == genreId);

            if (selectedGenre != null)
            {
                var editWindow = new AddGenresWindow(selectedGenre);
                editWindow.ShowDialog();
                LoadGenres();
            }
            else
            {
                MessageBox.Show("Жанр не найден.", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Warning);
            }
        }

        private void DeleteGenre_Click(object sender, RoutedEventArgs e)
        {
            var genreId = (int)((Button)sender).Tag;
            var selectedGenre = _context.Genres.FirstOrDefault(g => g.Id == genreId);

            if (selectedGenre != null)
            {
                if (MessageBox.Show($"Удалить жанр '{selectedGenre.Name}'?", "Удаление", MessageBoxButton.YesNo) == MessageBoxResult.Yes)
                {
                    _context.Genres.Remove(selectedGenre);
                    _context.SaveChanges();
                    LoadGenres();
                }
            }
            else
            {
                MessageBox.Show("Жанр не найден.", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Warning);
            }
        }
    }
}
