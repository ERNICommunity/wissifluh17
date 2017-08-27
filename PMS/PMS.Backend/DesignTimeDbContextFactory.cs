using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Design;
using PMS.Backend.Data.Models;

namespace PMS.Backend
{
    public class DesignTimeDbContextFactory : IDesignTimeDbContextFactory<PmsDataContext>
    {
        public PmsDataContext CreateDbContext(string[] args)
        {
            var builder = new DbContextOptionsBuilder<PmsDataContext>();
            //            var connectionString = configuration.GetConnectionString("DefaultConnection");
            var connection = @"Server=NB-SK-16\SQLEXPRESS120;Database=PMS;Trusted_Connection=True;";
            builder.UseSqlServer(connection);
            return new PmsDataContext(builder.Options);
        }
    }
}
