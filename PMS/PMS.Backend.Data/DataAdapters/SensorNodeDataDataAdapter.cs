using PMS.Backend.Data.Persistence.Entities;
using PMS.Backend.DomainModel;

namespace PMS.Backend.Data.DataAdapters
{
    public static class SensorNodeDataDataAdapter
    {
        public static SensorNodeData ToSensorNodeData(this SensorNodeDataEntity entity)
        {
            return new SensorNodeData
            {
                Id = entity.Id,
                SensorNodeId = entity.SensorNodeId,
                DateTime = entity.DateTime,
                Pm2_5 = entity.Pm2_5,
                Pm10 = entity.Pm10,
                Temperature = entity.Temperature,
                Humidity = entity.Humidity
            };
        }

        public static SensorNodeDataEntity ToSensorNodeDataEntity(this SensorNodeData sensorNodeData)
        {
            return new SensorNodeDataEntity
            {
                SensorNodeId = sensorNodeData.SensorNodeId,
                DateTime = sensorNodeData.DateTime,
                Pm2_5 = sensorNodeData.Pm2_5,
                Pm10 = sensorNodeData.Pm10,
                Temperature = sensorNodeData.Temperature,
                Humidity = sensorNodeData.Humidity
            };
        }
    }
}
