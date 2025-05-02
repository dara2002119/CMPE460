#include "msp.h"
#include "TimerA.h"
#include	"Motor.h"



void stop_DC_motors(void){
	TIMER_A0_PWM_DutyCycle(0.0,1);
	TIMER_A0_PWM_DutyCycle(0.0,2);
	TIMER_A0_PWM_DutyCycle(0.0,3);
	TIMER_A0_PWM_DutyCycle(0.0,4);
}

void DC_motors_init(void){
	

	P3 -> SEL0 &= ~BIT6;
	P3 -> SEL1 &= ~BIT6;
	P3 -> SEL0 &= ~BIT7;
	P3 -> SEL1 &= ~BIT7;
	P3	-> DIR |= BIT6; 
	P3	-> DIR |= BIT7;
	P3	-> DS |= BIT6;
	P3	-> DS |= BIT7;


	P2 -> SEL0 |= BIT4; 
	P2 -> SEL1 &= ~BIT4; 
	P2 -> SEL0 |= BIT5; 
	P2 -> SEL1 &= ~BIT5; 
	P2 -> SEL0 |= BIT6; 
	P2 -> SEL1 &= ~BIT6; 
	P2 -> SEL0 |= BIT7; 
	P2 -> SEL1 &= ~BIT7; 

	int motor_freq_Hz = 10000; 
	int motor_period = HIGH_CLOCK_SPEED/motor_freq_Hz;
	float initial_DC = 0.0; 
	TIMER_A0_PWM_Init(motor_period, initial_DC, 1);
	TIMER_A0_PWM_Init(motor_period, initial_DC, 2);
	TIMER_A0_PWM_Init(motor_period, initial_DC, 3);
	TIMER_A0_PWM_Init(motor_period, initial_DC, 4);
}

void DC_motors_enable(void){
	P3->OUT |= BIT6;	// Enable Motor 1
	P3->OUT |= BIT7;	// Enable Motor 2
}


void DC_motors_disable(void){
	P3->OUT &= ~BIT6;	// Disable Motor 1
	P3->OUT &= ~BIT7;	// Disable Motor 2
}



double bound_speed(double speed){
	if (speed > 50000){
		return 50000;
	} else{
		return speed;
	}
}



void left_motor_move(double speed, int direction){
	speed = bound_speed(speed);
	int highPin; 
	int lowPin; 
	if (direction == 0){
		lowPin = 2;
		highPin = 1;
	}else{
		lowPin = 1;
		highPin = 2;
	}
	TIMER_A0_PWM_DutyCycle(0.01*speed, highPin); 
	TIMER_A0_PWM_DutyCycle(0.0, lowPin); 
}



void right_motor_move(double speed, int direction){
	speed = bound_speed(speed);
	int highPin; 
	int lowPin; 
	if (direction == 0){
		lowPin = 4;
		highPin = 3;
	}else{
		
		lowPin = 3;
		highPin = 4;
	}
	TIMER_A0_PWM_DutyCycle(0.01*speed, highPin); 
	TIMER_A0_PWM_DutyCycle(0.0, lowPin); 
}



void motors_move(double speed, int direction){
	right_motor_move(speed,direction);
	left_motor_move(speed,direction);
}