using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace TourGuideApp.Models
{
    public class Attraction
    {
        public int Id { get; set; }

        [Required(ErrorMessage = "Название обязательно")]
        public string Name { get; set; }

        [Required(ErrorMessage = "Описание обязательно")]
        public string Description { get; set; }

        [Required(ErrorMessage = "История обязательна")]
        public string History { get; set; }

        public string PhotoPath { get; set; }   

        [Required(ErrorMessage = "Часы работы обязательны")]
        public string WorkingHours { get; set; }

        public decimal? EntranceFee { get; set; }

        public int CityId { get; set; }

        public City City { get; set; }

        [NotMapped]
        public IFormFile Photo { get; set; }
    }
}
