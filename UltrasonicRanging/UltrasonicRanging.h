/*
 * UltrasonicRanging.h
 *
 *  Created on: 16.10.2013
 *      Author: niklausd
 */

#ifndef ULTRASONICRANGING_H_
#define ULTRASONICRANGING_H_

class UltrasonicSensor;
class NewPing;
class Timer;

/*
 *
 */
class UltrasonicRanging
{
public:
  static UltrasonicRanging* instance();
  virtual ~UltrasonicRanging();

  void handleSensorTrigger();

  void attach(UltrasonicSensor* ultrasonicSensor);
  void detach(UltrasonicSensor* ultrasonicSensor);

  static UltrasonicSensor* currentlyMeasuringSensor();

private:
  UltrasonicRanging();

private:
  static UltrasonicRanging* s_instance;
  static UltrasonicSensor*  s_currentUltrasonicSensor;
  Timer* m_triggerTimer;
  UltrasonicSensor* m_ultrasonicSensorList;

private: // forbidden default functions
  UltrasonicRanging& operator = (const UltrasonicRanging& );  // assignment operator
  UltrasonicRanging(const UltrasonicRanging& src);            // copy constructor
};

#endif /* ULTRASONICRANGING_H_ */
