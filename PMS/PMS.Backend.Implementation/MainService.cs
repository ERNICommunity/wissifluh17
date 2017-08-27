using PMS.Backend.Data.DataAdapters;
using PMS.Backend.Data.Models;
using PMS.Backend.DomainModel;

namespace PMS.Backend.Implementation
{
    public class MainService
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
    }
}
