#ifndef LOGGING_H
#define LOGGING_H

#include <stdint.h>
#include <Arduino.h>
#include "state.h"
#include "minipack.h"

#define DEFAULT_BAUD_RATE 9600

class Logging {
	private:
	  int logNo;
    MinipackOutput miniout;
    void sendPackedByte(int byte_no, int c);
  public:
	  Logging();
	  void init(State& state, int baud=DEFAULT_BAUD_RATE);
    void update(State& state);
    void writeSerial(State& state);
};

#endif
