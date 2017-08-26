using System;

namespace PMS.Backend.Contract.Dto
{
    public class SensorNode
    {
        public Guid Id { get; set; }

        public string Name { get; set; }

        public double Latitude { get; set; }

        public double Longitude { get; set; }
    }
}
