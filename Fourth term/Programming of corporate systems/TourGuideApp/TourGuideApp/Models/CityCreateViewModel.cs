using System.ComponentModel.DataAnnotations;

namespace TourGuideApp.Models
{
    public class CityCreateViewModel
    {
        [Required(ErrorMessage = "Название обязательно")]
        public string Name { get; set; }

        [Required(ErrorMessage = "Регион обязателен")]
        public string Region { get; set; }

        [Required(ErrorMessage = "Население обязательно")]
        public int Population { get; set; }

        [Required(ErrorMessage = "История обязательна")]
        public string History { get; set; }

        public IFormFile Photo { get; set; }

        public IFormFile CoatOfArms { get; set; }
    }
}