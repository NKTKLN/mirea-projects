using Microsoft.EntityFrameworkCore;
using TourGuideApp.Models;

namespace TourGuideApp.Data
{
    public class ApplicationDbContext : DbContext
    {
        public DbSet<City> Cities { get; set; }
        public DbSet<Attraction> Attractions { get; set; }

        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options) { }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<City>()
                .HasMany(c => c.Attractions)
                .WithOne(a => a.City)
                .HasForeignKey(a => a.CityId);
        }
    }
}
