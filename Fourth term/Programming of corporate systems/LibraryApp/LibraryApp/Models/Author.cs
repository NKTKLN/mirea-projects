using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LibraryApp.Models
{
    public class Author
    {
        public int Id { get; set; }

        [Required, MaxLength(100)]
        public string ?FirstName { get; set; }

        [Required, MaxLength(100)]
        public string ?LastName { get; set; }

        public DateTime BirthDate { get; set; }

        [MaxLength(100)]
        public string ?Country { get; set; }
    }
}
