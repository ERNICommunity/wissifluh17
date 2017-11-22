/*
 * Screen.h
 *
 *  Created on: 28.08.2017
 *      Author: nid
 */

#ifndef LIB_HMI_SCREEN_H_
#define LIB_HMI_SCREEN_H_

class Hmi;

class Screen
{
protected:
  Screen(Hmi* hmi, const char* name);

public:
  virtual ~Screen();

  Screen* next();
  void setNext(Screen* screen);

  Hmi* hmi();

  virtual void updateDisplay()  = 0;

  const char* name();

private:
  Hmi* m_hmi;
  Screen* m_next;
  const char* m_name;

private: // forbidden default functions
  Screen();                               // default constructor
  Screen& operator = (const Screen& src); // assignment operator
  Screen(const Screen& src);              // copy constructor
};

//-----------------------------------------------------------------------------

class HumTempScreen : public Screen
{
public:
  HumTempScreen(Hmi* hmi);
  virtual ~HumTempScreen();
  void updateDisplay();

private: // forbidden default functions
  HumTempScreen();                                      // default constructor
  HumTempScreen& operator = (const HumTempScreen& src); // assignment operator
  HumTempScreen(const HumTempScreen& src);              // copy constructor
};

//-----------------------------------------------------------------------------

class PmScreen : public Screen
{
public:
  PmScreen(Hmi* hmi);
  virtual ~PmScreen();
  void updateDisplay();

private: // forbidden default functions
  PmScreen();                                 // default constructor
  PmScreen& operator = (const PmScreen& src); // assignment operator
  PmScreen(const PmScreen& src);              // copy constructor
};

//-----------------------------------------------------------------------------

#endif /* LIB_HMI_SCREEN_H_ */
