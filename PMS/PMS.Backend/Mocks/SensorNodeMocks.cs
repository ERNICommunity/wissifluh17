using PMS.Backend.Model;
using System;
using System.Collections.Generic;

namespace PMS.Backend.Mocks
{
    public static class SensorNodeMocks
    {
        public static IEnumerable<SensorNode> SensorNodes = new List<SensorNode>
        {
            new SensorNode{Id=new Guid("896f0f55-6f82-440d-a4bc-2c0a84f6c225"), Name="Hotspot1", Latitude=0.1, Longitude=0.1},
            new SensorNode{Id=new Guid("52c42322-1166-401f-9074-0243baf2ffd7"), Name="Hotspot2", Latitude=0.2, Longitude=0.2},
            new SensorNode{Id=new Guid("4b8aff41-2c46-44c2-89c5-85e9acc4d22a"), Name="Hotspot3", Latitude=0.3, Longitude=0.3},
            new SensorNode{Id=new Guid("c9c0dd0f-c1eb-46c1-b731-0651d07786ff"), Name="Hotspot4", Latitude=0.4, Longitude=0.4},
            new SensorNode{Id=new Guid("5e95a529-a9a4-4533-a815-c2db957e0b34"), Name="Hotspot5", Latitude=0.5, Longitude=0.5},
            new SensorNode{Id=new Guid("6963bd4c-c643-42c5-8538-ba061beea381"), Name="Hotspot6", Latitude=0.6, Longitude=0.6},
        };
    }
}
