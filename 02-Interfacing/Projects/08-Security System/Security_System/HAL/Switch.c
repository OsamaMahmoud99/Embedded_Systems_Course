
/*
 * Switch.c
 *
 * Created: 7/15/2021 7:29:58 PM
 *  Author: Osama Mahmoud
 */ 

#include "Switch.h"

void Switch_Direction(Port_type Port , PinNum_type Pin , PinStatus_type Direction){
	
	switch(Port)
	{
		case PA:
		     DIO_setpinDirection(PA , Pin%8 , INPUT);
			 break;
		case PB:
		     DIO_setpinDirection(PB , Pin%8 , INPUT);
			 break;
		case PC:
		     DIO_setpinDirection(PC , Pin%8 , INPUT);
		     break;
		case PD:
		     DIO_setpinDirection(PD , Pin%8 , INPUT);
		     break;
	}
}
SWITCH_st Switch_CheckPressed(Port_type Port , PinNum_type Pin){
	
	SWITCH_st Value = Open;
	switch(Port)
	{
		case PA:
		     Value = DIO_Getpinvalue(PA , Pin%8);
		     break;
		case PB:
		     Value = DIO_Getpinvalue(PB , Pin%8);
			 break;
		case PC:
		     Value = DIO_Getpinvalue(PC , Pin%8);
			 break;
		case PD:
		     Value = DIO_Getpinvalue(PD , Pin%8);
			 break; 
	}
	return Value;
}