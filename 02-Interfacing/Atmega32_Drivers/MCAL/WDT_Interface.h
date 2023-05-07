/*
 * WDT_Interface.h
 *
 * Created: 8/6/2022 1:17:32 PM
 *  Author: Osama
 */ 


#ifndef WDT_INTERFACE_H_
#define WDT_INTERFACE_H_

#include "MemMap.h"
#include "StdTypes.h"
#include "Utils.h"


typedef enum
{
	timeout_16ms=0,
	timeout_32ms,
	timeout_65ms,
	timeout_130ms,
	timeout_260ms,
	timeout_520ms,
	timeout_1000ms,
	timeout_2100ms,
	
}timeout_type;

void WDT_Set(timeout_type time);
void WDT_Stop(void);




#endif /* WDT_INTERFACE_H_ */