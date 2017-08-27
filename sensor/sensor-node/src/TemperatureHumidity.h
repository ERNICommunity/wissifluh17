/*
 * TemperatureHumidity.h
 *
 *  Created on: 27.08.2017
 *      Author: nid
 */

#ifndef SRC_TEMPERATUREHUMIDITY_H_
#define SRC_TEMPERATUREHUMIDITY_H_

#include <DbgTracePort.h>
//#include <DbgTraceContext.h>
//#include <DbgTraceOut.h>
//#include <DbgPrintConsole.h>
#include <DbgTraceLevel.h>

//class DbgTrace_Port;
//class DbgTrace_Level;
class DHT_Unified;
class Timer;

class DhtPollTimerAdapter : public TimerAdapter
{
private:
  DbgTrace_Port* m_trPort;
  DHT_Unified* m_dht;

public:
  DhtPollTimerAdapter(DHT_Unified* dht)
  : m_trPort(new DbgTrace_Port("dht", DbgTrace_Level::debug))
  , m_dht(dht)
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
//        if (0 != myLcdKeypad)
//        {
//          myLcdKeypad->setCursor(0, 0);   // position the cursor at beginning of the first line
//          myLcdKeypad->print("Temp:  ");
//          myLcdKeypad->print(event.temperature);
//        }
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
//        if (0 != myLcdKeypad)
//        {
//          myLcdKeypad->setCursor(0, 1);   // position the cursor at beginning of the second line
//          myLcdKeypad->print("Humid: ");
//          myLcdKeypad->print(event.relative_humidity);
//        }
        TR_PRINTF(m_trPort, DbgTrace_Level::debug, "Humidity:    %d.%02d %%",
            static_cast<int>(event.relative_humidity),
            static_cast<int>(event.temperature*100.0)-static_cast<int>(event.relative_humidity)*100);
      }
    }
  }
};

class TemperatureHumidity
{
public:
  TemperatureHumidity();
  virtual ~TemperatureHumidity();

private:
  DHT_Unified* m_dht;
  unsigned long int m_delayMs;
  Timer* m_dhtPollTimer;

private: // forbidden default functions
  TemperatureHumidity& operator = (const TemperatureHumidity& src); // assignment operator
  TemperatureHumidity(const TemperatureHumidity& src);              // copy constructor
};

#endif /* SRC_TEMPERATUREHUMIDITY_H_ */
