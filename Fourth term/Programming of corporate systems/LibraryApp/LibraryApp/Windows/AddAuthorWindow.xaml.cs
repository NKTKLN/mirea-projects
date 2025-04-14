using LibraryApp.Data;
using LibraryApp.Models;
using System;
using System.Windows;

namespace LibraryApp.Windows
{
    public partial class AddAuthorWindow : Window
    {
        private AppDbContext _context;
        private Author _authorToEdit;

        public AddAuthorWindow(Author author = null)
        {
            InitializeComponent();
            _context = new AppDbContext();
            _authorToEdit = author;

            if (_authorToEdit != null)
            {
                FirstNameTextBox.Text = _authorToEdit.FirstName;
                LastNameTextBox.Text = _authorToEdit.LastName;
                BirthDatePicker.SelectedDate = _authorToEdit.BirthDate;
                CountryTextBox.Text = _authorToEdit.Country;
            }
        }

        private void AddAuthor_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrWhiteSpace(FirstNameTextBox.Text) || string.IsNullOrWhiteSpace(LastNameTextBox.Text))
            {
                MessageBox.Show("Пожалуйста, заполните все обязательные поля.", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            if (_authorToEdit != null)
            {
                _authorToEdit.FirstName = FirstNameTextBox.Text;
                _authorToEdit.LastName = LastNameTextBox.Text;
                _authorToEdit.BirthDate = BirthDatePicker.SelectedDate ?? DateTime.MinValue;
                _authorToEdit.Country = CountryTextBox.Text;

                _context.Authors.Update(_authorToEdit);
            }
            else
            {
                var newAuthor = new Author
                {
                    FirstName = FirstNameTextBox.Text,
                    LastName = LastNameTextBox.Text,
                    BirthDate = BirthDatePicker.SelectedDate ?? DateTime.MinValue,
                    Country = CountryTextBox.Text
                };

                _context.Authors.Add(newAuthor);
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
