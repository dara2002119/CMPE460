#include <stdint.h>
#include <stdio.h>
#include <stdlib.h> // abs() function
#include "msp.h"
#include "uart.h"
#include "Common.h"
#include "ServoMotor.h"
#include "Motor.h"
#include "CortexM.h"
#include "Lab5_Camera.h"
#include	"LEDs.h"
#include "ControlPins.h" // camera
#include "switches.h" // mode switching
#include "Timer32.h" 





void initCarParts(void){
	DisableInterrupts();
	Switch1_Init();
	Switch2_Init();
	uart0_init();
	servo_init();
	DC_motors_init();
	INIT_Camera();
	// enable the LEDs for signaling state info
	LED1_Init();
	LED2_Init();
	// enable the switches for modes

	// enable interrupts so the camera updates
	EnableInterrupts();
	//Clock_Delay1ms(10);
	
}

enum MotorDirection {
	FORWARD	= 1,
	REVERSE = 0
};

void runDiffThrust(int8_t steeringAngle, double baseSpeed, double innerWheelAngleMultiple, double outerWheelAngleMultiple){
	double innerWheelSpeed;
	double outerWheelSpeed;
	int absAngle = abs(steeringAngle);
	
	innerWheelSpeed = baseSpeed - absAngle*innerWheelAngleMultiple;
	outerWheelSpeed = baseSpeed + absAngle*outerWheelAngleMultiple;
	#ifdef MIN_SPEED
	if(baseSpeed<MIN_SPEED){
		outerWheelSpeed = MIN_SPEED;
	}
	#endif

	if (sign(steeringAngle)<0){
		//left turn
		left_motor_move(innerWheelSpeed, FORWARD);
		right_motor_move(outerWheelSpeed, FORWARD);
	} else{
		// right turn or straight
		left_motor_move(outerWheelSpeed, FORWARD);
		right_motor_move(innerWheelSpeed, FORWARD);
	}
}




int main(void) {
			BYTE trackPosLEDSW;
			BOOLEAN carArmed = FALSE;

		enum CarDirectionState{
		straight = 0,
		normal = 1,
		TurnIncoming = 2,
		turning = 3,
		trackEdge = 4,
		OffTrack = 5 
	};
			struct SetStruct{
				int speed;
				int trackMaxValue; 
				BOOLEAN SpeedScalerEnable;
				BOOLEAN DifferenceFuncEnable;
				double steeringScalar;
				double innerWheelAngle;
				double outerWheelAngle;
	};
			
		struct SetStruct mode0 = {40, 2400,FALSE,TRUE, 2.4, 0.3,0.05};
	struct CarMotorState {
		BOOLEAN MotorEnabled;
		double speed;
			BOOLEAN IsCarOnTrack1; 
		int direction;
		int threshold;
		int16_t steeringAngle;
		int16_t trackCenter;
		enum CarDirectionState trackPos;
	};
	extern uint16_t line[128];
	 uint16_t cameraAverageLine[128];
	 extern BOOLEAN g_sendData;
	

	uint8_t CameraCenterIndex;
	struct CarMotorState carState, previousCarState; 
	carState.trackPos = normal;
	carState.steeringAngle = 0;
	carState.IsCarOnTrack1 = TRUE;
	struct SetStruct Settings = mode0;
	int timeBufferms = 100;
	BOOLEAN OnTrack;
	double expectedSpeed;
	double ScaleSpeed = 1.0; 
	LED1_Init();
	//g_sendData = TRUE;
	static char str[128];

	//if(Switch1_Pressed()) {
	initCarParts();
			// Clock_Delay1ms(3);


			while (1) { 
			//	uart0_put("hi");
				int i = 0;
				if (sizeof(line) > 127) {
					g_sendData = TRUE;
					
				}
				else {
					Clock_Delay1ms(1);
				}
				camera_print();
					//uart0_put("hey");

					cameraAverage(line, cameraAverageLine);

					CameraCenterIndex = fake_center_line(cameraAverageLine);
					carState.trackCenter = cameraAverageLine[CameraCenterIndex];
					OnTrack = IsCarOnTrack(carState.trackCenter, Settings.trackMaxValue);
					carState.IsCarOnTrack1 = OnTrack;
					for (i = 0; i <128; i++) {
					sprintf(str,"%i\n\r", line[i]);
					}
					uart0_put(str);
					if (OnTrack) {
						LED1_On();
					}
					else {
						LED1_Off();
					}
				
					if(carState.trackCenter > MAXSTATE1){
				carState.trackPos = straight;
			} else if(carState.trackCenter > MAXSTATE2){
				carState.trackPos = normal;
			} else if(carState.trackCenter > MAXSTATE3){
				carState.trackPos = TurnIncoming;
			} else if(carState.trackCenter > MAXSTATE4){
				carState.trackPos = turning;
			} else if (carState.trackCenter > MAXSTATE5){
				carState.trackPos = trackEdge;
			} else{
				carState.trackPos = OffTrack;
			}
		if(carState.trackPos == trackEdge){
				carState.steeringAngle = set_steering_deg(sign(carState.steeringAngle)*SERVO_MAX_ANGLE_DEG);
		}
		if (carState.trackPos == turning ) {
			carState.steeringAngle = set_steering_deg(25);
		}
			if (carState.trackPos == straight ) {
			carState.steeringAngle = set_steering_deg(0);
		}
if(Settings.SpeedScalerEnable == TRUE){
				// scale the speed by how straight it is 
				ScaleSpeed = carState.trackCenter / 4000;
				carState.speed = Settings.speed * ScaleSpeed;
				// create a min speed during turns
				if (carState.speed < 25){
					carState.speed = 25;
				}
			}
	
if(carState.IsCarOnTrack1){ 
			previousCarState = carState;	
				DC_motors_enable();
				// determine baseline speed
				if(Settings.SpeedScalerEnable){
					expectedSpeed = carState.speed;
				} else{
					expectedSpeed = 30;
				}

				// Differential steering
				if(Settings.DifferenceFuncEnable){
					runDiffThrust(carState.steeringAngle, expectedSpeed,Settings.innerWheelAngle, Settings.outerWheelAngle);
				} else{
				// regular drive both motors same speed
					motors_move(expectedSpeed, FORWARD);
				}
			} 
	else{
				//we are off the track
				stop_DC_motors();
		set_steering_deg(0);
			
		
	}
	
		//motors_move(40, FORWARD);
		
	//	DC_motors_enable();
	//runDiffThrust(1, 1.0, 2.0, 1.0);


	}
	
}
	
