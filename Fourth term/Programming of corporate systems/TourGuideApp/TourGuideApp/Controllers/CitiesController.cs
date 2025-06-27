using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using TourGuideApp.Data;

namespace TourGuideApp.Controllers
{
    public class CitiesController : Controller
    {
        private readonly ApplicationDbContext _context;

        public CitiesController(ApplicationDbContext context) => _context = context;

        public async Task<IActionResult> Index(string search)
        {
            var cities = _context.Cities.AsQueryable();
            if (!string.IsNullOrEmpty(search))
                cities = cities.Where(c => c.Name.ToLower().Contains(search.ToLower()));
            return View(await cities.ToListAsync());
        }

        public async Task<IActionResult> Details(int? id)
        {
            var city = await _context.Cities
                .Include(c => c.Attractions)
                .FirstOrDefaultAsync(c => c.Id == id);
            return View(city);
        }
    }
}
