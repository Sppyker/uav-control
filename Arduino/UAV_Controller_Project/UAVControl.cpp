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

  // Wall Distance
  wall_distance_setpoint = WALL_DISTANCE_DESIRED;
  // Get initial ultrasonic distance
  wall_distance_input = (state.forward_sensor1 + state.forward_sensor2)/2;
  wall_distance_PID.setOutputLimits(-50,50);
  wall_distance_PID.init(DISTANCE_KP, DISTANCE_KI, DISTANCE_KD, wall_distance_setpoint, DISTANCE_PID_LIMIT_MIN, DISTANCE_PID_LIMIT_MAX);

  // Startup delay, sensors provide wrong values when starting up
  startup_delay = STARTUP_SENSOR_IGNORE;
  
}

void UAVControl::update(State& state)
{
 // Check the current control mode and update the state.
 state.control_mode = digitalRead(CONTROL_MODE_PIN);
 
 // Read the altitude sensor to determine current height
 altitude_input = state.altitude_sensor;

 // Read the distance sensor to determine distance from wall
 wall_distance_input = (state.forward_sensor1 + state.forward_sensor2)/2;
 
 // Ignore the first STARTUP_SENSOR_IGNORE sensor reads, as first reads can be inaccurate
 if (startup_delay >= 0) { altitude_input = ALTITUDE_DESIRED_HOVER_HEIGHT; startup_delay--;}

 // Set integral to 0 if in Manual Mode
 if (state.control_mode == MANUAL_CONTROL) { altitudePID.resetIntegral(); }
  
 // Use altitude PID to converge towards desired 
 altitude_output = altitudePID.update(altitude_input);
 state.kp_error_altitude = altitudePID.getErrorP();
 state.ki_error_altitude = altitudePID.getErrorI();
 state.kd_error_altitude = altitudePID.getErrorD();
 
 state.throttle_control = altitude_output+PWM_LIMIT_MIN;
 if (state.throttle_control >= THROTTLE_LIMIT)
 {
   state.throttle_control = THROTTLE_LIMIT;
 }

// Use distance PID to converge towards desired distance
wall_distance_output = wall_distance_PID.update(wall_distance_input);
state.pitch_control = wall_distance_output+PWM_NEUTRAL;
 
}
