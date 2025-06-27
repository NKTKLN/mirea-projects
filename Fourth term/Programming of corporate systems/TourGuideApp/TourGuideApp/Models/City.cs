using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace TourGuideApp.Models
{
    public class City
    {
        public int Id { get; set; }

        [Required(ErrorMessage = "Название обязательно")]
        [Column(TypeName = "nvarchar(255)")]
        public string Name { get; set; }

        [Required(ErrorMessage = "Регион обязателен")]
        public string Region { get; set; }

        [Required(ErrorMessage = "Население обязательно")]
        public int Population { get; set; }

        [Required(ErrorMessage = "История обязательна")]
        public string History { get; set; }

        public string PhotoPath { get; set; }

        public string CoatOfArmsPath { get; set; }

        public ICollection<Attraction> Attractions { get; set; } = new List<Attraction>();

        [NotMapped]
        public IFormFile Photo { get; set; }

        [NotMapped]
        public IFormFile CoatOfArms { get; set; }
    }
}