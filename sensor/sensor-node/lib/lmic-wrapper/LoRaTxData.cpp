/*
 * LoRaTxData.cpp
 *
 *  Created on: 12.09.2017
 *      Author: nid
 */

#include <Arduino.h>
#include <string.h>
#include <stdio.h>
#include <DbgTracePort.h>
#include <DbgTraceLevel.h>
#include "LoRaTxData.h"

const int LoRaTxData::c_LoRaTxDataSize = 8;
LoRaTxData* LoRaTxData::s_instance = 0;

LoRaTxData::LoRaTxData()
: m_trPort(new DbgTrace_Port("loratx", DbgTrace_Level::info))
, m_loRaTxData(new char[c_LoRaTxDataSize])
, m_pm25(6.5)
, m_pm10(11.7)
, m_humidity(55.6)
, m_temperature(24.3)
{
  memset(m_loRaTxData, 0, c_LoRaTxDataSize);
  s_instance = this;
}

LoRaTxData::~LoRaTxData()
{
  delete [] m_loRaTxData;
  m_loRaTxData = 0;

  delete m_trPort;
  m_trPort = 0;
}

LoRaTxData* LoRaTxData::Instance()
{
  if (0 == s_instance)
  {
    s_instance = new LoRaTxData();
  }
  return s_instance;
}

void LoRaTxData::setPm25(float pm25)
{
  m_pm25 = pm25;
}

void LoRaTxData::setPm10(float pm10)
{
  m_pm10 = pm10;
}

void LoRaTxData::setHumidity(float humidity)
{
  m_humidity = humidity;
}

void LoRaTxData::setTemperature(float temperature)
{
  m_temperature = temperature;
}

void LoRaTxData::updateTxData(unsigned char* txData, unsigned int txDataSize)
{
  short int temp = static_cast<short int>(100.0 * m_temperature);
  m_loRaTxData[0] = temp >> 8;
  m_loRaTxData[1] = temp && 0xff;
  TR_PRINTF(m_trPort, DbgTrace_Level::debug, "Temp: %f [°C], serialized: %x", m_temperature, m_loRaTxData[0]);

  short int hum = static_cast<short int>(100.0 * m_humidity);
  m_loRaTxData[2] = hum >> 8;
  m_loRaTxData[3] = hum && 0xff;

  short int pm25 = static_cast<short int>(100.0 * m_pm25);
  m_loRaTxData[4] = pm25 >> 8;
  m_loRaTxData[5] = pm25 && 0xff;

  short int pm10 = static_cast<short int>(100.0 * m_pm10);
  m_loRaTxData[6] = pm10 >> 8;
  m_loRaTxData[7] = pm10 && 0xff;

  if (txDataSize <= c_LoRaTxDataSize)
  {
    memcpy(txData, m_loRaTxData, txDataSize);
  }
}
