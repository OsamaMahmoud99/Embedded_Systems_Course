/*
 * ULTRASONIC_Interface.h
 *
 * Created: 7/25/2022 6:05:23 AM
 *  Author: Osama
 */ 


#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_

#define F_CPU     8000000
#include <Util/delay.h>
#include "MemMap.h"
#include "Utils.h"
#include "StdTypes.h"
#include "TIMER_Interface.h"
#include "DIO_Interface.h"

typedef enum
{
	ULTRASONIC1 =PINC0,
	ULTRASONIC2 =PINC1,
	ULTRASONIC3 =PINC2,
	ULTRASONIC4 =PINC3
}Ultrasonic_t;
void ULTRASONIC_Init(void);

u8 ULTRASONIC_GetDistance(Ultrasonic_t UltraNumber);  // synchronous function
u8 ULTRASONIC_GetDistance2(Ultrasonic_t UltraNumber);
u8 ULTRASONIC_GetDistance3(Ultrasonic_t UltraNumber); 

void ULTRASONIC_GetTrigger(Ultrasonic_t UltraNumber);
bool_t ULTRASONIC_GetDistance_PeridicCheck(u16*PDistance);


#endif /* ULTRASONIC_INTERFACE_H_ */