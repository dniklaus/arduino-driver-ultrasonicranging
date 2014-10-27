/*
 * UltrasonicSensor.h
 *
 *  Created on: 16.10.2013
 *      Author: niklausd
 */

#ifndef ULTRASONICSENSOR_H_
#define ULTRASONICSENSOR_H_

//-----------------------------------------------------------------------------

class UltrasonicSensorAdapter
{
public:
  virtual void startPing() = 0;
  virtual unsigned long getEchoPulseDurationTimeMicros() = 0;
  virtual void notifyObstacleDetectionChange(bool isObstacleDetected) = 0;
  virtual ~UltrasonicSensorAdapter() { }
protected:
  UltrasonicSensorAdapter() { }                                           // abstract
private: // forbidden default functions
  UltrasonicSensorAdapter& operator = (const UltrasonicSensorAdapter& );  // assignment operator
  UltrasonicSensorAdapter(const UltrasonicSensorAdapter& src);            // copy constructor
};

//-----------------------------------------------------------------------------

class UltrasonicSensor
{
public:
  UltrasonicSensor(unsigned int maxDistance, unsigned long obstacleRangeCM = s_defaultObstacleRange);
  virtual ~UltrasonicSensor();
  void attachAdapter(UltrasonicSensorAdapter* adapter);
  UltrasonicSensorAdapter* adapter();
  UltrasonicSensor* next();
  void setNext(UltrasonicSensor* ultrasonicSensor);
  void startPing();
  unsigned long getDistanceCM();
  bool isObstacleDetected();
  void setIsObstacleDetectionActive(bool isActive);

private:
  void checkObstacle();

public:
  static const unsigned long DISTANCE_LIMIT_EXCEEDED;
  static const unsigned int  s_microsPerCm;

private:
  static const unsigned long s_defaultObstacleRange;

private:
  UltrasonicSensor* m_nextUltrasonicSensor;
  UltrasonicSensorAdapter* m_adapter;
  volatile unsigned long m_obstacleRangeCM;
  volatile unsigned long m_echoStartTimeMicros;
  volatile unsigned long m_durationTimeMicros;
  bool m_isObstacleDetected;
  bool m_isObstacleDetectionActive;

private: // forbidden default functions
  UltrasonicSensor& operator = (const UltrasonicSensor& );  // assignment operator
  UltrasonicSensor(const UltrasonicSensor& src);            // copy constructor
};

#endif /* ULTRASONICSENSOR_H_ */
