#ifndef UAVCONTROL_H
#define UAVCONTROL_H

#include <stdint.h>
#include <Arduino.h>
#include "state.h"
#include "PID.h"
#include "motorController.h"
#include "config.h"

#define ALTITUDE_PID_LIMIT_MIN 0
#define ALTITUDE_PID_LIMIT_MAX 1000

class UAVControl {
  private:
    int altitude_setpoint,  altitude_input,  altitude_output;
    PID altitudePID;
    int startup_delay;
  public:
	  UAVControl();
	  void init(State& state);
    void update(State& state);
    
};

#endif
