/*
 * MyPmAdapter.cpp
 *
 *  Created on: 29.08.2017
 *      Author: nid
 */

#include <Hmi.h>
#include <LoRaTxData.h>
#include <MyPmAdapter.h>

MyPmAdapter::MyPmAdapter(Hmi* hmi, LoRaTxData* loRaTxData)
: m_hmi(hmi)
, m_loRaTxData(loRaTxData)
{ }

MyPmAdapter::~MyPmAdapter()
{ }

void MyPmAdapter::notifyPmChanged(float pm10, float pm25)
{
  if (0 != m_loRaTxData)
  {
    m_loRaTxData->setPm25(pm25);
    m_loRaTxData->setPm10(pm10);
  }
  if (0 != m_hmi)
  {
    m_hmi->setPm(pm10, pm25);
  }
}
