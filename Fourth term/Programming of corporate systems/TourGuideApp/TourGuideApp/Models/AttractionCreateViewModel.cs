using System.ComponentModel.DataAnnotations;

namespace TourGuideApp.Models
{
    public class AttractionCreateViewModel
{
    [Required(ErrorMessage = "Название обязательно")]
    public string Name { get; set; }

    [Required(ErrorMessage = "Описание обязательно")]
    public string Description { get; set; }

    [Required(ErrorMessage = "История обязательна")]
    public string History { get; set; }

    public string WorkingHours { get; set; }

    public decimal? EntranceFee { get; set; }

    public int CityId { get; set; }

    public IFormFile Photo { get; set; }
}
}
