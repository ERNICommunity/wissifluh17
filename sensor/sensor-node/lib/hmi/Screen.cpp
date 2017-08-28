/*
 * Screen.cpp
 *
 *  Created on: 28.08.2017
 *      Author: nid
 */
#include <LcdKeypad.h>
#include <Hmi.h>
#include <Screen.h>

Screen::Screen(Hmi* hmi)
: m_hmi(hmi)
, m_next(0)
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

//-----------------------------------------------------------------------------

HumTempScreen::HumTempScreen(Hmi* hmi)
: Screen(hmi)
{ }

HumTempScreen::~HumTempScreen()
{ }

void HumTempScreen::updateDisplay()
{
  LcdKeypad* lcd = hmi()->lcd();
  lcd->setCursor(0, 0); // position the cursor at beginning of the first line
  lcd->print("Temp:  ");
  lcd->print(hmi()->getTemperature());
  lcd->setCursor(0, 1); // position the cursor at beginning of the second line
  lcd->print("Humid: ");
  lcd->print(hmi()->getRelHumidity());
}

//-----------------------------------------------------------------------------

PmScreen::PmScreen(Hmi* hmi)
: Screen(hmi)
{ }

PmScreen::~PmScreen()
{ }

void PmScreen::updateDisplay()
{
  LcdKeypad* lcd = hmi()->lcd();
  lcd->setCursor(0, 0); // position the cursor at beginning of the first line
  lcd->print("PM 10:  ");
  lcd->print(hmi()->getPm10());
  lcd->setCursor(0, 1); // position the cursor at beginning of the second line
  lcd->print("PM 2.5: ");
  lcd->print(hmi()->getPm25());
}
