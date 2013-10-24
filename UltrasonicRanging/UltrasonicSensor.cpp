/*
 * UltrasonicSensor.cpp
 *
 *  Created on: 16.10.2013
 *      Author: niklausd
 */

#include "NewPing.h"
#include "UltrasonicRanging.h"
#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(unsigned int triggerPin,
                                   unsigned int echoPin,
                                   unsigned int maxDistance)
: m_newPing(new NewPing(triggerPin, echoPin, maxDistance))
, m_nextUltrasonicSensor(0)
, m_distanceCM(0)
{
  UltrasonicRanging::instance()->attach(this);
}

UltrasonicSensor::~UltrasonicSensor()
{
  delete m_newPing; m_newPing = 0;
  UltrasonicRanging::instance()->detach(this);
}

UltrasonicSensor* UltrasonicSensor::next()
{
  return m_nextUltrasonicSensor;
}

void UltrasonicSensor::setNext(UltrasonicSensor* ultrasonicSensor)
{
  m_nextUltrasonicSensor = ultrasonicSensor;
}

void UltrasonicSensor::startPing()
{
  if (0 != m_newPing)
  {
    m_newPing->timer_stop();                            // Make sure previous timer is canceled before starting a new ping
    m_distanceCM = 0;                                   // Set distance zero in case there's no ping echo for this sensor.
    m_newPing->ping_timer(UltrasonicSensor::echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
  }
}

NewPing* UltrasonicSensor::getNewPing()
{
  return m_newPing;
}

void UltrasonicSensor::echoCheck()
{
  UltrasonicSensor* ultrasonicSensor = UltrasonicRanging::currentlyMeasuringSensor();
  if (0 != ultrasonicSensor)
  {
    NewPing* newPing = ultrasonicSensor->getNewPing();
    if (0 != newPing)
    {
      if (newPing->check_timer() > 0)
      {
        ultrasonicSensor->setDistanceCM(newPing->ping_result / US_ROUNDTRIP_CM);
      }
    }
  }
}

void UltrasonicSensor::setDistanceCM(unsigned long distanceCM)
{
  m_distanceCM = distanceCM;
}

unsigned long UltrasonicSensor::getDistanceCM()
{
  return m_distanceCM;
}
