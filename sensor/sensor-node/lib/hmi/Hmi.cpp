/*
 * Hmi.cpp
 *
 *  Created on: 27.08.2017
 *      Author: nid
 */
#include <LcdKeypad.h>
#include <Battery.h>
#include <Screen.h>
#include <Timer.h>
#include <Hmi.h>

//-----------------------------------------------------------------------------
// LCD Keypad Key Press Detection
//-----------------------------------------------------------------------------
class MyLcdKeypadAdapter : public LcdKeypadAdapter
{
private:
  LcdKeypad* m_lcdKeypad;
  Hmi* m_hmi;
  unsigned char m_value;

public:
  MyLcdKeypadAdapter(LcdKeypad* lcdKeypad, Hmi* hmi)
  : m_lcdKeypad(lcdKeypad)
  , m_hmi(hmi)
  , m_value(7)
  { }

  // Specific handleKeyChanged() method implementation - define your actions here
  void handleKeyChanged(LcdKeypad::Key newKey)
  {
    if ((0 != m_lcdKeypad) && (0 != m_hmi))
    {
      if (LcdKeypad::UP_KEY == newKey)
      {
        m_value++;
      }
      else if (LcdKeypad::DOWN_KEY == newKey)
      {
        m_value--;
      }
      else if (LcdKeypad::SELECT_KEY == newKey)
      {
        m_hmi->switchNext();
      }

      // RGB colored backlight: set according to the current value
      m_lcdKeypad->setBacklight(static_cast<LcdKeypad::LcdBacklightColor>(LcdKeypad::LCDBL_WHITE & m_value));
    }
  }
};

//-----------------------------------------------------------------------------

class ScreenChangeTimerAdapter : public TimerAdapter
{
private:
  Hmi* m_hmi;
public:
  ScreenChangeTimerAdapter(Hmi* hmi)
  : m_hmi(hmi)
  { }

  void timeExpired()
  {
    if (0 != m_hmi)
    {
      m_hmi->switchNext();
    }
  }
};

//-----------------------------------------------------------------------------

Hmi::Hmi()
: m_lcdKeypad(new LcdKeypad())
, m_battery(0)
, m_relHumidity(0.0)
, m_temperature(0.0)
, m_pm10(0.0)
, m_pm25(0.0)
, m_currentScreen(0)
, m_screenChangeTimer(new Timer(new ScreenChangeTimerAdapter(this), Timer::IS_RECURRING, 5000))
{
  if (0 != m_lcdKeypad)
  {
    m_lcdKeypad->attachAdapter(new MyLcdKeypadAdapter(m_lcdKeypad, this));
    m_lcdKeypad->setBackLightOn(true);
  }

  m_currentScreen = new HumTempScreen(this);
  m_currentScreen->setNext(new PmScreen(this));
  // m_currentScreen->next()->setNext(new BattScreen(this));
  // m_currentScreen->next()->next()->setNext(m_currentScreen);
  m_currentScreen->next()->next()->setNext(m_currentScreen);
}

Hmi::~Hmi()
{
  delete m_lcdKeypad;
  m_lcdKeypad = 0;
}

void Hmi::attachBattery(Battery* battery)
{
  m_battery = battery;
}

LcdKeypad* Hmi::lcd()
{
  return m_lcdKeypad;
}

Battery* Hmi::battery()
{
  return m_battery;
}

void Hmi::setRelHumidity(float relHumidity)
{
  m_relHumidity = relHumidity;
  if (0 != m_currentScreen)
  {
    m_currentScreen->updateDisplay();
  }
}

void Hmi::setTemperature(float temperature)
{
  m_temperature = temperature;
  if (0 != m_currentScreen)
  {
    m_currentScreen->updateDisplay();
  }
}

void Hmi::setPm(float pm10, float pm25)
{
  m_pm10 = pm10;
  m_pm25 = pm25;
  if (0 != m_currentScreen)
  {
    m_currentScreen->updateDisplay();
  }
}

float Hmi::getRelHumidity()
{
  return m_relHumidity;
}

float Hmi::getTemperature()
{
  return m_temperature;
}

float Hmi::getPm10()
{
  return m_pm10;
}

float Hmi::getPm25()
{
  return m_pm25;
}

void Hmi::switchNext()
{
  if (0 != m_currentScreen)
  {
    m_currentScreen = m_currentScreen->next();
    m_currentScreen->updateDisplay();
  }
}
