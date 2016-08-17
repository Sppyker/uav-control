#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>
#include <Arduino.h>
#include "state.h"
#include "PWMInterrupt.h"

class Sensors {
	private:
	
    public:
	  Sensors();
	  void init(State& state);
    void update(State& state);
};

#endif
