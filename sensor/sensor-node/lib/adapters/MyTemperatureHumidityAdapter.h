/*
 * MyTemperatureHumidityAdapter.h
 *
 *  Created on: 29.08.2017
 *      Author: nid
 */

#ifndef LIB_ADAPTERS_MYTEMPERATUREHUMIDITYADAPTER_H_
#define LIB_ADAPTERS_MYTEMPERATUREHUMIDITYADAPTER_H_

#include <TemperatureHumidity.h>

class Hmi;
class LoRaTxData;

class MyTemperatureHumidityAdapter : public TemperatureHumidityAdapter
{
public:
  MyTemperatureHumidityAdapter(Hmi* hmi, LoRaTxData* loRaTxData);
  virtual ~MyTemperatureHumidityAdapter();

  void notifyTemperatureChanged(float temperature);
  void notifyRelHumidityChanged(float relHumidity);

private:
  Hmi* m_hmi;
  LoRaTxData* m_loRaTxData;

private: // forbidden default functions
  MyTemperatureHumidityAdapter();                                                     // default constructor
  MyTemperatureHumidityAdapter& operator = (const MyTemperatureHumidityAdapter& src); // assignment operator
  MyTemperatureHumidityAdapter(const MyTemperatureHumidityAdapter& src);              // copy constructor
};

#endif /* LIB_ADAPTERS_MYTEMPERATUREHUMIDITYADAPTER_H_ */
