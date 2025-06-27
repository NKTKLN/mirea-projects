using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System;
using System.IO;
using TourGuideApp.Models;
using TourGuideApp.Data;

namespace TourGuideApp.Controllers
{
    public class AdminController : BaseAdminController
    {
        private readonly ApplicationDbContext _context;

        public AdminController(ApplicationDbContext context)
        {
            _context = context;
        }

        // Метод сохранения файла с созданием папки
        private string SaveImage(IFormFile photo)
        {
            if (photo == null || photo.Length == 0)
                return null;

            var uploadsFolder = Path.Combine(Directory.GetCurrentDirectory(), "wwwroot", "images");

            // Создаем папку, если её нет
            if (!Directory.Exists(uploadsFolder))
            {
                Directory.CreateDirectory(uploadsFolder);
            }

            var uniqueFileName = Guid.NewGuid() + Path.GetExtension(photo.FileName);
            var filePath = Path.Combine(uploadsFolder, uniqueFileName);

            using (var fileStream = new FileStream(filePath, FileMode.Create))
            {
                photo.CopyTo(fileStream);
            }

            return "/images/" + uniqueFileName;
        }

        [HttpGet]
        public IActionResult AddCity()
        {
            return View();
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> AddCity(CityCreateViewModel model)
        {
            if (!ModelState.IsValid)
                return View(model);

            var city = new City
            {
                Name = model.Name,
                Region = model.Region,
                Population = model.Population,
                History = model.History
            };

            if (model.Photo != null)
            {
                city.PhotoPath = SaveImage(model.Photo);
            }

            if (model.CoatOfArms != null)
            {
                city.CoatOfArmsPath = SaveImage(model.CoatOfArms);
            }

            _context.Cities.Add(city);
            await _context.SaveChangesAsync();

            return RedirectToAction("Details", "Cities", new { id = city.Id });
        }

        [HttpGet]
        public async Task<IActionResult> AddAttraction()
        {
            ViewBag.Cities = await _context.Cities.ToListAsync();
            return View();
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> AddAttraction(AttractionCreateViewModel model)
        {
            if (!ModelState.IsValid)
            {
                ViewBag.Cities = await _context.Cities.ToListAsync();
                return View(model);
            }

            var attraction = new Attraction
            {
                Name = model.Name,
                Description = model.Description,
                History = model.History,
                WorkingHours = model.WorkingHours,
                EntranceFee = model.EntranceFee,
                CityId = model.CityId
            };

            if (model.Photo != null)
            {
                attraction.PhotoPath = SaveImage(model.Photo);
            }

            var city = await _context.Cities.FindAsync(model.CityId);
            if (city == null)
            {
                ModelState.AddModelError("", "Город не найден");
                ViewBag.Cities = await _context.Cities.ToListAsync();
                return View(model);
            }

            attraction.City = city;

            _context.Attractions.Add(attraction);
            await _context.SaveChangesAsync();

            return RedirectToAction("Details", "Attractions", new { id = attraction.Id });
        }

        [HttpGet]
        public IActionResult Login()
        {
            return View();
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public IActionResult Login(string username, string password)
        {
            if (username == "admin" && password == "admin")
            {
                HttpContext.Session.SetString("User", "Admin");
                return RedirectToAction("Index");
            }

            ModelState.AddModelError("", "Неверный логин или пароль.");
            return View();
        }

        [HttpGet]
        public IActionResult Index()
        {
            if (!IsAdmin())
            {
                return RedirectToAction("Login");
            }

            return View();
        }

        private bool IsAdmin()
        {
            return HttpContext.Session.GetString("User") == "Admin";
        }
    }
}