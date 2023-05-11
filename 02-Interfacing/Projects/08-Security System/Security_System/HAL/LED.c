/*
 * LED.c
 *
 * Created: 7/15/2021 7:31:18 PM
 *  Author: Osama Mahmoud
 */ 

#include "LED.h"


void LED_Direction(Port_type Port , PinNum_type Pin , PinStatus_type Direction){
	
	switch(Port)
	{
		case PA:
	         DIO_setpinDirection(PA , Pin%8 , OUTPUT);
			 break;
		case PB:
		     DIO_setpinDirection(PB , Pin%8 , OUTPUT);
		     break;
		case PC:
		     DIO_setpinDirection(PC , Pin%8 , OUTPUT);
		     break;
		case PD:
		     DIO_setpinDirection(PD , Pin%8 , OUTPUT);
		     break;  
	}
}

void LED_State(Port_type Port , PinNum_type Pin , LED_St State){
	
	switch(Port)
	{
		case PA:
		     if (State == ON)
	     	 {
			    DIO_setpinvalue(PA , Pin%8 , HIGH);
		     }
		     else
		     {
			    DIO_setpinvalue(PA , Pin%8 , LOW);
		     }
		     break;
		case PB:
		     if (State == ON)
		     {
		 	    DIO_setpinvalue(PB , Pin%8 , HIGH);
		     }
		     else
		     {
			    DIO_setpinvalue(PB , Pin%8 , LOW);
		     }
		     break;
		case PC:
		     if (State == ON)
		     {
			    DIO_setpinvalue(PC , Pin%8 , HIGH);
		     }
		     else
		     {
			    DIO_setpinvalue(PC , Pin%8 , LOW);
		     }
		     break;
		case PD:
		     if (State == ON)
		     {
			    DIO_setpinvalue(PD , Pin%8 , HIGH);
		     }
		     else
		     {
			    DIO_setpinvalue(PD , Pin%8 , LOW);
		     }
		     break;
	}
}