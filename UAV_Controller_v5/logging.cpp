#include "logging.h"

// Create a new sensors class
Logging::Logging()
{
	
}

// Init all the sensors
void Logging::init(State& state, int baud)
{
  logNo = 0;
  
	LOGGING_SERIAL_PORT.begin(baud);
  delay(2500); // DELAY TO ALLOW TO START UP
  LOGGING_SERIAL_PORT.print("Initiating logging...");
  
  LOGGING_SERIAL_PORT.println("Successful! Initial Values as follows:");

  LOGGING_SERIAL_PORT.print(ALTITUDE_KP);
  LOGGING_SERIAL_PORT.print(" ");
  LOGGING_SERIAL_PORT.print(ALTITUDE_KI);
  LOGGING_SERIAL_PORT.print(" ");
  LOGGING_SERIAL_PORT.print(ALTITUDE_KD);
  LOGGING_SERIAL_PORT.print(" ");
  LOGGING_SERIAL_PORT.print(THROTTLE_LIMIT);
  LOGGING_SERIAL_PORT.print(" ");
  LOGGING_SERIAL_PORT.print(ALTITUDE_PID_GAIN_RATIO);
  LOGGING_SERIAL_PORT.print(" ");
  LOGGING_SERIAL_PORT.print(ALTITUDE_DESIRED_HOVER_HEIGHT);
  LOGGING_SERIAL_PORT.println(" ");
  
  LOGGING_SERIAL_PORT.println("ALTITUDE_KP,ALTITUDE_KI,ALTITUDE_KD,THROTTLE_LIMIT,ALTITUDE_PID_GAIN_RATIO,ALTITUDE_HOVER_HEIGHT");
  LOGGING_SERIAL_PORT.println(" ");
  LOGGING_SERIAL_PORT.println("Beginning Control Loop...logging data in following sequence");
  LOGGING_SERIAL_PORT.println("LogNo,Timestep,ControlMode,FowardUS1,FowardUS2,AltitudeUS,ThrottleCTRL,YawCTRL,RollCTRL,PitchCTRL,StabilityModeCtrl");
  LOGGING_SERIAL_PORT.println(" ");
}

void Logging::update(State& state)
{
  logNo = logNo+1;
  LOGGING_SERIAL_PORT.print(logNo); // Increment by 1 each time (int -> 2 Bytes)
  LOGGING_SERIAL_PORT.print(" "); // (1 byte)
  LOGGING_SERIAL_PORT.print(millis()); // Current Timestep (Unsigned long -> 4 bytes)
  LOGGING_SERIAL_PORT.print(" "); // (1 byte)
  LOGGING_SERIAL_PORT.print(state.control_mode); // Control Mode (Byte -> 1 byte)
  LOGGING_SERIAL_PORT.print(" "); // (1 byte)
  LOGGING_SERIAL_PORT.print(state.forward_sensor1); // Forward sensor reading 1 (Double -> 8 bytes)
  LOGGING_SERIAL_PORT.print(" "); // (1 byte)
  LOGGING_SERIAL_PORT.print(state.forward_sensor2); // Forward sensor reading 2 (Double -> 8 bytes)
  LOGGING_SERIAL_PORT.print(" "); // (1 byte)
  LOGGING_SERIAL_PORT.print(state.altitude_sensor); // Altitude sensor reading (Double -> 8 bytes)
  LOGGING_SERIAL_PORT.print(" "); // (1 byte)
  LOGGING_SERIAL_PORT.print(state.throttle_control); // Throttle control signal (Short -> 2 bytes)
  LOGGING_SERIAL_PORT.print(" "); // (1 byte)
  LOGGING_SERIAL_PORT.print(0); // Yaw control signal (Short -> 2 bytes)
  LOGGING_SERIAL_PORT.print(" "); // (1 byte)
  LOGGING_SERIAL_PORT.print(0); // Roll control signal (Short -> 2 bytes)
  LOGGING_SERIAL_PORT.print(" "); // (1 byte)
  LOGGING_SERIAL_PORT.print(0); // Pitch control signal (Short -> 2 bytes)
  LOGGING_SERIAL_PORT.print(" "); // (1 byte)
  LOGGING_SERIAL_PORT.print(0); // Stability mode control signal (Short -> 2 bytes)
  LOGGING_SERIAL_PORT.print(" "); // (1 byte)
  LOGGING_SERIAL_PORT.print(state.kp_error); // Kp Error  (Float -> 4 bytes)
  LOGGING_SERIAL_PORT.print(" "); // (1 byte)
  LOGGING_SERIAL_PORT.print(state.ki_error); // Ki Error (Float -> 4 bytes)
  LOGGING_SERIAL_PORT.print(" "); // (1 byte)
  LOGGING_SERIAL_PORT.println(state.kd_error); // Kd Error (Float -> 4 bytes)
}



void Logging::sendPackedByte(char c)
{
  miniout.NewPacket();
  miniout.Pack(1, c);
  LOGGING_SERIAL_PORT.write(miniout.EndPacket());
}

