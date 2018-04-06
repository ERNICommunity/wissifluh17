/*
 * MyBatteryAdapter.h
 *
 *  Created on: 15.03.2018
 *      Author: niklaudi
 */

#ifndef LIB_ADAPTERS_MYBATTERYADAPTER_H_
#define LIB_ADAPTERS_MYBATTERYADAPTER_H_

#include <Battery.h>

class Hmi;

class MyBatteryAdapter: public BatteryAdapter
{
private:
  Battery* m_battery;
  Hmi* m_hmi;

public:
  MyBatteryAdapter(Battery* battery, Hmi* hmi);
	virtual ~MyBatteryAdapter();

  float readBattVoltageSenseFactor();
  unsigned int readRawBattSenseValue();

  void notifyBattVoltageOk()                      { notifyAnyChange(); }
  void notifyBattVoltageBelowWarnThreshold()      { notifyAnyChange(); }
  void notifyBattVoltageBelowStopThreshold()      { notifyAnyChange(); }
  void notifyBattVoltageBelowShutdownThreshold()  { notifyAnyChange(); }

private:
  void notifyAnyChange();

private: // forbidden default functions
	MyBatteryAdapter();                                         // default constructor
	MyBatteryAdapter& operator = (const MyBatteryAdapter& src); // assignment operator
	MyBatteryAdapter(const MyBatteryAdapter& src);              // copy constructor
};

#endif /* LIB_ADAPTERS_MYBATTERYADAPTER_H_ */
