/*
 * TemperatureHumidity.cpp
 *
 *  Created on: 27.08.2017
 *      Author: nid
 */

#include <Adafruit_Sensor.h>  // pio lib 19, 31, lib details see https://github.com/adafruit/DHT-sensor-library
#include <DHT.h>
#include <DHT_U.h>
#include <Timer.h>
#include <DbgTracePort.h>
#include <DbgTraceLevel.h>
#include <TemperatureHumidity.h>

#define DHTPIN      12        // Pin which is connected to the DHT sensor.
#define DHTTYPE     DHT22     // DHT 22 (AM2302)

class DhtPollTimerAdapter : public TimerAdapter
{
private:
  DbgTrace_Port* m_trPort;
  DHT_Unified* m_dht;
  TemperatureHumidity* m_temperatureHumidity;

public:
  DhtPollTimerAdapter(DHT_Unified* dht, TemperatureHumidity* temperatureHumidity)
  : m_trPort(new DbgTrace_Port("dht", DbgTrace_Level::critical))
  , m_dht(dht)
  , m_temperatureHumidity(temperatureHumidity)
  { }

  void timeExpired()
  {
    if (0 != m_dht)
    {
      sensors_event_t event;

      // Get temperature event and print its value.
      m_dht->temperature().getEvent(&event);
      if (isnan(event.temperature))
      {
        TR_PRINTF(m_trPort, DbgTrace_Level::error, "Error reading temperature!");
      }
      else
      {
        if (0 != m_temperatureHumidity)
        {
          m_temperatureHumidity->setTemperature(event.temperature);
        }
        TR_PRINTF(m_trPort, DbgTrace_Level::debug, "Temperature: %d.%02d *C",
            static_cast<int>(event.temperature),
            static_cast<int>(event.temperature*100.0)-static_cast<int>(event.temperature)*100);
      }

      // Get humidity event and print its value.
      m_dht->humidity().getEvent(&event);
      if (isnan(event.relative_humidity))
      {
        TR_PRINTF(m_trPort, DbgTrace_Level::error, "Error reading humidity!");
      }
      else
      {
        if (0 != m_temperatureHumidity)
        {
          m_temperatureHumidity->setRelHumidity(event.relative_humidity);
        }
        TR_PRINTF(m_trPort, DbgTrace_Level::debug, "Humidity:    %d.%02d %%",
            static_cast<int>(event.relative_humidity),
            static_cast<int>(event.temperature*100.0)-static_cast<int>(event.relative_humidity)*100);
      }
    }
  }
};

//-----------------------------------------------------------------------------

TemperatureHumidity::TemperatureHumidity(TemperatureHumidityAdapter* temperatureHumidityAdapter)
: m_dht(new DHT_Unified(DHTPIN, DHTTYPE))
, m_delayMs(2500)
, m_dhtPollTimer(new Timer(new DhtPollTimerAdapter(m_dht, this), Timer::IS_RECURRING))
, m_relHumidity(0.0)
, m_temperature(0.0)
, m_temperatureHumidityAdapter(temperatureHumidityAdapter)
{
  m_dht->begin();

  // DHT22: Set delay between sensor readings based on sensor details.
  sensor_t sensor;
  m_dht->temperature().getSensor(&sensor);
  m_delayMs = sensor.min_delay / 1000;
  m_dhtPollTimer->startTimer(m_delayMs);
}

TemperatureHumidity::~TemperatureHumidity()
{
  delete m_dhtPollTimer->adapter();
  m_dhtPollTimer->attachAdapter(0);

  delete m_dhtPollTimer;
  m_dhtPollTimer = 0;

  delete m_dht;
  m_dht = 0;
}

void TemperatureHumidity::setRelHumidity(float relHumidity)
{
  m_relHumidity = relHumidity;
  if (0 != m_temperatureHumidityAdapter)
  {
    m_temperatureHumidityAdapter->notifyRelHumidityChanged(relHumidity);
  }
}

void TemperatureHumidity::setTemperature(float temperature)
{
  m_temperature = temperature;
  if (0 != m_temperatureHumidityAdapter)
  {
    m_temperatureHumidityAdapter->notifyTemperatureChanged(temperature);
  }
}

float TemperatureHumidity::getRelHumidity()
{
  return m_relHumidity;
}

float TemperatureHumidity::getTemperature()
{
  return m_temperature;
}

