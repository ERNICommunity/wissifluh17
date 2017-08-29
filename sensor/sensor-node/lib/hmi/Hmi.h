/*
 * Hmi.h
 *
 *  Created on: 27.08.2017
 *      Author: nid
 */

#ifndef LIB_HMI_HMI_H_
#define LIB_HMI_HMI_H_

class LcdKeypad;
class Screen;
class Timer;

class Hmi
{
public:
  Hmi();
  virtual ~Hmi();

  void setRelHumidity(float relHumidity);
  void setTemperature(float temperature);
  void setPm(float pm10, float pm25);

  float getRelHumidity();
  float getTemperature();
  float getPm10();
  float getPm25();

  void switchNext();

  LcdKeypad* lcd();

private:
  LcdKeypad* m_lcdKeypad;
  float m_relHumidity;
  float m_temperature;
  float m_pm10;
  float m_pm25;
  Screen* m_currentScreen;
  Timer* m_screenChangeTimer;

private: // forbidden default functions
  Hmi& operator = (const Hmi& src); // assignment operator
  Hmi(const Hmi& src);              // copy constructor
};

#endif /* LIB_HMI_HMI_H_ */
