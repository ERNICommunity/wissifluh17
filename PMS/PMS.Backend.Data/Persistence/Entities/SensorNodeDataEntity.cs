using System;

namespace PMS.Backend.Data.Persistence.Entities
{
    public class SensorNodeDataEntity
    {
        public int Id { get; set; }

        public Guid SensorNodeId { get; set; }

        public DateTime DateTime { get; set; }

        public double Pm2_5 { get; set; }

        public double Pm10 { get; set; }

        public double Humidity { get; set; }

        public double Temperature { get; set; }

        public SensorNodeEntity SensorNode { get; set; }
    }
}
