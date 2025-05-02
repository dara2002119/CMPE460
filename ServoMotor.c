#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "msp.h"
#include "TimerA.h"
#include "ServoMotor.h"

#define CENTER_VAL 0.075
double oneDegDC = 0.5/SERVO_MAX_ANGLE_DEG;



void servo_init(void){
	uint16_t timerPeriod = SystemCoreClock/15;
	double servoStraightDC = 1.5/SERVO_PWM_PERIOD_MS;
	
	// start with servo straight -> initialize to 1.5 ms
	TIMER_A2_PWM_Init(timerPeriod, servoStraightDC, 1); 
}



void set_servo_pulse(double servoPulse){
	double servoDC = servoPulse/SERVO_PWM_PERIOD_MS;
	TIMER_A2_PWM_DutyCycle(servoDC, 1);
}



int sign(int x) {
    return (x > 0) - (x < 0);
}


int fsign(float x) {
    return (x > 0) - (x < 0);
}



float fbound_steering_angle(float steeringAngle){
	int direction = fsign(steeringAngle);
	// make sure that it is within the correct bounds
	if (fabs(steeringAngle) > SERVO_MAX_ANGLE_DEG){
		if(direction == -1){
			steeringAngle = -SERVO_MAX_ANGLE_DEG;
		} else{
			steeringAngle = SERVO_MAX_ANGLE_DEG;
		}
	}
	return steeringAngle;
}



int ibound_steering_angle(int steeringAngle){
	int direction = sign(steeringAngle);
	if (abs(steeringAngle) > SERVO_MAX_ANGLE_DEG){
		if(direction == -1){
			steeringAngle = -SERVO_MAX_ANGLE_DEG;
		} else{
			steeringAngle = SERVO_MAX_ANGLE_DEG;
		}
	}
	return steeringAngle;
}



int8_t set_steering_deg(int16_t steeringAngle){
	steeringAngle = ibound_steering_angle(steeringAngle);
	
	double servoPulse= 1.5 +  (steeringAngle * oneDegDC);
	set_servo_pulse(servoPulse);
	return steeringAngle;
}