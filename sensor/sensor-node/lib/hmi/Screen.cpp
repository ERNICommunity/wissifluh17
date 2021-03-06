/*
 * Screen.cpp
 *
 *  Created on: 28.08.2017
 *      Author: nid
 */
#include <Arduino.h>
#include <LcdKeypad.h>
#include <Battery.h>
#include <Hmi.h>
#include <Screen.h>

Screen::Screen(Hmi* hmi, const char* name)
: m_hmi(hmi)
, m_next(0)
, m_name(name)
{ }

Screen::~Screen()
{ }

Screen* Screen::next()
{
  return m_next;
}

void Screen::setNext(Screen* screen)
{
  m_next = screen;
}

Hmi* Screen::hmi()
{
  return m_hmi;
}

const char* Screen::name()
{
  return m_name;
}

//-----------------------------------------------------------------------------

HumTempScreen::HumTempScreen(Hmi* hmi)
: Screen(hmi, "TempScreen")
{ }

HumTempScreen::~HumTempScreen()
{ }

void HumTempScreen::updateDisplay()
{
  LcdKeypad* lcd = hmi()->lcd();
  lcd->setCursor(0, 0); // position the cursor at beginning of the first line
  lcd->print("Temp:  ");
  lcd->print(hmi()->getTemperature());
  lcd->print(" *C ");
  lcd->setCursor(0, 1); // position the cursor at beginning of the second line
  lcd->print("Humid: ");
  lcd->print(hmi()->getRelHumidity());
  lcd->print(" %  ");
}

//-----------------------------------------------------------------------------

PmScreen::PmScreen(Hmi* hmi)
: Screen(hmi, "PmScreen")
{ }

PmScreen::~PmScreen()
{ }

void PmScreen::updateDisplay()
{
  LcdKeypad* lcd = hmi()->lcd();
  lcd->setCursor(0, 0); // position the cursor at beginning of the first line
  lcd->print("PM10: ");
  lcd->print(hmi()->getPm10());
  lcd->print("ug/m3");
  lcd->setCursor(0, 1); // position the cursor at beginning of the second line
  lcd->print("PM2.5:");
  lcd->print(hmi()->getPm25());
  lcd->print("ug/m3");
}

//-----------------------------------------------------------------------------

BattScreen::BattScreen(Hmi* hmi)
: Screen(hmi, "BattScreen")
{ }

BattScreen::~BattScreen()
{ }

void BattScreen::updateDisplay()
{
  LcdKeypad* lcd = hmi()->lcd();
  Battery* batt  = hmi()->battery();

  lcd->setCursor(0, 0); // position the cursor at beginning of the first line
  lcd->print("Batt: ");

  if (0 != batt)
  {
    lcd->print(batt->getBatteryVoltage());
    Serial.print("Batt: ");
    Serial.print(batt->getBatteryVoltage());
    Serial.println("V");
    lcd->print("V");
    lcd->setCursor(0, 1); // position the cursor at beginning of the second line
    lcd->print("state: ");
    lcd->print(batt->getCurrentStateName());
  }
  else
  {
    lcd->setCursor(0, 1); // position the cursor at beginning of the second line
    lcd->print("  no data available");
  }
}
