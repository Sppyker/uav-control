#ifndef CONFIG_H
#define CONFIG_H

/* PUT ALL REVEVANT #defines here that will be modified!! */

#define MAIN_LOOP_FREQUENCY 20 // How often the main loop should poll (ms)
#define LOG_INTERVAL 5 // How many loops of the program before each logging period is done

// How many main loops should the sensor readings be ignored for when program first begins
#define STARTUP_SENSOR_IGNORE 10

#define PWM_NEUTRAL 1500 // This one should not really change -> maybe put somewhere else??

#define ALTITUDE_PID_GAIN_RATIO 1

// Define the PID values for the altitude controls
#define ALTITUDE_KP 0.6*ALTITUDE_PID_GAIN_RATIO
#define ALTITUDE_KI 0.3*ALTITUDE_PID_GAIN_RATIO
#define ALTITUDE_KD 0.001*ALTITUDE_PID_GAIN_RATIO

// Multiplier for KP,KI,KD if ratio correct but gain wrong.

// Define the PID values for the distance control

#define DISTANCE_KP 0.5
#define DISTANCE_KI 0
#define DISTANCE_KD 0


// Limit throttle during testing such that the UAV does not fly upwards with too much force (1000 -> 2000 | MIN -> MAX)
#define THROTTLE_LIMIT 1800

// Limit the angle of the UAV so it cannot tilt excessively

#define TILT_LIMIT_MAX 1700
#define TILT_LIMIT_MIN 1300

// Desired height that the UAV will remain at (millimetres)

#define ALTITUDE_DESIRED_HOVER_HEIGHT 1200

// Desired distance from a wall that the UAV will remain at

#define WALL_DISTANCE_DESIRED 500

// Serial port to log data on (Currently Serial or Serial3)
#define LOGGING_SERIAL_PORT Serial3

// Pin definitions
#define CONTROL_MODE_PIN A1 // HIGH = Manual, LOW = Auto
#define AUTONOMOUS_THROTTLE_PIN 38 
#define AUTONOMOUS_ROLL_PIN 40
#define AUTONOMOUS_PITCH_PIN 42
#define AUTONOMOUS_YAW_PIN 44
#define AUTONOMOUS_STABLE_MODE_PIN 46 

// Ultrasonic sensor pins reading PWM signal

#define ULTRASONIC_PIN_0 20
#define ULTRASONIC_PIN_1 19
#define ULTRASONIC_PIN_2 18

#define ULTRASONIC_ENABLE_PIN_2 17




#endif
