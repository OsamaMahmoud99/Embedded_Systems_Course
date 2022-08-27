/*
 * Sensors.c
 *
 * Created: 7/13/2022 1:01:07 PM
 *  Author: Osama
 */ 

#include "LM35_Interface.h"


u16 LM35_GetTemp(void)
{
	u16 Temp;
	u16 volt = ADC_Get_Voltage(LM35_CHANNEL);
	
	Temp = volt;
	
	return Temp;
}
