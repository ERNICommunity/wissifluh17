/*
 * TemperatureHumidity.h
 *
 *  Created on: 27.08.2017
 *      Author: nid
 */

#ifndef SRC_TEMPERATUREHUMIDITY_H_
#define SRC_TEMPERATUREHUMIDITY_H_

class DHT_Unified;
class Timer;

//-----------------------------------------------------------------------------

class TemperatureHumidityAdapter
{
public:
  virtual void notifyTemperatureChanged(float temperature) = 0;
  virtual void notifyRelHumidityChanged(float relHumidity) = 0;
  virtual ~TemperatureHumidityAdapter() { }
};

//-----------------------------------------------------------------------------

class TemperatureHumidity
{
  friend class DhtPollTimerAdapter;

public:
  TemperatureHumidity(TemperatureHumidityAdapter* temperatureHumidityAdapter = 0);
  virtual ~TemperatureHumidity();

  float getRelHumidity();
  float getTemperature();

protected:
  void setRelHumidity(float relHumidity);
  void setTemperature(float temperature);

private:
  DHT_Unified* m_dht;
  unsigned long int m_delayMs;
  Timer* m_dhtPollTimer;
  float m_relHumidity;
  float m_temperature;
  TemperatureHumidityAdapter* m_temperatureHumidityAdapter;

private: // forbidden default functions
  TemperatureHumidity& operator = (const TemperatureHumidity& src); // assignment operator
  TemperatureHumidity(const TemperatureHumidity& src);              // copy constructor
};

#endif /* SRC_TEMPERATUREHUMIDITY_H_ */
