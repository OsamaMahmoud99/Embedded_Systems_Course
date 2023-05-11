/*
 * Switch.h
 *
 * Created: 7/15/2021 7:30:22 PM
 *  Author: Osama Mahmoud
 */ 


#ifndef SWITCH_H_
#define SWITCH_H_

#include "DIO_interface.h"


typedef enum{
	Open=0,
	Close
	}SWITCH_st;
	
void Switch_Direction(Port_type Port , PinNum_type Pin , PinStatus_type Direction);
SWITCH_st Switch_CheckPressed(Port_type Port , PinNum_type Pin);



#endif /* SWITCH_H_ */