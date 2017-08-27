using System;
using System.Linq;
using Microsoft.AspNetCore.Mvc;
using PMS.Backend.Mocks;
using PMS.Backend.Contract.Dto;
using PMS.Backend.Implementation;
using PMS.Backend.Mappers;

// For more information on enabling Web API for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace PMS.Backend.Controllers
{
    [Route("api/[controller]")]
    public class SensorNodesController : Controller
    {
        // GET: api/values
        [HttpGet]
        public JsonResult Get()
        {
            var mainService = new MainService();
            var sensorNodes = mainService.GetAllSensorNodes().ToList().Select(x => x.ToSensorNodeDto()).ToList();

            return Json(sensorNodes);
        }

        // GET api/values/5
        [HttpGet("{id}")]
        public JsonResult Get(Guid id)
        {
            var mainService = new MainService();
            var sensorNode = mainService.GetSensorNode(id).ToSensorNodeDto();
            
            return Json(sensorNode);
        }

        // POST api/values
        [HttpPost]
        public void Post([FromBody]SensorNode value)
        {
            var mainService = new MainService();
            mainService.AddSensorNode(value.ToSensorNode());
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
