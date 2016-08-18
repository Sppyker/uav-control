#include "sensors.h"

// Create a new sensors class
Sensors::Sensors()
{
	
}

// Init all the sensors
void Sensors::init(State& state)
{
	// Init all sensors here
  PWMRead0.init(ULTRASONIC_PIN_0);
  PWMRead1.init(ULTRASONIC_PIN_1);
  PWMRead2.init(ULTRASONIC_PIN_2);

  // Enable sensor 2 by holding trigger pin low
  pinMode(ULTRASONIC_ENABLE_PIN_2, OUTPUT); // THESE SHOULD BE MOVED SOMEWHERE ELSE??
  digitalWrite(ULTRASONIC_ENABLE_PIN_2, LOW); // THESE SHOULD BE MOVED SOMEWHERE ELSE??
}

void Sensors::update(State& state)
{
  // Update all the sensors here
  state.forward_sensor1 = PWMRead0.getMedianTime();
  state.forward_sensor2 = PWMRead1.getMedianTime();
  state.altitude_sensor = PWMRead2.getMedianTime();
}
