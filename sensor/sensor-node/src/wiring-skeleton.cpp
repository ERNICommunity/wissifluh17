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

#define HMI 0

#ifndef BUILTIN_LED
#define BUILTIN_LED 13
#endif

SerialCommand* sCmd = 0;
SDS011* pmSensor = 0;
TemperatureHumidity* temperatureHumidity = 0;
Hmi* hmi = 0;

//-----------------------------------------------------------------------------

class MyTemperatureHumidityAdapter : public TemperatureHumidityAdapter
{
private:
  Hmi* m_hmi;

public:
  MyTemperatureHumidityAdapter(Hmi* hmi)
  : m_hmi(hmi)
  { }

  void notifyTemperatureChanged(float temperature)
  {
    if (0 != m_hmi)
    {
      m_hmi->setTemperature(temperature);
    }
  }

  void notifyRelHumidityChanged(float relHumidity)
  {
    if (0 != m_hmi)
    {
      m_hmi->setRelHumidity(relHumidity);
    }
  }
};

//-----------------------------------------------------------------------------

class MyPmAdapter : public PmAdapter
{
private:
  Hmi* m_hmi;

public:
  MyPmAdapter(Hmi* hmi)
  : m_hmi(hmi)
  { }

  void notifyPmChanged(float pm10, float pm25)
  {
    if (0 != m_hmi)
    {
      m_hmi->setPm(pm10, pm25);
    }
  }
};

//-----------------------------------------------------------------------------

void setup()
{
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, 0);

  setupProdDebugEnv();

#if HMI
  hmi = new Hmi();
#endif

  pmSensor = new SDS011(&Serial1, new MyPmAdapter(hmi));
  pmSensor->init(9600);

  temperatureHumidity = new TemperatureHumidity(new MyTemperatureHumidityAdapter(hmi));
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
