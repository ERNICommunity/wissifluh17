using PMS.Backend.DomainModel;
using System;
using System.Collections.Generic;

namespace PMS.Backend.Implementation
{
    public interface IMainService
    {
        void AddSensorNode(SensorNode sensorNode);
        void AddSensorNodeData(SensorNodeData sensorNodeData);
        IEnumerable<SensorNode> GetAllSensorNodes();
        SensorNode GetSensorNode(Guid sensorNodeId);
        IEnumerable<SensorNodeData> GetSensorNodeData(Guid sensorNodeId);
    }
}
