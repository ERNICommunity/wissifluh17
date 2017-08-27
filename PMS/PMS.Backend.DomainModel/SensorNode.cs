using System;
using System.Collections.Generic;

namespace PMS.Backend.DomainModel
{
    public class SensorNode
    {
        public Guid Id { get; set; }

        public string Name { get; set; }

        public double Latitude { get; set; }

        public double Longitude { get; set; }

        public IEnumerable<SensorNodeData> SensorData { get; set; }
    }
}
