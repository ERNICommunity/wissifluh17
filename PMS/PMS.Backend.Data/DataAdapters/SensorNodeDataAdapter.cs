using PMS.Backend.Data.Persistence.Entities;
using PMS.Backend.DomainModel;

namespace PMS.Backend.Data.DataAdapters
{
    public static class SensorNodeDataAdapter
    {
        public static SensorNode ToSensorNode(this SensorNodeEntity entity)
        {
            return new SensorNode
            {
                Id = entity.Id,
                Name = entity.Name,
                Latitude = entity.Latitude,
                Longitude = entity.Longitude
            };
        }

        public static SensorNodeEntity ToSensorNodeEntity(this SensorNode sensorNode)
        {
            return new SensorNodeEntity
            {
                Id = sensorNode.Id,
                Name = sensorNode.Name,
                Latitude = sensorNode.Latitude,
                Longitude = sensorNode.Longitude
            };
        }
    }
}
