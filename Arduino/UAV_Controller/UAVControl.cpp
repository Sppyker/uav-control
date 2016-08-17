#include "UAVControl.h"

// Create a new sensors class
UAVControl::UAVControl()
{
}

// Init all the sensors
void UAVControl::init(State& state)
{
  // Define the desired setpoint
  altitude_setpoint = ALTITUDE_DESIRED_HOVER_HEIGHT;
  // Get the ultrasonic sensor time.
  altitude_input = state.altitude_sensor;
  altitudePID.setOutputLimits(0,1000);
  altitudePID.init(ALTITUDE_KP, ALTITUDE_KI, ALTITUDE_KD, altitude_setpoint, ALTITUDE_PID_LIMIT_MIN, ALTITUDE_PID_LIMIT_MAX);
  startup_delay = STARTUP_SENSOR_IGNORE;
}

void UAVControl::update(State& state)
{
 // Check the current control mode and update the state.
 state.control_mode = digitalRead(CONTROL_MODE_PIN);
 
 // Read the altitude sensor to determine current height
 altitude_input = state.altitude_sensor;
 
 // Ignore the first STARTUP_SENSOR_IGNORE sensor reads, as first reads can be inaccurate
 if (startup_delay >= 0) { altitude_input = ALTITUDE_DESIRED_HOVER_HEIGHT; startup_delay--;}

 // Set integral to 0 if not in control mode
 if (state.control_mode == MANUAL_CONTROL) { altitudePID.resetIntegral(); }

 // Read both distance sensors to determine distance from wall
 // Make sure the difference between the two sensors is within a certain range
 // If not: Rotate YAW to adjust them towards each other (SLOWLY)
 // If so: Use PID to adjust pitch to move UAV to desired position to wall (SLOWLY)

 // Right now roll is left at neutral as no way to detect the position along the wall.
  
 // Use PID to converge towards desired 
 altitude_output = altitudePID.update(altitude_input);
 state.kp_error = altitudePID.getErrorP();
 state.ki_error = altitudePID.getErrorI();
 state.kd_error = altitudePID.getErrorD();
 
 state.throttle_control = altitude_output+PWM_LIMIT_MIN;
 if (state.throttle_control >= THROTTLE_LIMIT)
 {
   state.throttle_control = THROTTLE_LIMIT;
 }
}
