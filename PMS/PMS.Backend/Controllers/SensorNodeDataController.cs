﻿using System;
using System.Linq;
using Microsoft.AspNetCore.Mvc;
using PMS.Backend.Contract.Dto;
using PMS.Backend.Implementation;
using PMS.Backend.Mappers;

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
            var mainService = new MainService();
            var sensorNodeData = mainService.GetSensorNodeData(id).ToList().Select(x => x.ToSensorNodeDataDto()).ToList();

            return Json(sensorNodeData);
        }

        // POST api/values
        [HttpPost]
        public void Post([FromBody]SensorNodeData value)
        {
            var mainService = new MainService();
            mainService.AddSensorNodeData(value.ToSensorNodeData());
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
