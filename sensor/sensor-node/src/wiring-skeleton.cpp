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

#ifndef BUILTIN_LED
#define BUILTIN_LED 13
#endif

SerialCommand* sCmd = 0;
LcdKeypad* myLcdKeypad = 0;
SDS011* pmSensor = 0;
TemperatureHumidity* temperatureHumidity = 0;

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

  temperatureHumidity = new TemperatureHumidity();

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
