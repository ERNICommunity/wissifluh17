using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using PMS.Backend.Mocks;
using PMS.Backend.Model;

// For more information on enabling Web API for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace PMS.Backend.Controllers
{
    [Route("api/[controller]")]
    public class HotspotDataController : Controller
    {
        // GET api/values/5
        [HttpGet("{id}")]
        public JsonResult Get(Guid id)
        {
            var hotspotData = HotspotDataMocks.HotspotData.Where(d => d.HotspotId == id);
            if (hotspotData == null)
                return Json(Enumerable.Empty<HotspotData>());

            return Json(HotspotDataMocks.HotspotData);
        }

        // POST api/values
        [HttpPost]
        public void Post([FromBody]string value)
        {
        }

        // PUT api/values/5
        [HttpPut("{id}")]
        public void Put(int id, [FromBody]string value)
        {
        }

        // DELETE api/values/5
        [HttpDelete("{id}")]
        public void Delete(int id)
        {
        }
    }
}
