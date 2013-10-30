/*
 * UltrasonicSensorHCSR04.h
 *
 *  Created on: 16.10.2013
 *      Author: niklausd
 */

#ifndef ULTRASONICSENSORHCSR04_H_
#define ULTRASONICSENSORHCSR04_H_

#include "UltrasonicSensor.h"
/*
 *
 */
class UltrasonicSensorHCSR04 : public UltrasonicSensor
{
public:
  UltrasonicSensorHCSR04(unsigned int triggerPin, unsigned int echoPin, unsigned int maxDistance = s_defaultMaxDistance);
  virtual ~UltrasonicSensorHCSR04();

private:
  /**
   * Maximum default distance we want to ping for: 200 [cm]. Maximum sensor distance is rated at 400-500 [cm].
   */
  static const unsigned int s_defaultMaxDistance;

private: // forbidden default functions
  UltrasonicSensorHCSR04& operator = (const UltrasonicSensorHCSR04& );  // assignment operator
  UltrasonicSensorHCSR04(const UltrasonicSensorHCSR04& src);            // copy constructor
};

#endif /* ULTRASONICSENSORHCSR04_H_ */