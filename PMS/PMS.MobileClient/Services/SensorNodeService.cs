using System;
using System.Collections.Generic;
using PMS.Backend.Contract.Dto;

namespace PMS.MobileClient.Services
{
    public class SensorNodeService
    {
        public SensorNodeService()
        {
            
        }

        public List<SensorNode> GetAll()
        {
            return new List<SensorNode>
            {
                new SensorNode {Id = Guid.NewGuid(), Latitude = 47.003220, Longitude = 8.494633, Name = "Wissifluh"}
            };
        }
    }
}