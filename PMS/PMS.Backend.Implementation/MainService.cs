using PMS.Backend.Data.DataAdapters;
using PMS.Backend.Data.Models;
using PMS.Backend.DomainModel;
using System;
using System.Collections.Generic;
using System.Linq;

namespace PMS.Backend.Implementation
{
    public class MainService : IMainService
    {
        public void AddSensorNode(SensorNode sensorNode)
        {
            using (var context = new PmsDataContext())
            {
                context.SensorNode.Add(sensorNode.ToSensorNodeEntity());
                context.SaveChanges();
            }
        }

        public void AddSensorNodeData(SensorNodeData sensorNodeData)
        {
            using (var context = new PmsDataContext())
            {
                context.SensorNodeData.Add(sensorNodeData.ToSensorNodeDataEntity());
                context.SaveChanges();
            }
        }

        public IEnumerable<SensorNode> GetAllSensorNodes()
        {
            using (var context = new PmsDataContext())
            {
                return context.SensorNode
                    .Select(x => x.ToSensorNode())
                    .ToList();
            }
        }

        public SensorNode GetSensorNode(Guid sensorNodeId)
        {
            using (var context = new PmsDataContext())
            {
                return context.SensorNode
                    .SingleOrDefault(x => x.Id == sensorNodeId)
                    .ToSensorNode();
            }
        }

        public IEnumerable<SensorNodeData> GetSensorNodeData(Guid sensorNodeId)
        {
            using (var context = new PmsDataContext())
            {
                return context.SensorNodeData
                    .Where(x => x.SensorNodeId == sensorNodeId)
                    .Select(x => x.ToSensorNodeData())
                    .ToList();
            }
        }
    }
}
