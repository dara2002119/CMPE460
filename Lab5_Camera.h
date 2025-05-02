#include <stdint.h>
#include "Common.h"

#ifndef _CAMERA_HEADER_FILE_
#define _CAMERA_HEADER_FILE_

 /* Function prototypes */ 
void INIT_Camera(void);
	void cameraAverage(uint16_t* line, uint16_t* cameraAverageLine);
		BOOLEAN IsCarOnTrack(uint16_t CameraMax, uint16_t MaxTrackValue);
		int camera_print(void)

#define MAXSTATE1		(12000)
#define MAXSTATE2		(10000)
#define MAXSTATE3		(7000)
#define MAXSTATE4		(4000)
#define MAXSTATE5			(3500)
#endif
		