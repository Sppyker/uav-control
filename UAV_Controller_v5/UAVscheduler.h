#ifndef UAV_SCHEDULER_H
#define UAV_SCHEDULER_H

#include <stdint.h>
#include <Arduino.h>

class UAVscheduler {
  private:

  public:
  bool loggingInterval();
  bool mainLoopFrequency();
	UAVscheduler();
};

#endif
