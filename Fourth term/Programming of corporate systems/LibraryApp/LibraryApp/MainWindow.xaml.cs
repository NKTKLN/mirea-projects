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
using LibraryApp.Data;
using LibraryApp.Models;
using LibraryApp.Windows;
using Microsoft.EntityFrameworkCore;

namespace LibraryApp;

/// <summary>
/// Interaction logic for MainWindow.xaml
/// </summary>
public partial class MainWindow : Window
{
    private AppDbContext _context = new AppDbContext();
    private List<Book> _allBooks;

    public MainWindow()
    {
        InitializeComponent();
        InitializeDatabase();
        LoadBooks();
        LoadFilters();
    }

    private void LoadFilters()
    {
        using (var db = new AppDbContext())
        {
            AuthorFilter.ItemsSource = new List<string> { "--любой--" }
                                   .Concat(_context.Authors.Select(a => a.FirstName + " " + a.LastName))
                                   .ToList();
            GenreFilter.ItemsSource = new List<string> { "--любой--" }
                                    .Concat(_context.Genres.Select(g => g.Name))
                                    .ToList();
        }
    }

    private void FilterChanged(object sender, RoutedEventArgs e)
    {
        var searchQuery = SearchTextBox.Text;
        var authorFilter = AuthorFilter.SelectedItem?.ToString();
        var genreFilter = GenreFilter.SelectedItem?.ToString();
        LoadBooks(searchQuery, authorFilter, genreFilter);
    }

    public void InitializeDatabase()
    {
        using (var context = new AppDbContext())
        {
            context.Database.EnsureCreated();
        }
    }

    private void LoadBooks(string searchQuery = "", string authorFilter = null, string genreFilter = null)
    {
        var query = _context.Books.Include(b => b.Author).Include(b => b.Genre).AsQueryable();

        if (!string.IsNullOrEmpty(searchQuery))
        {
            query = query.Where(b => b.Title.Contains(searchQuery));
        }

        if (authorFilter != "--любой--" && !string.IsNullOrEmpty(authorFilter))
        {
            query = query.Where(b => (b.Author.FirstName + " " + b.Author.LastName) == authorFilter);
        }

        if (genreFilter != "--любой--" && !string.IsNullOrEmpty(genreFilter))
        {
            query = query.Where(b => b.Genre.Name == genreFilter);
        }

        _allBooks = query.ToList();
        BooksDataGrid.ItemsSource = _allBooks.Select(b => new
        {
            b.Id,
            b.Title,
            AuthorName = b.Author.FirstName + " " + b.Author.LastName,
            GenreName = b.Genre.Name,
            b.PublishYear,
            b.ISBN,
            b.QuantityInStock
        }).ToList();
    }

    private void OpenGenres_Click(object sender, RoutedEventArgs e)
    {
        var addWindow = new GenresWindow();
        addWindow.ShowDialog();
        LoadBooks();
        LoadFilters();
    }
    private void OpenAuthors_Click(object sender, RoutedEventArgs e)
    {
        var addWindow = new AuthorsWindow();
        addWindow.ShowDialog();
        LoadBooks();
        LoadFilters();
    }

    private void AddBook_Click(object sender, RoutedEventArgs e)
    {
        var addWindow = new AddBookWindow();
        addWindow.ShowDialog();
        LoadBooks();
    }

    private void EditBook_Click(object sender, RoutedEventArgs e)
    {
        var bookId = (int)((Button)sender).Tag;
        var book = _context.Books.FirstOrDefault(b => b.Id == bookId);

        if (book != null)
        {
            var editWindow = new AddBookWindow(book);
            editWindow.ShowDialog();
            LoadBooks();
        }
        else
        {
            MessageBox.Show("Книга не найдена.", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Warning);
        }
    }

    private void DeleteBook_Click(object sender, RoutedEventArgs e)
    {
        var bookId = (int)((Button)sender).Tag;
        var book = _context.Books.FirstOrDefault(b => b.Id == bookId);

        if (book != null)
        {
            if (MessageBox.Show($"Удалить книгу '{book.Title}'?", "Удаление", MessageBoxButton.YesNo) == MessageBoxResult.Yes)
            {
                _context.Books.Remove(book);
                _context.SaveChanges();
                LoadBooks();
            }
        }
        else
        {
            MessageBox.Show("Книга не найдена.", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Warning);
        }
    }
}