#include "PID.h"

// Create a new sensors class
PID::PID()
{
	
}

// Init the PID controller
void PID::init(float new_kp, float new_ki, float new_kd,int new_setpoint, int new_output_limit_min, int new_output_limit_max)
{
	// init the setpoint
	setpoint = new_setpoint;
	kp = new_kp;
	ki = new_ki;
	kd = new_kp;
	error_sum = 0;
	error_previous = 0;
	error_difference = 0;
  output_limit_min = new_output_limit_min;
  output_limit_max = new_output_limit_max;
  error_sum_limit = (output_limit_max - output_limit_min)/ki;
}

int PID::update(int input)
{
	/* Timestep */
	time = millis();
	timestep = ((float)(time - time_previous))/(1000.0);
	time_previous = time;
	
	/* Compute all error variables */
	error = setpoint - input;
	error_sum += error*timestep;
	error_difference = (error - error_previous)/timestep;

  /* Limit the integral */
  if (error_sum > error_sum_limit) { error_sum = error_sum_limit; }
  else if (error_sum < -error_sum_limit) { error_sum = -error_sum_limit; }

  /* Median filter the differential error, to reduce noise amplification */
  differential_median_filter.add(error_difference);
  error_difference = differential_median_filter.getAverage();
  
	/* Compute each part of the PID error */
	kp_error = kp*error;
	ki_error = ki*error_sum;
	kd_error = kd*error_difference;
	
	/* Compute PID output_iterator */
	output = kp_error + ki_error + kd_error;
  
  /* Limit the output between two variables */
  if (output >= output_limit_max) { output = output_limit_max; }
  if (output <= output_limit_min) { output = output_limit_min; }
  
	/* Record variables for next loop */
	error_previous = error;
	
	return output;
}

void PID::setSetpoint(int new_setpoint)
{
	setpoint = new_setpoint;
}

void PID::setOutputLimits(int min_limit, int max_limit)
{
  output_limit_min = min_limit;
  output_limit_max = max_limit;
}

void PID::setErrorSumLimit(int new_error_sum_limit)
{
  error_sum_limit = new_error_sum_limit;
}

float PID::getErrorP()
{
  return kp_error;
}

float PID::getErrorI()
{
  return ki_error;
}

float PID::getErrorD()
{
  return kd_error;
}

void PID::resetIntegral()
{
  error_sum = 0;
}
