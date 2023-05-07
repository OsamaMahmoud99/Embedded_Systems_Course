/*
 * Sensors.c
 *
 * Created: 7/13/2022 1:01:07 PM
 *  Author: Osama
 */ 

#include "Sensors.h"


u16 LM35_GetTemp(void)
{
	u16 Temp;
	u16 volt = ADC_Get_Voltage(LM35_CHANNEL);
	
	Temp = volt;
	
	return Temp;
}

u8 POT_GetPercentage(void)
{
	u16 adc_val;
	adc_val = ADC_Read(POT_CHANNEL);
	
	u8 Resistance = ((u32)adc_val * 100)/1023;
	return Resistance;
}