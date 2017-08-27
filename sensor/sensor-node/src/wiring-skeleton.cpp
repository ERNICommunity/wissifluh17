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
#include <TemperatureHumidity.h>
#include <Hmi.h>

#ifndef BUILTIN_LED
#define BUILTIN_LED 13
#endif

SerialCommand* sCmd = 0;
SDS011* pmSensor = 0;
TemperatureHumidity* temperatureHumidity = 0;
Hmi* hmi = 0;

class MyTemperatureHumidityAdapter : public TemperatureHumidityAdapter
{
private:
  Hmi* m_hmi;
  TemperatureHumidity* m_temperatureHumidity;

public:
  MyTemperatureHumidityAdapter(Hmi* hmi)
  : m_hmi(hmi)
  , m_temperatureHumidity(0)
  { }

  void attachTemeperatureHumidity(TemperatureHumidity* temperatureHumidity)
  {
    m_temperatureHumidity = temperatureHumidity;
  }

  void notifyValueChanged()
  {
    if ((0 != m_hmi) && (0 != m_temperatureHumidity))
    {
      m_hmi->updateDisplay(m_temperatureHumidity->getTemperature(), m_temperatureHumidity->getRelHumidity());
    }
  }
};

void setup()
{
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, 0);

  pmSensor = new SDS011(&Serial1);
  pmSensor->init(9600);

  setupProdDebugEnv();

  hmi = new Hmi();
  MyTemperatureHumidityAdapter* temperatureHumidityAdapter = new MyTemperatureHumidityAdapter(hmi);
  temperatureHumidity = new TemperatureHumidity(temperatureHumidityAdapter);
  temperatureHumidityAdapter->attachTemeperatureHumidity(temperatureHumidity);
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
