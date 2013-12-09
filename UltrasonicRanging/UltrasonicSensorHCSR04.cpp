/*
 * UltrasonicSensorHCSR04.cpp
 *
 *  Created on: 16.10.2013
 *      Author: niklausd
 */

#include "UltrasonicSensorHCSR04.h"

const unsigned int UltrasonicSensorHCSR04::DEFAULT_MAX_DIST = 200;

UltrasonicSensorHCSR04::UltrasonicSensorHCSR04(unsigned int triggerPin, unsigned int echoPin, unsigned int maxDistance)
: UltrasonicSensor(triggerPin, echoPin, maxDistance)
{ }

UltrasonicSensorHCSR04::~UltrasonicSensorHCSR04()
{ }

