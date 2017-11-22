/*
 * LoRaTxData.h
 *
 *  Created on: 12.09.2017
 *      Author: nid
 */

#ifndef LIB_LMIC_WRAPPER_LORATXDATA_H_
#define LIB_LMIC_WRAPPER_LORATXDATA_H_

class DbgTrace_Port;

class LoRaTxData
{
private:
  LoRaTxData();
public:
  virtual ~LoRaTxData();

  void setPm25(float pm25);
  void setPm10(float pm10);
  void setHumidity(float humidity);
  void setTemperature(float temperature);

  void updateTxData(unsigned char* txData, unsigned int txDataSize);

  static LoRaTxData* Instance();

  static const int c_LoRaTxDataSize;

private:
  DbgTrace_Port* m_trPort;
  static LoRaTxData* s_instance;
  char* m_loRaTxData;
  float m_pm25;
  float m_pm10;
  float m_humidity;
  float m_temperature;

private:  // forbidden default functions
  LoRaTxData& operator=(const LoRaTxData& src); // assignment operator
  LoRaTxData(const LoRaTxData& src);            // copy constructor
};

#endif /* LIB_LMIC_WRAPPER_LORATXDATA_H_ */
