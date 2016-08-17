// ALL #INCLUDES GO HERE, ONLY HIGH LEVEL! Low level #includes go in respective classes as required

#include "state.h"
#include "sensors.h"
#include "logging.h"
#include "motorController.h"
#include "UAVControl.h"
#include "config.h"

State state;

Sensors sensors;
UAVControl UAVcontrol;
MotorController motorController;
Logging logging;

unsigned long main_loop_polled_time;
short logging_counter;

void setup()
{
	state.init();
  logging.init(state, 19200); //NEED THIS TO BE AN OPTIONAL ARGUMENT LATER, ALSO INCREASE BAUD RATE
  UAVcontrol.init(state);
	sensors.init(state);
	motorController.init(state);

  main_loop_polled_time = millis();
  logging_counter = 0;
}

void loop()
{
 
 if (millis() - main_loop_polled_time >= MAIN_LOOP_FREQUENCY)
 {
	main_loop_polled_time = millis();
	
	sensors.update(state);
	UAVcontrol.update(state);
	motorController.update(state);


  if (logging_counter >= LOG_INTERVAL)
  {
	  logging.update(state);
    logging_counter = 0;
  }
  logging_counter++;
  
 }
}
