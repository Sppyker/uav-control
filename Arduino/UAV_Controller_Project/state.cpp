#include "state.h"

// Create a new state class
State::State()
{
	
}

// Initialize an ultrasonic sensor on a certain pin.
void State::init()
{
	State::defaults();
}

// Initialize an ultrasonic sensor on a certain pin.
void State::defaults()
{
	// Sensor readings
	altitude_sensor = 0;
	forward_sensor1 = 0;
	forward_sensor2 = 0;
	
	// ControlMode -> AUTO_CONTROL or MANUAL_CONTROL
	control_mode = MANUAL_CONTROL;
	
	// UAV Control -> All set to neutral!
	throttle_control = PWM_NEUTRAL;
	yaw_control = PWM_NEUTRAL;
	roll_control = PWM_NEUTRAL;
	pitch_control = PWM_NEUTRAL;
	stability_mode_control = PWM_NEUTRAL;

 // PID

 kp_error_altitude = 0;
 ki_error_altitude = 0;
 kd_error_altitude = 0;
}
