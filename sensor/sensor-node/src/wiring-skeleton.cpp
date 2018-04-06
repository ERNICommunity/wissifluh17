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
#include <LoRaTxData.h>
#include <MyTemperatureHumidityAdapter.h>
#include <MyPmAdapter.h>
#include <LmicWrapper.h>
#include <Battery.h>
#include <MyBatteryAdapter.h>

#define HMI 1

#ifndef BUILTIN_LED
#define BUILTIN_LED 13
#endif

SerialCommand* sCmd = 0;
SDS011* pmSensor = 0;
TemperatureHumidity* temperatureHumidity = 0;
Hmi* hmi = 0;
Battery* battery = 0;

//-----------------------------------------------------------------------------

void setup()
{
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, 0);

  delay(5000);

  setupProdDebugEnv();

#if HMI
  hmi = new Hmi();
#endif

  //-----------------------------------------------------------------------------
  // Battery Voltage Surveillance
  //-----------------------------------------------------------------------------
  BatteryThresholdConfig battCfg = { 3.6, // BATT_WARN_THRSHD [V]
                                     3.4, // BATT_STOP_THRSHD [V]
                                     3.2, // BATT_SHUT_THRSHD [V]
                                     0.1  // BATT_HYST        [V]
                                    };
  battery = new Battery(0, battCfg);
  BatteryAdapter* mBatAdapter = new MyBatteryAdapter(battery, hmi);
  battery->attachAdapter(mBatAdapter);

  pmSensor = new SDS011(&Serial1, new MyPmAdapter(hmi, LoRaTxData::Instance()));
  pmSensor->init(9600);

  temperatureHumidity = new TemperatureHumidity(new MyTemperatureHumidityAdapter(hmi, LoRaTxData::Instance()));

  lmicSetup();
}

//-----------------------------------------------------------------------------

void loop()
{
  if (0 != sCmd)
  {
    sCmd->readSerial();     // process serial commands
  }
  pmSensor->pollSerialData();
//  lmicLoop();
  yield();                  // process Timers
}
