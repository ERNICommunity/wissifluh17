/*
 * MyBatteryAdapter.cpp
 *
 *  Created on: 15.03.2018
 *      Author: niklaudi
 */

#include <Arduino.h>
#include <Hmi.h>
#include <MyBatteryAdapter.h>

MyBatteryAdapter::MyBatteryAdapter(Battery* battery, Hmi* hmi)
: m_battery(battery)
, m_hmi(hmi)
{
  if (0 != hmi)
  {
    hmi->attachBattery(battery);
  }
}

MyBatteryAdapter::~MyBatteryAdapter()
{ }

float MyBatteryAdapter::readBattVoltageSenseFactor()
{
  return 2.0;
}

unsigned int MyBatteryAdapter::readRawBattSenseValue()
{
  #define VBATPIN A7
  unsigned int rawBattSenseValue = analogRead(VBATPIN);
  return rawBattSenseValue;
}

void MyBatteryAdapter::notifyAnyChange()
{
  if (0 != m_battery)
  {
    m_battery->getBatteryVoltage();
    m_battery->isBattVoltageOk();
  }
}
