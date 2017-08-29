/*
 * MyPmAdapter.cpp
 *
 *  Created on: 29.08.2017
 *      Author: nid
 */

#include <Hmi.h>
#include <MyPmAdapter.h>

MyPmAdapter::MyPmAdapter(Hmi* hmi)
: m_hmi(hmi)
{ }

MyPmAdapter::~MyPmAdapter()
{ }

void MyPmAdapter::notifyPmChanged(float pm10, float pm25)
{
  if (0 != m_hmi)
  {
    m_hmi->setPm(pm10, pm25);
  }
}
