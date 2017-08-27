using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;
using PMS.Backend.Data.Persistence.Entities;

namespace PMS.Backend.Data.Persistence.EntityConfiguration
{
    public class SensorNodeEntityConfiguration : EntityTypeConfiguration<SensorNodeEntity>
    {
        public override void Map(EntityTypeBuilder<SensorNodeEntity> builder)
        {
            builder.ToTable("SensorNode");

            builder.HasKey(p => p.Id);

            builder.Property(p => p.Name).IsRequired();
            builder.Property(p => p.Latitude).IsRequired();
            builder.Property(p => p.Longitude).IsRequired();
        }
    }
}
