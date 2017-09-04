/*
 * SDS011.h
 *
 *  Created on: 27.08.2017
 *      Author: scan
 */

#ifndef LIB_SENSORS_SDS011_H_
#define LIB_SENSORS_SDS011_H_

#include <Arduino.h>

class PmAdapter
{
public:
  virtual ~PmAdapter() { }
  virtual void notifyPmChanged(float pm10, float pm25) = 0;
};

class SDS011
{
public:
  SDS011(HardwareSerial* serial, PmAdapter* pmAdapter = 0)
  : m_serial(serial)
  , m_readIndex(0)
  , m_data()
  , m_pm10()
  , m_pm25()
  , m_pmAdapter(pmAdapter)
  {  }

  virtual ~SDS011() {}

public:
  /**
   * print all child nodes to console output
   */
  void pollSerialData();

  void init(uint32_t baudrate) { m_serial->begin(baudrate); }

  float getPm10Average();
  float getPm25Average();

private:
  bool validateChecksum();
  void storeToBuffer(float pm10, float pm25);

private:
  HardwareSerial* m_serial;
  uint8_t m_readIndex;
  uint8_t m_data[10];

  static const uint8_t BUFFER_SIZE = 60;  // Buffer for average calculation
  float m_pm10[BUFFER_SIZE];
  float m_pm25[BUFFER_SIZE];

  PmAdapter* m_pmAdapter;
};


#endif /* LIB_SENSORS_SDS011_H_ */
