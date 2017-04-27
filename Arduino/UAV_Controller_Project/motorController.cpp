#include "motorController.h"

// Create a new sensors class
MotorController::MotorController()
{
	
}

// Init all the sensors
void MotorController::init(State& state)
{
	// Attach the servos to control 
  UAV_stable_mode.attach(AUTONOMOUS_STABLE_MODE_PIN,PWM_LIMIT_MIN, PWM_LIMIT_MAX);
  UAV_stable_mode.writeMicroseconds(PWM_NEUTRAL);

  UAV_yaw.attach(AUTONOMOUS_YAW_PIN,PWM_LIMIT_MIN, PWM_LIMIT_MAX);
  UAV_yaw.writeMicroseconds(PWM_NEUTRAL);

  UAV_throttle.attach(AUTONOMOUS_THROTTLE_PIN,PWM_LIMIT_MIN, PWM_LIMIT_MAX);
  UAV_throttle.writeMicroseconds(PWM_LIMIT_MIN);

  UAV_roll.attach(AUTONOMOUS_ROLL_PIN,PWM_LIMIT_MIN, PWM_LIMIT_MAX);
  UAV_roll.writeMicroseconds(PWM_NEUTRAL);

  UAV_pitch.attach(AUTONOMOUS_PITCH_PIN,PWM_LIMIT_MIN, PWM_LIMIT_MAX);
  UAV_pitch.writeMicroseconds(PWM_NEUTRAL);
}


void MotorController::update(State& state)
{
  /* Limit throttle to the PWM limits of the motor, such that it does not exceed these */
  if (state.throttle_control >= PWM_LIMIT_MAX) { state.throttle_control = PWM_LIMIT_MAX; }
  if (state.throttle_control <= PWM_LIMIT_MIN) { state.throttle_control = PWM_LIMIT_MIN; }

  /* Limit the tilt command signal, such that it does not exceed these */
  if (state.pitch_control >= TILT_LIMIT_MAX) { state.pitch_control = TILT_LIMIT_MAX; }
  if (state.pitch_control <= TILT_LIMIT_MIN) { state.pitch_control = TILT_LIMIT_MIN; }

  /* Update all the motors with their required PWM control*/
	UAV_throttle.writeMicroseconds((state.throttle_control));
  UAV_pitch.writeMicroseconds((state.pitch_control));
 
}
