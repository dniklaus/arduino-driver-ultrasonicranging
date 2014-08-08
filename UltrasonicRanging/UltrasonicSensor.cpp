/*
 * UltrasonicSensor.cpp
 *
 *  Created on: 16.10.2013
 *      Author: niklausd
 */

#include "NewPing.h"
#include "UltrasonicRanging.h"
#include "UltrasonicSensor.h"

const unsigned long UltrasonicSensor::DISTANCE_LIMIT_EXCEEDED = -1;
const unsigned long UltrasonicSensor::s_defaultObstacleRange = 15;

UltrasonicSensor::UltrasonicSensor(unsigned int triggerPin,
                                   unsigned int echoPin,
                                   unsigned int maxDistance,
                                   unsigned long obstacleRangeCM)
: m_newPing(new NewPing(triggerPin, echoPin, maxDistance))
, m_nextUltrasonicSensor(0)
, m_adapter(0)
, m_distanceCM(0)
, m_obstacleRangeCM(obstacleRangeCM)
, m_isObstacleDetected(false)
, m_isObstacleDetectionActive(false)
{
  UltrasonicRanging::instance()->attach(this);
}

UltrasonicSensor::~UltrasonicSensor()
{
  UltrasonicRanging::instance()->detach(this);
  delete m_newPing; m_newPing = 0;
}

void UltrasonicSensor::attachAdapter(UltrasonicSensorAdapter* adapter)
{
  m_adapter = adapter;
}

UltrasonicSensorAdapter* UltrasonicSensor::adapter()
{
  return m_adapter;
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
  checkObstacle();
  if (0 != m_newPing)
  {
    m_newPing->timer_stop();                            // Make sure previous timer is canceled before starting a new ping
    m_distanceCM = DISTANCE_LIMIT_EXCEEDED;             // Set distance infinite in case there's no ping echo for this sensor.
    m_newPing->ping_timer(UltrasonicSensor::echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
  }
}

NewPing* UltrasonicSensor::getNewPing()
{
  return m_newPing;
}

void UltrasonicSensor::echoCheck()
{
  noInterrupts();
  UltrasonicSensor* ultrasonicSensor = UltrasonicRanging::currentlyMeasuringSensor();
  if (0 != ultrasonicSensor)
  {
    NewPing* newPing = ultrasonicSensor->getNewPing();
    if (0 != newPing)
    {
      if (newPing->check_timer() > 0)
      {
        ultrasonicSensor->updateDistanceCM(newPing->ping_result / US_ROUNDTRIP_CM);
      }
    }
  }
  interrupts();
}

void UltrasonicSensor::updateDistanceCM(unsigned long distanceCM)
{
  m_distanceCM = distanceCM;
}

void UltrasonicSensor::checkObstacle()
{
  unsigned long distanceCM = getDistanceCM();
  bool isObstacleDetected = m_isObstacleDetectionActive && (distanceCM > 0) && (distanceCM < m_obstacleRangeCM);
  bool haveToNotify = (isObstacleDetected != m_isObstacleDetected);
  m_isObstacleDetected = isObstacleDetected;
  if ((0 != m_adapter) && haveToNotify)
  {
    m_adapter->notifyObstacleDetectionChange(isObstacleDetected);
  }
}


unsigned long UltrasonicSensor::getDistanceCM()
{
  unsigned long distanceCM = 0;
  noInterrupts();
  distanceCM = m_distanceCM;
  interrupts();
  return distanceCM;
}

bool UltrasonicSensor::isObstacleDetected()
{
  return m_isObstacleDetected;
}

void UltrasonicSensor::setIsObstacleDetectionActive(bool isActive)
{
  m_isObstacleDetectionActive = isActive;
  checkObstacle();
}
