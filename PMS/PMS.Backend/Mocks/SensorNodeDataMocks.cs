using PMS.Backend.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace PMS.Backend.Mocks
{
    public static class SensorNodeDataMocks
    {
        public static IEnumerable<SensorNodeData> SensorNodeData = new List<SensorNodeData>
        {
            new SensorNodeData{Id=1, HotspotId=new Guid("896f0f55-6f82-440d-a4bc-2c0a84f6c225"), DateTime=DateTime.UtcNow, Pm2_5=0.1, Pm10=0.1,Temperature=24.3, Humidity=22.1},
            new SensorNodeData{Id=2, HotspotId=new Guid("896f0f55-6f82-440d-a4bc-2c0a84f6c225"), DateTime=DateTime.UtcNow, Pm2_5=0.2, Pm10=0.1,Temperature=24.3, Humidity=22.1},
            new SensorNodeData{Id=3, HotspotId=new Guid("896f0f55-6f82-440d-a4bc-2c0a84f6c225"), DateTime=DateTime.UtcNow, Pm2_5=0.3, Pm10=0.1,Temperature=24.3, Humidity=22.1},
            new SensorNodeData{Id=4, HotspotId=new Guid("896f0f55-6f82-440d-a4bc-2c0a84f6c225"), DateTime=DateTime.UtcNow, Pm2_5=0.4, Pm10=0.1,Temperature=24.3, Humidity=22.1},
            new SensorNodeData{Id=5, HotspotId=new Guid("896f0f55-6f82-440d-a4bc-2c0a84f6c225"), DateTime=DateTime.UtcNow, Pm2_5=0.5, Pm10=0.1,Temperature=22.3, Humidity=18.1},
            new SensorNodeData{Id=6, HotspotId=new Guid("896f0f55-6f82-440d-a4bc-2c0a84f6c225"), DateTime=DateTime.UtcNow, Pm2_5=0.6, Pm10=0.1,Temperature=22.3, Humidity=17.1},
        };
    }
}
