/*
 * MyPmAdapter.h
 *
 *  Created on: 29.08.2017
 *      Author: nid
 */

#ifndef LIB_ADAPTERS_MYPMADAPTER_H_
#define LIB_ADAPTERS_MYPMADAPTER_H_

#include <SDS011.h>

class Hmi;

class MyPmAdapter : public PmAdapter
{
private:
  Hmi* m_hmi;

public:
  MyPmAdapter(Hmi* hmi);
  virtual ~MyPmAdapter();

  void notifyPmChanged(float pm10, float pm25);

private: // forbidden default functions
  MyPmAdapter();                                    // default constructor
  MyPmAdapter& operator = (const MyPmAdapter& src); // assignment operator
  MyPmAdapter(const MyPmAdapter& src);              // copy constructor
};

#endif /* LIB_ADAPTERS_MYPMADAPTER_H_ */
