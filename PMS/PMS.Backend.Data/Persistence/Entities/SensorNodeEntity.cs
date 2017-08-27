using System;
using System.Collections.Generic;

namespace PMS.Backend.Data.Persistence.Entities
{
    public class SensorNodeEntity
    {
        public Guid Id { get; set; }

        public string Name { get; set; }

        public double Latitude { get; set; }

        public double Longitude { get; set; }

        public ICollection<SensorNodeDataEntity> SensorData { get; set; }
    }
}
