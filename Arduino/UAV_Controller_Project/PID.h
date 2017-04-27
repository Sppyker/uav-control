#ifndef PID_H
#define PID_H

#include <stdint.h>
#include <Arduino.h>
#include "runningMedian.h"

#define DIFFERENTIAL_MEDIAN_DEFAULT_BUFFER 3

class PID {
	private:
		int setpoint;
		float kp;
		float ki;
		float kd;
		float input;
		float output;
    float error;
		float error_sum;
		float error_previous;
		float error_difference;
		float kp_error_altitude;
		float ki_error_altitude;
		float kd_error_altitude;
		float timestep;
		unsigned long time_previous;
		unsigned long time;
    int output_limit_min;
    int output_limit_max;
    int error_sum_limit;
    RunningMedian differential_median_filter = RunningMedian(DIFFERENTIAL_MEDIAN_DEFAULT_BUFFER);
	public:
		PID();
		void init(float new_kp, float new_ki, float new_kd,int new_setpoint=0, int new_output_limit_min=0, int new_output_limit_max=255);
		int update(int input);
		void setSetpoint(int new_setpoint);
    void setOutputLimits(int min_limit, int max_limit);
    void setErrorSumLimit(int new_error_sum_limit);
    void resetIntegral();
    
    float getErrorP();
    float getErrorI();
    float getErrorD();

};

#endif
