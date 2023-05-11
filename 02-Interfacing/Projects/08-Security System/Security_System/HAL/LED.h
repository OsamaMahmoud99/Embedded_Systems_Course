/*
 * LED.h
 *
 * Created: 7/15/2021 7:31:03 PM
 *  Author: Osama Mahmoud
 */ 


#ifndef LED_H_
#define LED_H_


#include "DIO_interface.h"


typedef enum {
	ON,
	OFF
	}LED_St;
	
void LED_State(Port_type Port, PinNum_type Pin , LED_St State);	
void LED_Direction(Port_type Port , PinNum_type Pin , PinStatus_type Direction);


#endif /* LED_H_ */