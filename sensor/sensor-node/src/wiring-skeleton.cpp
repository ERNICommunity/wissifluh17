/*
 * wiring-skeleton.cpp
 *
 *  Created on: 15.03.2017
 *      Author: niklausd
 */

#include <Arduino.h>

// PlatformIO libraries
#include <SerialCommand.h>    // pio lib 173, lib details see https://github.com/kroimon/Arduino-SerialCommand
#include <Timer.h>            // pio lib 1699, lib details see https://github.com/dniklaus/wiring-timer
#include <Adafruit_Sensor.h>  // pio lib 19, 31, lib details see https://github.com/adafruit/DHT-sensor-library
#include <DHT.h>
#include <DHT_U.h>


// private libraries
#include <LcdKeypad.h>
#include <lmic.h>
#include <DbgCliNode.h>
#include <DbgCliTopic.h>
#include <DbgCliCommand.h>
#include <DbgTracePort.h>
#include <DbgTraceContext.h>
#include <DbgTraceOut.h>
#include <DbgPrintConsole.h>
#include <DbgTraceLevel.h>
#include <AppDebug.h>
#include <ProductDebug.h>
#include <RamUtils.h>
#include <SDS011.h>

#ifndef BUILTIN_LED
#define BUILTIN_LED 13
#endif

SerialCommand* sCmd = 0;
LcdKeypad* myLcdKeypad = 0;
SDS011* pmSensor = 0;

//-----------------------------------------------------------------------------
// DHT22 Sensor
//-----------------------------------------------------------------------------
#define DHTPIN      12        // Pin which is connected to the DHT sensor.
#define DHTTYPE     DHT22     // DHT 22 (AM2302)

DHT_Unified*    dht = 0;
Timer* dhtPollTimer = 0;

unsigned long int delayMS = 2500;

class DhtPollTimerAdapter : public TimerAdapter
{
private:
  DbgTrace_Port* m_trPort;

public:
  DhtPollTimerAdapter()
  : m_trPort(new DbgTrace_Port("dht", DbgTrace_Level::debug))
  { }

  void timeExpired()
  {
    if (0 != dht)
    {
      sensors_event_t event;

      // Get temperature event and print its value.
      dht->temperature().getEvent(&event);
      if (isnan(event.temperature))
      {
        TR_PRINTF(m_trPort, DbgTrace_Level::error, "Error reading temperature!");
      }
      else
      {
        if (0 != myLcdKeypad)
        {
          myLcdKeypad->setCursor(0, 0);   // position the cursor at beginning of the first line
          myLcdKeypad->print("Temp:  ");
          myLcdKeypad->print(event.temperature);
        }
        TR_PRINTF(m_trPort, DbgTrace_Level::debug, "Temperature: %d.%02d *C",
            static_cast<int>(event.temperature),
            static_cast<int>(event.temperature*100.0)-static_cast<int>(event.temperature)*100);
      }

      // Get humidity event and print its value.
      dht->humidity().getEvent(&event);
      if (isnan(event.relative_humidity))
      {
        TR_PRINTF(m_trPort, DbgTrace_Level::error, "Error reading humidity!");
      }
      else
      {
        if (0 != myLcdKeypad)
        {
          myLcdKeypad->setCursor(0, 1);   // position the cursor at beginning of the second line
          myLcdKeypad->print("Humid: ");
          myLcdKeypad->print(event.relative_humidity);

        }
        TR_PRINTF(m_trPort, DbgTrace_Level::debug, "Humidity:    %d.%02d %%",
            static_cast<int>(event.relative_humidity),
            static_cast<int>(event.temperature*100.0)-static_cast<int>(event.relative_humidity)*100);
      }
    }
  }
};

//-----------------------------------------------------------------------------
// LCD Keypad Key Press Detection
//-----------------------------------------------------------------------------
class MyLcdKeypadAdapter : public LcdKeypadAdapter
{
private:
  LcdKeypad* m_lcdKeypad;
  unsigned char m_value;
public:
  MyLcdKeypadAdapter(LcdKeypad* lcdKeypad)
  : m_lcdKeypad(lcdKeypad)
  , m_value(7)
  { }

  // Specific handleKeyChanged() method implementation - define your actions here
  void handleKeyChanged(LcdKeypad::Key newKey)
  {
    if (0 != m_lcdKeypad)
    {
      if (LcdKeypad::UP_KEY == newKey)
      {
        m_value++;
      }
      else if (LcdKeypad::DOWN_KEY == newKey)
      {
        m_value--;
      }

      // RGB colored backlight: set according to the current value
      // monochrome backlight: set backlight on or off according to the current value
      m_lcdKeypad->setBacklight(static_cast<LcdKeypad::LcdBacklightColor>(LcdKeypad::LCDBL_WHITE & m_value));
    }
  }
};


//-----------------------------------------------------------------------------

void setup()
{
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, 0);

  pmSensor = new SDS011(&Serial1);
  pmSensor->init(9600);

  setupProdDebugEnv();

  dht = new DHT_Unified(DHTPIN, DHTTYPE);
  dht->begin();

  // DHT22: Set delay between sensor readings based on sensor details.
  sensor_t sensor;
  dht->temperature().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
  dhtPollTimer = new Timer(new DhtPollTimerAdapter(), Timer::IS_RECURRING, delayMS);

  myLcdKeypad = new LcdKeypad();  // instatiate an object of the LcdKeypad class, using default parameters
  myLcdKeypad->attachAdapter(new MyLcdKeypadAdapter(myLcdKeypad));
  myLcdKeypad->setBackLightOn(true);
}

void loop()
{
  if (0 != sCmd)
  {
    sCmd->readSerial();     // process serial commands
  }

  pmSensor->pollSerialData();

  yield();                  // process Timers
}
