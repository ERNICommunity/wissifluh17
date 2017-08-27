/*
 * Hmi.h
 *
 *  Created on: 27.08.2017
 *      Author: nid
 */

#ifndef LIB_HMI_HMI_H_
#define LIB_HMI_HMI_H_

class LcdKeypad;

class Hmi
{
public:
  Hmi();
  virtual ~Hmi();

  void setRelHumidity(float relHumidity);
  void setTemperature(float temperature);
  void setPm(float pm10Average, float pm25Average);

private:
  void updateDisplayRelHumidityTemperature();
  void updateDisplayPm();

private:
  LcdKeypad* m_lcdKeypad;
  float m_relHumidity;
  float m_temperature;
  float m_pm10;
  float m_pm25;

private: // forbidden default functions
  Hmi& operator = (const Hmi& src); // assignment operator
  Hmi(const Hmi& src);              // copy constructor
};

#endif /* LIB_HMI_HMI_H_ */
