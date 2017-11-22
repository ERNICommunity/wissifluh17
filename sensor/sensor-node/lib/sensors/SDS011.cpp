/*
 * SD010.cpp
 *
 *  Created on: 27.08.2017
 *      Author: scan
 */

#include <DbgTracePort.h>
#include <DbgTraceLevel.h>
#include <SDS011.h>

SDS011::SDS011(HardwareSerial* serial, PmAdapter* pmAdapter)
: m_serial(serial)
, m_readIndex(0)
, m_data()
, m_pm10()
, m_pm25()
, m_pmAdapter(pmAdapter)
, m_trPort(new DbgTrace_Port("pm", DbgTrace_Level::info))
{  }

SDS011::~SDS011() { }

void SDS011::pollSerialData() {
  if (m_serial->available())
  {
	  uint8_t value = (uint8_t)m_serial->read();
	  if (! (m_readIndex == 0 && value != 170))
	  {
		  // first value must be always 170, otherwise skip value
		  m_data[m_readIndex] = value;
		  m_readIndex++;
	  }
  }
  if (m_readIndex == 10)
  {
	  if (validateChecksum()) {
		  float pm25 = (float)(((int)m_data[3])*256 +((int)m_data[2]))/10;
		  float pm10 = (float)(((int)m_data[5])*256 +((int)m_data[4]))/10;
		  storeToBuffer(pm10, pm25);
		  TR_PRINTF(m_trPort, DbgTrace_Level::debug, "PM25: %f, PM10: %f", pm25, pm10);
		  m_readIndex = 0;
	  }
	  else {
		  Serial.println("Checksum failed");
	  }
  }
}

float SDS011::getPm10Average() {
	// Calculate average
	float average = 0.0f;
	uint8_t i;
	for ( i = 0; i < BUFFER_SIZE; i++) {
		average += m_pm10[i];
	}
	return average/BUFFER_SIZE;
}
float SDS011::getPm25Average() {
	// Calculate average
	float average = 0.0f;
	uint8_t i;
	for ( i = 0; i < BUFFER_SIZE; i++) {
		average += m_pm25[i];
	}
	return average/BUFFER_SIZE;
}

bool SDS011::validateChecksum() {
	uint8_t checksum = m_data[2] + m_data[3] + m_data[4] + m_data[5] + m_data[6] + m_data[7];
	return (checksum == m_data[8]);
}

void SDS011::storeToBuffer(float pm10, float pm25) {
	static uint8_t bufferIndex = 0;
	m_pm10[bufferIndex] = pm10;
	m_pm25[bufferIndex] = pm25;
	bufferIndex++;
	if (bufferIndex >= BUFFER_SIZE) {
		bufferIndex = 0;
	}
	if (0 != m_pmAdapter)
	{
	  m_pmAdapter->notifyPmChanged(pm10, pm25);
	}
}
