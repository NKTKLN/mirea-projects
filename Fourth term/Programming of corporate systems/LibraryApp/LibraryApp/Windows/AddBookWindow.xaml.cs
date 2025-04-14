using LibraryApp.Data;
using LibraryApp.Models;
using Microsoft.EntityFrameworkCore;
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
    /// Interaction logic for AddBookWindow.xaml
    /// </summary>
    public partial class AddBookWindow : Window
    {
        private AppDbContext _context;
        private Book _bookToEdit;
        public AddBookWindow(Book? book = null)
        {
            InitializeComponent();

            _context = new AppDbContext();
            _bookToEdit = book;

            AuthorComboBox.ItemsSource = _context.Authors
                .Select(a => new { a.Id, Name = a.FirstName + " " + a.LastName })
                .ToList();
            AuthorComboBox.DisplayMemberPath = "Name";
            AuthorComboBox.SelectedValuePath = "Id";

            GenreComboBox.ItemsSource = _context.Genres
                .Select(g => new { g.Id, g.Name })
                .ToList();
            GenreComboBox.DisplayMemberPath = "Name";
            GenreComboBox.SelectedValuePath = "Id";

            if (_bookToEdit != null)
            {
                TitleTextBox.Text = _bookToEdit.Title;
                YearTextBox.Text = _bookToEdit.PublishYear.ToString();
                ISBNTextBox.Text = _bookToEdit.ISBN;
                QuantityTextBox.Text = _bookToEdit.QuantityInStock.ToString();

                AuthorComboBox.SelectedValue = _bookToEdit.AuthorId;
                GenreComboBox.SelectedValue = _bookToEdit.GenreId;
            }
        }

        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void AddBook_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrWhiteSpace(TitleTextBox.Text) || string.IsNullOrWhiteSpace(ISBNTextBox.Text) || AuthorComboBox.SelectedItem == null || GenreComboBox.SelectedItem == null)
            {
                MessageBox.Show("Пожалуйста, заполните все поля.", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            if (!int.TryParse(YearTextBox.Text, out int year) || !int.TryParse(QuantityTextBox.Text, out int quantity))
            {
                MessageBox.Show("Год публикации и количество должны быть числовыми значениями.", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            var selectedAuthorId = (int?)AuthorComboBox.SelectedValue;
            var selectedGenreId = (int?)GenreComboBox.SelectedValue;

            if (_bookToEdit != null)
            {
                _bookToEdit.Title = TitleTextBox.Text;
                _bookToEdit.PublishYear = year;
                _bookToEdit.ISBN = ISBNTextBox.Text;
                _bookToEdit.QuantityInStock = quantity;
                _bookToEdit.AuthorId = selectedAuthorId.Value;
                _bookToEdit.GenreId = selectedGenreId.Value;

                _context.Books.Update(_bookToEdit);
            }
            else
            {
                var newBook = new Book
                {
                    Title = TitleTextBox.Text,
                    PublishYear = year,
                    ISBN = ISBNTextBox.Text,
                    QuantityInStock = quantity,
                    AuthorId = selectedAuthorId.Value,
                    GenreId = selectedGenreId.Value
                };

                _context.Books.Add(newBook);
            }

            _context.SaveChanges();

            this.Close();
        }
    }
}
