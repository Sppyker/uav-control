#ifndef STATE_H
#define STATE_H

#include <stdint.h>
#include <Arduino.h>
#include "config.h"

#define AUTO_CONTROL 0
#define MANUAL_CONTROL 1

class State {
	public:
	  // Sensor readings
	  double altitude_sensor;
	  double forward_sensor1;
	  double forward_sensor2;
	  
	  // Control Mode: AUTO_CONTROL or MANUAL_CONTROL
	  byte control_mode;
	  
	  // UAV Control
	  short throttle_control;
	  short yaw_control;
	  short roll_control;
	  short pitch_control;
	  short stability_mode_control;

    // PID

    float kp_error_altitude;
    float ki_error_altitude;
    float kd_error_altitude;
    
	  State();
    void init();
    void defaults();
};

#endif
