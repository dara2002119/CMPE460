#include <stdint.h>
#include "Common.h"

#ifndef _SERVOMOTOR_HEADER_FILE_
#define _SERVOMOTOR_HEADER_FILE_

#define SERVO_MAX_ANGLE_DEG 	(60)
#define SERVO_PWM_FREQ_HZ 		(50)
#define SERVO_PWM_PERIOD_MS	(20)


#define SERVO_CLK 				(3000000)

 int sign(int x);
 int fsign(float x);
 int 	ibound_steering_angle(int steeringAngle);
 float fbound_steering_angle(float steeringAngle);
 void servo_init(void);
 void set_servo_pulse(double servoDC);
 int8_t set_steering_deg(int16_t steeringAngle);

 
 #endif
 