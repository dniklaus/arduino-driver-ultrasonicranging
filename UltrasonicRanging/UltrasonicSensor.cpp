/*
 * UltrasonicSensor.cpp
 *
 *  Created on: 16.10.2013
 *      Author: niklausd
 */

#include "UltrasonicRanging.h"
#include "UltrasonicSensor.h"

const unsigned long UltrasonicSensor::DISTANCE_LIMIT_EXCEEDED = -1;
const unsigned int  UltrasonicSensor::s_microsPerCm           = 58;
const unsigned long UltrasonicSensor::s_defaultObstacleRange  = 15;

UltrasonicSensor::UltrasonicSensor(unsigned int maxDistanceCM,
                                   unsigned long obstacleRangeCM)
: m_nextUltrasonicSensor(0)
, m_adapter(0)
, m_distanceCM(DISTANCE_LIMIT_EXCEEDED)
, m_maxDistanceCM(maxDistanceCM)
, m_obstacleRangeCM(obstacleRangeCM)
, m_echoTimeMicros(0)
, m_isObstacleDetected(false)
, m_isObstacleDetectionActive(false)
{
  UltrasonicRanging::instance()->attach(this);
}

UltrasonicSensor::~UltrasonicSensor()
{
  UltrasonicRanging::instance()->detach(this);
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
  if (0 != m_adapter)
  {
    m_echoTimeMicros = m_adapter->getEchoTimeMicros();
    m_distanceCM = m_echoTimeMicros / s_microsPerCm;
    if (m_distanceCM > m_maxDistanceCM)
    {
      m_distanceCM = DISTANCE_LIMIT_EXCEEDED;
    }
    checkObstacle();
    m_adapter->startPing();
  }
}


void UltrasonicSensor::checkObstacle()
{
  bool isObstacleDetected = m_isObstacleDetectionActive && ((m_distanceCM > 0) && (m_distanceCM < m_obstacleRangeCM));
  bool haveToNotify = (isObstacleDetected != m_isObstacleDetected);
  m_isObstacleDetected = isObstacleDetected;
  if ((0 != adapter()) && haveToNotify)
  {
    adapter()->notifyObstacleDetectionChange(isObstacleDetected);
  }
}

unsigned long UltrasonicSensor::getDistanceCM()
{
  return m_distanceCM;
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
