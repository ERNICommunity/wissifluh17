using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;
using PMS.Backend.Data.Persistence.Entities;

namespace PMS.Backend.Data.Persistence.EntityConfiguration
{
    public class SensorNodeDataEntityConfiguration : EntityTypeConfiguration<SensorNodeDataEntity>
    {
        public override void Map(EntityTypeBuilder<SensorNodeDataEntity> builder)
        {
            builder.ToTable("SensorNodeData");

            builder.HasKey(p => p.Id);

            builder.Property(p => p.SensorNodeId).IsRequired();
            builder.Property(p => p.DateTime).IsRequired();
            builder.Property(p => p.Pm2_5).IsRequired();
            builder.Property(p => p.Pm10).IsRequired();
            builder.Property(p => p.Humidity).IsRequired();
            builder.Property(p => p.Temperature).IsRequired();

            builder.HasOne(p => p.SensorNode).WithMany(b => b.SensorData).HasForeignKey(p => p.SensorNodeId);
        }
    }
}
