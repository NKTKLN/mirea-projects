using LibraryApp.Data;
using LibraryApp.Models;
using System;
using System.Linq;
using System.Windows;
using System.Windows.Controls;

namespace LibraryApp.Windows
{
    public partial class AuthorsWindow : Window
    {
        private AppDbContext _context;

        public AuthorsWindow()
        {
            InitializeComponent();
            _context = new AppDbContext();
            LoadAuthors();
        }

        private void LoadAuthors()
        {
            AuthorsDataGrid.ItemsSource = _context.Authors
                .Select(a => new
                {
                    a.Id,
                    a.FirstName,
                    a.LastName,
                    a.BirthDate,
                    a.Country
                }).ToList();
        }

        private void AddAuthor_Click(object sender, RoutedEventArgs e)
        {
            var addAuthorWindow = new AddAuthorWindow();
            addAuthorWindow.ShowDialog();
            LoadAuthors();
        }

        private void EditAuthor_Click(object sender, RoutedEventArgs e)
        {
            var authorId = (int)((Button)sender).Tag;
            var selectedAuthor = _context.Authors.FirstOrDefault(a => a.Id == authorId);

            if (selectedAuthor != null)
            {
                var editAuthorWindow = new AddAuthorWindow(selectedAuthor);
                editAuthorWindow.ShowDialog();
                LoadAuthors();
            }
            else
            {
                MessageBox.Show("Автор не найден.", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Warning);
            }
        }

        private void DeleteAuthor_Click(object sender, RoutedEventArgs e)
        {
            var authorId = (int)((Button)sender).Tag;
            var selectedAuthor = _context.Authors.FirstOrDefault(a => a.Id == authorId);

            if (selectedAuthor != null)
            {
                if (MessageBox.Show($"Удалить автора '{selectedAuthor.FirstName} {selectedAuthor.LastName}'?", "Удаление", MessageBoxButton.YesNo) == MessageBoxResult.Yes)
                {
                    _context.Authors.Remove(selectedAuthor);
                    _context.SaveChanges();
                    LoadAuthors();
                }
            }
            else
            {
                MessageBox.Show("Автор не найден.", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Warning);
            }
        }
    }
}
