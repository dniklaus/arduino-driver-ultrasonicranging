/*
 * UltrasonicSensor.h
 *
 *  Created on: 16.10.2013
 *      Author: niklausd
 */

#ifndef ULTRASONICSENSOR_H_
#define ULTRASONICSENSOR_H_

class NewPing;
class UltrasonicSensor
{
public:
  UltrasonicSensor(unsigned int triggerPin, unsigned int echoPin, unsigned int maxDistance);
  virtual ~UltrasonicSensor();
  UltrasonicSensor* next();
  void setNext(UltrasonicSensor* ultrasonicSensor);
  void startPing();
  NewPing* getNewPing();
  unsigned long getDistanceCM();

private:
  static void echoCheck();
  void setDistanceCM(unsigned long distanceCM);

private:
  NewPing* m_newPing;
  UltrasonicSensor* m_nextUltrasonicSensor;
  unsigned long m_distanceCM;

private: // forbidden default functions
  UltrasonicSensor& operator = (const UltrasonicSensor& );  // assignment operator
  UltrasonicSensor(const UltrasonicSensor& src);            // copy constructor
};

#endif /* ULTRASONICSENSOR_H_ */
