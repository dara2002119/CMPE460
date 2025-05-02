/**
 * @file Motor.h
 * 
 * 
 */

#include <stdint.h>
#include "Common.h"

#ifndef	_MOTOR_HEADER_FILE_
#define	_MOTOR_HEADER_FILE_


// function prototypes
void stop_DC_motors(void);
void DC_motors_init(void);
void DC_motors_enable(void);
void DC_motors_disable(void);
double bound_speed(double speed);
void left_motor_move(double speed, int direction);
void right_motor_move(double speed, int direction);
void motors_move(double speed, int direction);


#endif
