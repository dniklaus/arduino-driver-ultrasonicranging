/*
 * UltrasonicRanging.cpp
 *
 *  Created on: 16.10.2013
 *      Author: niklausd
 */

#include "Timer.h"
#include <NewPing.h>
#include "UltrasonicSensor.h"
#include "UltrasonicRanging.h"

//===============================================
class UltrasonicRangingTrigTimerAdapter : public TimerAdapter
{
public:
  UltrasonicRangingTrigTimerAdapter(UltrasonicRanging* ultrasonicRanging)
  : m_ultrasonicRanging(ultrasonicRanging)
  { }

  virtual void timeExpired()
  {
    if (0 != m_ultrasonicRanging)
    {
      m_ultrasonicRanging->handleSensorTrigger();
    }
  }

private:
  UltrasonicRanging* m_ultrasonicRanging;
};

//===============================================

UltrasonicSensor* UltrasonicRanging::s_currentUltrasonicSensor = (UltrasonicSensor*)0;

UltrasonicRanging* UltrasonicRanging::s_instance = (UltrasonicRanging*)0;

UltrasonicRanging* UltrasonicRanging::instance()
{
  if (0 == s_instance)
  {
    s_instance = new UltrasonicRanging();
  }
  return s_instance;
}

void UltrasonicRanging::attach(UltrasonicSensor* ultrasonicSensor)
{
  if (0 == m_ultrasonicSensorList)
  {
    m_ultrasonicSensorList = ultrasonicSensor;
  }
  else
  {
    UltrasonicSensor* next = m_ultrasonicSensorList;
    while (next->next() != 0)
    {
      next = next->next();
    }
    next->setNext(ultrasonicSensor);
  }
}

void UltrasonicRanging::detach(UltrasonicSensor* ultrasonicSensor)
{
  if (m_ultrasonicSensorList == ultrasonicSensor)
  {
    m_ultrasonicSensorList = ultrasonicSensor->next();
  }
  else
  {
    UltrasonicSensor* next = m_ultrasonicSensorList;
    while ((next != 0) && (next->next() != ultrasonicSensor))
    {
      next = next->next();
    }
    if (next != 0)
    {
      next->setNext(ultrasonicSensor->next());
    }
  }
}

void UltrasonicRanging::handleSensorTrigger()
{
  if ((0 == s_currentUltrasonicSensor) && (0 != m_ultrasonicSensorList))
  {
    s_currentUltrasonicSensor = m_ultrasonicSensorList;
  }
  else
  {
    s_currentUltrasonicSensor = s_currentUltrasonicSensor->next();
  }
  if (0 != s_currentUltrasonicSensor)
  {
    s_currentUltrasonicSensor->startPing();
  }
}

UltrasonicRanging::UltrasonicRanging()
: m_triggerTimer(new Timer(new UltrasonicRangingTrigTimerAdapter(this), Timer::IS_RECURRING, 50))
, m_ultrasonicSensorList(0)
{ }

UltrasonicRanging::~UltrasonicRanging()
{
  delete m_triggerTimer->adapter();
  delete m_triggerTimer; m_triggerTimer = 0;
}

UltrasonicSensor* UltrasonicRanging::currentlyMeasuringSensor()
{
  return s_currentUltrasonicSensor;
}
