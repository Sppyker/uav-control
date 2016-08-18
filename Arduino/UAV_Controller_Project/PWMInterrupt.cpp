#include "PWMInterrupt.h"

// Create classes for each PWM input pin
PWMInterrupt PWMRead0(0);
PWMInterrupt PWMRead1(1);
PWMInterrupt PWMRead2(2);
PWMInterrupt PWMRead3(3);
PWMInterrupt PWMRead4(4);
PWMInterrupt PWMRead5(5);
PWMInterrupt PWMRead6(6);
PWMInterrupt PWMRead7(7);

// Interrupt Functions
void PWMInterrupt0() { PWMRead0.change(); }
void PWMInterrupt1() { PWMRead1.change(); }
void PWMInterrupt2() { PWMRead2.change(); }
void PWMInterrupt3() { PWMRead3.change(); }
void PWMInterrupt4() { PWMRead4.change(); }
void PWMInterrupt5() { PWMRead5.change(); }
void PWMInterrupt6() { PWMRead6.change(); }
void PWMInterrupt7() { PWMRead7.change(); }

typedef void (*FunctionPointer) (void);

// Create a lookup table contatining all interrupt functions
FunctionPointer PWMInterruptLookup[] = 
{
	PWMInterrupt0,
	PWMInterrupt1,
	PWMInterrupt2,
	PWMInterrupt3,
	PWMInterrupt4,
	PWMInterrupt5,
	PWMInterrupt6,
	PWMInterrupt7,
};

// Create a new PWM interrupt class
PWMInterrupt::PWMInterrupt(byte newInterruptIndex)
{
	interruptIndex = newInterruptIndex;
}


// Attach an interrupt to a certain pin to listen for interrupts
void PWMInterrupt::init(byte newInterruptPin)
{
	interruptPin = newInterruptPin;
	pinMode(interruptPin, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(interruptPin), PWMInterruptLookup[interruptIndex], CHANGE);
}

// Interrupt function that detects when the PWM input has changed and records times.
void PWMInterrupt::change()
{
  if (digitalRead(interruptPin) == LOW)
  {
    usTimeTotal = micros() - usTimeStart;
    medianFilter.add(usTimeTotal);
  }
  else
  {
    usTimeStart = micros();
  }
}

// Returns the current width of the incoming PWM signal
int PWMInterrupt::getTime()
{
	return usTimeTotal;
}

// Returns the median of the incoming PWM signal, range of prior values used is set in #define MEDIAN_BUFFER_SIZE
int PWMInterrupt::getMedianTime()
{
   return medianFilter.getMedian();
}
