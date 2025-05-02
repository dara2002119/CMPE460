/*
* Rochester Institute of Technology
* Department of Computer Engineering
* CMPE 460  Interfacing Digital Electronics
* LJBeato
* 1/14/2021
*
* Filename: main_timer_template.c
*/
#include <stdio.h>
#include <stdlib.h>

#include "msp.h"
#include "uart.h"
#include "leds.h"
#include "switches.h"
#include "Timer32.h"
#include "CortexM.h"
#include "Common.h"
#include "ADC14.h"
#include "ControlPins.h"
//#include "ControlPins.h"





///////////////////////////////////////////////////////
//
// NOTE: For the camera, you may want to change the default
//       clock to 48MHz
//
// To do that: Edit system_msp432p401r.c
//             Change:   #define  __SYSTEM_CLOCK    3000000
//             To:       #define  __SYSTEM_CLOCK    48000000 
// ADC will be P4.7 A6
//
// SI Pin will be P5.5 A0
//
// CLK Pin will be P5.4 A1//
//

// line stores the current array of camera data
extern uint16_t line[128];
extern BOOLEAN g_sendData;

static char str[100];

// ADC_In() gets t


// ADC will be P4.7 A6

// SI Pin will be P5.5 A0

// CLK Pin will be P5.4 A1

// main


/////////////////////////////////////////////////////
//
// simple delay function
//
//
/////////////////////////////////////////////////////
void myDelay(void)
{
	volatile int j = 0;
	for (j = 0; j < 800000; j++)
	{
		;
	}
}
/////////////////////////////////////////////////////
//
// INIT_Camera function
//
//
/////////////////////////////////////////////////////
void INIT_Camera(void)
{
	uart0_init();
	g_sendData = FALSE;
	ControlPin_SI_Init();
	ControlPin_CLK_Init();
	ADC0_InitSWTriggerCh6();
	
}

uint8_t fake_center_line(uint16_t* cameraAverage){
	double x = 0.0;
	double y = 0.0;
	
	for(int i = 0; i < 128; i++){
		x += cameraAverage[i]*i; // is weighted by the multiplication
		y += cameraAverage[i];
	}

	return (uint8_t) (x/y);
}



	void cameraAverage(uint16_t* rawData, uint16_t* cameraAverageLine){
	uint16_t avg;
		uart0_init();
		uart0_put("we");


	for(int j = 0; j < 128; j++){
		avg = ( rawData[j+2] + rawData[j+1] + rawData[j] + rawData[j-1] + rawData[j-2])/5;
		cameraAverageLine[j] = avg;
	}
}
	BOOLEAN IsCarOnTrack(uint16_t CameraMax, uint16_t MaxTrackValue){
	if (CameraMax > MaxTrackValue){
		
		return TRUE; //car is on the track
	} else{
		return FALSE; //car is off track
	}
}




/////////////////////////////////////////////////////
//
// main function
//
//
/////////////////////////////////////////////////////
int camera_print(void)
{
int i = 0;
	//initializations
//	DisableInterrupts();
//	uart0_init();
//	uart0_put("\r\nLab5 CAMERA demo\r\n");

	
//	uart0_put("\r\nINIT LEDs\r\n");
//	LED1_Init();
//	LED2_Init();
	// remember that we double the desired frequency because we need to account

//	uart0_put("\r\nINIT Camera CLK and SI\r\n");
//	uart0_put("\r\nINIT ADC\r\n");	
//	INIT_Camera();
	
//	uart0_put("\r\nINIT Switch 2\r\n");
	//Switch2_Init();


//	uart0_put("\r\nEnable Interrupts\r\n");
//	EnableInterrupts();
//	uart0_put("\r\nInterrupts successfully enabled\r\n");

//	while(1)
	//{

	//	if (g_sendData == TRUE) 
	//	{
	//		LED1_On();
			// send the array over uart
//			sprintf(str,"%i\n\r",-1); // start value
	//		uart0_put(str);
	for (i = 0; i < 128; i++) 
		{
				sprintf(str,"%i\n\r", line[i]);
				uart0_put(str);
			}
	//		sprintf(str,"%i\n\r",-2); // end value
	//		uart0_put(str);
	//		LED1_Off();
	//		g_sendData = FALSE;
//		}
		// do a small delay
//		myDelay();
	//}
			return 0;
}
