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

  void updateDisplay(float relHumidity, float temperature);

private:
  LcdKeypad* m_lcdKeypad;

private: // forbidden default functions
  Hmi& operator = (const Hmi& src); // assignment operator
  Hmi(const Hmi& src);              // copy constructor
};

#endif /* LIB_HMI_HMI_H_ */
