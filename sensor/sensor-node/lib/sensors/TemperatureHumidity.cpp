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
#include <TemperatureHumidity.h>

#define DHTPIN      12        // Pin which is connected to the DHT sensor.
#define DHTTYPE     DHT22     // DHT 22 (AM2302)

TemperatureHumidity::TemperatureHumidity()
: m_dht(new DHT_Unified(DHTPIN, DHTTYPE))
, m_delayMs(2500)
, m_dhtPollTimer(new Timer(new DhtPollTimerAdapter(m_dht), Timer::IS_RECURRING))
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

