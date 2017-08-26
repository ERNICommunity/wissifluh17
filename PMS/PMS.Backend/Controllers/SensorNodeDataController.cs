using System;
using System.Linq;
using Microsoft.AspNetCore.Mvc;
using PMS.Backend.Mocks;
using PMS.Backend.Contract.Dto;

// For more information on enabling Web API for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace PMS.Backend.Controllers
{
    [Route("api/[controller]")]
    public class SensorNodeDataController : Controller
    {
        // GET api/values/5
        [HttpGet("{id}")]
        public JsonResult Get(Guid id)
        {
            var sensorNodeData = SensorNodeDataMocks.SensorNodeData.Where(d => d.HotspotId == id);
            if (sensorNodeData == null)
                return Json(Enumerable.Empty<SensorNodeData>());

            return Json(SensorNodeDataMocks.SensorNodeData);
        }

        // POST api/values
        [HttpPost]
        public void Post([FromBody]SensorNodeData value)
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
