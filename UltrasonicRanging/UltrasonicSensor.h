/*
 * UltrasonicSensor.h
 *
 *  Created on: 16.10.2013
 *      Author: niklausd
 */

#ifndef ULTRASONICSENSOR_H_
#define ULTRASONICSENSOR_H_

class NewPing;

//-----------------------------------------------------------------------------

class UltrasonicSensorAdapter
{
public:
  virtual void notifyObstacleDetectionChange(bool isObstacleDetected) = 0;
  virtual ~UltrasonicSensorAdapter() { }
protected:
  UltrasonicSensorAdapter() { }
private: // forbidden default functions
  UltrasonicSensorAdapter& operator = (const UltrasonicSensorAdapter& );  // assignment operator
  UltrasonicSensorAdapter(const UltrasonicSensorAdapter& src);            // copy constructor
};

//-----------------------------------------------------------------------------

class UltrasonicSensor
{
public:
  UltrasonicSensor(unsigned int triggerPin, unsigned int echoPin,
                   unsigned int maxDistance, unsigned long obstacleRangeCM = s_defaultObstacleRange);
  virtual ~UltrasonicSensor();
  void attachAdapter(UltrasonicSensorAdapter* adapter);
  UltrasonicSensorAdapter* adapter();
  UltrasonicSensor* next();
  void setNext(UltrasonicSensor* ultrasonicSensor);
  void startPing();
  NewPing* getNewPing();
  unsigned long getDistanceCM();
  bool isObstacleDetected();
  void setIsObstacleDetectionActive(bool isActive);

private:
  static void echoCheck();
  void updateDistanceCM(unsigned long distanceCM);
  void checkObstacle();

public:
  static const unsigned long DISTANCE_LIMIT_EXCEEDED;

private:
  static const unsigned long s_defaultObstacleRange;

private:
  NewPing* m_newPing;
  UltrasonicSensor* m_nextUltrasonicSensor;
  UltrasonicSensorAdapter* m_adapter;
  unsigned long m_distanceCM;
  unsigned long m_obstacleRangeCM;
  bool m_isObstacleDetected;
  bool m_isObstacleDetectionActive;

private: // forbidden default functions
  UltrasonicSensor& operator = (const UltrasonicSensor& );  // assignment operator
  UltrasonicSensor(const UltrasonicSensor& src);            // copy constructor
};

#endif /* ULTRASONICSENSOR_H_ */
