/*
 * ADC_Interface.h
 *
 * Created: 7/13/2022 8:31:18 AM
 *  Author: Osama
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


#include "Utils.h"
#include "StdTypes.h"

typedef enum
{
	ADC_AREF,
	ADC_VCC,
	ADC_V256
}ADC_Vref_type;

typedef enum
{
	divfact2=0,
	divfact4=2,
	divfact8,
	divfact16,
	divfact32,
	divfact64,
	divfact128,
	
}ADC_Scaler_type;

typedef enum
{
	ADC0=0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7
}ADC_Channel_type;

void ADC_Init(ADC_Vref_type vref , ADC_Scaler_type scaler);

u16 ADC_Read(ADC_Channel_type channel);

u16 ADC_Get_Voltage(ADC_Channel_type channel);
u16 ADC_Get_MilliVoltage(ADC_Channel_type channel);


void ADC_Start_Conversion(ADC_Channel_type channel);
u16 ADC_GetReading(void);
u16 ADC_GetReadingNoBlock(void);

bool_t ADC_GetReading_periodicCheck(u16*pdata);

#endif /* ADC_INTERFACE_H_ */