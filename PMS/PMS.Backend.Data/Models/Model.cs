using Microsoft.EntityFrameworkCore;
using PMS.Backend.Data.Persistence.Entities;
using PMS.Backend.Data.Persistence.EntityConfiguration;

namespace PMS.Backend.Data.Models
{
    public class PmsDataContext : DbContext
    {
        public PmsDataContext(DbContextOptions<PmsDataContext> options)
            : base(options)
        { }

        public DbSet<SensorNodeEntity> SensorNode { get; set; }
        public DbSet<SensorNodeDataEntity> SensorNodeData { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlServer(@"Server=NB-SK-16\SQLEXPRESS120;Database=PMS;Trusted_Connection=True;");
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.AddConfiguration(new SensorNodeEntityConfiguration());
            modelBuilder.AddConfiguration(new SensorNodeDataEntityConfiguration());
        }
    }
}