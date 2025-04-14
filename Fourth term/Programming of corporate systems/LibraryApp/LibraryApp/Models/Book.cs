using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LibraryApp.Models
{
    public class Book
    {
        public int Id { get; set; }

        [Required, MaxLength(255)]
        public string ?Title { get; set; }

        [ForeignKey("Author")]
        public int? AuthorId { get; set; } = null;
        public Author ?Author { get; set; } = null;

        public int PublishYear { get; set; }

        [Required, MaxLength(13)]
        public string ?ISBN { get; set; }

        [ForeignKey("Genre")]
        public int ?GenreId { get; set; } = null;
        public Genre? Genre { get; set; } = null;

        public int QuantityInStock { get; set; }
    }
}
