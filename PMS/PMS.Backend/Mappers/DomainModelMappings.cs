namespace PMS.Backend.Mappers
{
    public static class DomainModelMappings
    {
        public static DomainModel.SensorNode ToSensorNode(this Contract.Dto.SensorNode sensorNode)
        {
            return new DomainModel.SensorNode
            {
                Id = sensorNode.Id,
                Name = sensorNode.Name,
                Latitude = sensorNode.Latitude,
                Longitude = sensorNode.Longitude,
            };
        }

        public static DomainModel.SensorNodeData ToSensorNodeData(this Contract.Dto.SensorNodeData sensorNodeData)
        {
            return new DomainModel.SensorNodeData
            {
                Id = sensorNodeData.Id,
                SensorNodeId = sensorNodeData.SensorNodeId,
                DateTime = sensorNodeData.DateTime,
                Pm2_5 = sensorNodeData.Pm2_5,
                Pm10 = sensorNodeData.Pm10,
                Temperature = sensorNodeData.Temperature,
                Humidity = sensorNodeData.Humidity,
            };
        }

        public static Contract.Dto.SensorNode ToSensorNodeDto(this DomainModel.SensorNode sensorNode)
        {
            return new Contract.Dto.SensorNode
            {
                Id = sensorNode.Id,
                Name = sensorNode.Name,
                Latitude = sensorNode.Latitude,
                Longitude = sensorNode.Longitude,
            };
        }

        public static Contract.Dto.SensorNodeData ToSensorNodeDataDto(this DomainModel.SensorNodeData sensorNodeData)
        {
            return new Contract.Dto.SensorNodeData
            {
                Id = sensorNodeData.Id,
                SensorNodeId = sensorNodeData.SensorNodeId,
                DateTime = sensorNodeData.DateTime,
                Pm2_5 = sensorNodeData.Pm2_5,
                Pm10 = sensorNodeData.Pm10,
                Temperature = sensorNodeData.Temperature,
                Humidity = sensorNodeData.Humidity,
            };
        }
    }
}
