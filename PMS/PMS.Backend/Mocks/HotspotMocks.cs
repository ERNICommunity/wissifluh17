using PMS.Backend.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace PMS.Backend.Mocks
{
    public static class HotspotMocks
    {
        public static IEnumerable<Hotspot> Hotspots = new List<Hotspot>
        {
            new Hotspot{Id=new Guid("896f0f55-6f82-440d-a4bc-2c0a84f6c225")},
            new Hotspot{Id=new Guid("52c42322-1166-401f-9074-0243baf2ffd7")},
            new Hotspot{Id=new Guid("4b8aff41-2c46-44c2-89c5-85e9acc4d22a")},
            new Hotspot{Id=new Guid("c9c0dd0f-c1eb-46c1-b731-0651d07786ff")},
            new Hotspot{Id=new Guid("5e95a529-a9a4-4533-a815-c2db957e0b34")},
            new Hotspot{Id=new Guid("6963bd4c-c643-42c5-8538-ba061beea381")},
        };
    }
}
