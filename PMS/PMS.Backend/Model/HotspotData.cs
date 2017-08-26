using System;

namespace PMS.Backend.Model
{
    public class HotspotData
    {
        public int Id { get; set; }

        public Guid HotspotId { get; set; }

        public DateTime DateTime { get; set; }

        public double Pm2_5 { get; set; }

        public double Pm10 { get; set; }
        
        public double Humidity { get; set; }

        public double Temperature { get; set; }
    }
}
