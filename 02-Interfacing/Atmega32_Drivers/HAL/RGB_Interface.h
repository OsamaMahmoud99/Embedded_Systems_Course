/*
 * RGB_Interface.h
 *
 * Created: 7/26/2022 7:22:31 PM
 *  Author: Osama
 */ 


#ifndef RGB_INTERFACE_H_
#define RGB_INTERFACE_H_

#include "MemMap.h"
#include "StdTypes.h"

#define  R      0
#define  G      1
#define  B      2

typedef enum
{
	RED=0,
	GREEN,
	BLUE,
	YELLOW,
	CYAN,
	MAGENTA,
	BLACK,
	WHITE, 
	GRAY,   
	PURPLE,
	NUMColors 	
}Color_t;

void RGB_SetDuty(Color_t color);

#endif /* RGB_INTERFACE_H_ */