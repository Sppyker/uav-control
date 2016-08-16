#ifndef PWMINTERRUPT_H
#define PWMINTERRUPT_H

#include <stdint.h>
#include <Arduino.h>
#include "runningMedian.h"

#define MEDIAN_BUFFER_SIZE 5

class PWMInterrupt {
	private:
		byte interruptIndex;
		byte interruptPin;
		bool state;
		unsigned long usTimeStart;
		int usTimeTotal;
		RunningMedian medianFilter = RunningMedian(MEDIAN_BUFFER_SIZE);
    public:
		PWMInterrupt(byte newInterruptIndex);
		void init(byte newInterruptPin);
		void change();
		int getTime();
		int getMedianTime();
};

extern PWMInterrupt PWMRead0;
extern PWMInterrupt PWMRead1;
extern PWMInterrupt PWMRead2;
extern PWMInterrupt PWMRead3;
extern PWMInterrupt PWMRead4;
extern PWMInterrupt PWMRead5;
extern PWMInterrupt PWMRead6;
extern PWMInterrupt PWMRead7;

#endif
