/*
 * Hmi.cpp
 *
 *  Created on: 27.08.2017
 *      Author: nid
 */

#include <LcdKeypad.h>
#include <Hmi.h>

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
      m_lcdKeypad->setBacklight(static_cast<LcdKeypad::LcdBacklightColor>(LcdKeypad::LCDBL_WHITE & m_value));
    }
  }
};

Hmi::Hmi()
: m_lcdKeypad(new LcdKeypad())
{
  m_lcdKeypad->attachAdapter(new MyLcdKeypadAdapter(m_lcdKeypad));
  m_lcdKeypad->setBackLightOn(true);
}

Hmi::~Hmi()
{
  delete m_lcdKeypad;
  m_lcdKeypad = 0;
}

void Hmi::updateDisplay(float relHumidity, float temperature)
{
  m_lcdKeypad->setCursor(0, 0); // position the cursor at beginning of the first line
  m_lcdKeypad->print("Temp:  ");
  m_lcdKeypad->print(temperature);
  m_lcdKeypad->setCursor(0, 1); // position the cursor at beginning of the second line
  m_lcdKeypad->print("Humid: ");
  m_lcdKeypad->print(relHumidity);
}
