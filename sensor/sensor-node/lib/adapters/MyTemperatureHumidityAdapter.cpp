/*
 * MyTemperatureHumidityAdapter.cpp
 *
 *  Created on: 29.08.2017
 *      Author: nid
 */

#include <Hmi.h>
#include <LoRaTxData.h>
#include <MyTemperatureHumidityAdapter.h>

MyTemperatureHumidityAdapter::MyTemperatureHumidityAdapter(Hmi* hmi, LoRaTxData* loRaTxData)
: m_hmi(hmi)
, m_loRaTxData(loRaTxData)
{ }

MyTemperatureHumidityAdapter::~MyTemperatureHumidityAdapter()
{ }

void MyTemperatureHumidityAdapter::notifyTemperatureChanged(float temperature)
{
  if (0 != m_loRaTxData)
  {
    m_loRaTxData->setTemperature(temperature);
  }
  if (0 != m_hmi)
  {
    m_hmi->setTemperature(temperature);
  }
}

void MyTemperatureHumidityAdapter::notifyRelHumidityChanged(float relHumidity)
{
  if (0 != m_loRaTxData)
  {
    m_loRaTxData->setHumidity(relHumidity);
  }
  if (0 != m_hmi)
  {
    m_hmi->setRelHumidity(relHumidity);
  }
}
