#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <stdint.h>
#include <Arduino.h>
#include "state.h"
#include <Servo.h>

#define PWM_LIMIT_MIN 1000
#define PWM_LIMIT_MAX 2000
#define PWM_NEUTRAL 1500

class MotorController {
	private:
	  Servo UAV_stable_mode;
    Servo UAV_yaw;
    Servo UAV_throttle;
    Servo UAV_roll;
    Servo UAV_pitch;
  public:
	  MotorController();
	  void init(State& state);
    void update(State& state);
};

#endif
