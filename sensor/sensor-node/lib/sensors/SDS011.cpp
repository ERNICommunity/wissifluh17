/*
 * SD010.cpp
 *
 *  Created on: 27.08.2017
 *      Author: scan
 */

#include <SDS011.h>


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
		  double pm25 = (double)(((int)m_data[3])*256 +((int)m_data[2]))/10;
		  double pm10 = (double)(((int)m_data[5])*256 +((int)m_data[4]))/10;
		  storeToBuffer(pm10, pm25);
		  Serial.print("PM25: ");
		  Serial.print(pm25);
		  Serial.print("        PM10: ");
		  Serial.println(pm10);
		  m_readIndex = 0;
	  }
	  else {
		  Serial.println("Checksum failed");
	  }
  }
}

double SDS011::getPm10Average() {
	// Calculate average
	double average = 0;
	uint8_t i;
	for ( i = 0; i < BUFFER_SIZE; i++) {
		average += m_pm10[i];
	}
	return average;
}
double SDS011::getPm25Average() {
	// Calculate average
	double average = 0;
	uint8_t i;
	for ( i = 0; i < BUFFER_SIZE; i++) {
		average += m_pm25[i];
	}
	return average;
}

bool SDS011::validateChecksum() {
	uint8_t checksum = m_data[2] + m_data[3] + m_data[4] + m_data[5] + m_data[6] + m_data[7];
	return (checksum == m_data[8]);
}

void SDS011::storeToBuffer(double pm10, double pm25) {
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
