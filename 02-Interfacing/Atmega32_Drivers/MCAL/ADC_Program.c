/*
 * ADC_Program.c
 *
 * Created: 7/13/2022 8:30:58 AM
 *  Author: Osama
 */ 


#include "ADC_Interface.h"


void ADC_Init(ADC_Vref_type vref , ADC_Scaler_type scaler)
{
	//vref
	switch(vref)
	{
		case ADC_AREF:
		CLR_BIT(ADMUX , REFS0);
		CLR_BIT(ADMUX , REFS1);
		break;
		case ADC_VCC:
		SET_BIT(ADMUX , REFS0);
		CLR_BIT(ADMUX , REFS1);
		break;
		case ADC_V256:
		SET_BIT(ADMUX , REFS0);
		SET_BIT(ADMUX , REFS1);
		break;
	}
	// prescaler
	ADCSRA = ADCSRA&0xF8;   //11111000
	ADCSRA = ADCSRA | scaler;
	
	//adjust read to right
	CLR_BIT(ADMUX , ADLAR);
	
	//adc enable
	SET_BIT(ADCSRA , ADEN);
}

u16 ADC_Read(ADC_Channel_type channel)
{
	u16 adc;
	//selcet channel
	ADMUX = (ADMUX & 0xE0)|channel;
	
	//start conversion
	SET_BIT(ADCSRA , ADSC);
	
	//wait until conversion complete
	while(READ_BIT(ADCSRA , ADSC));
	
	// read
	/*adc  = ADCL;
	adc |=(ADCH<<8);*/
	
	return ADC;
}

u16 ADC_Get_Voltage(ADC_Channel_type channel)
{
	u16 volt;
	u16 adc_val = ADC_Read(channel);
	
	volt = ((u32)adc_val*5000) / 1024;
	
	return volt;
}

static u8 read_flag = 1;

void ADC_Start_Conversion(ADC_Channel_type channel)
{
	if (read_flag == 1)
	{
		//selcet channel
	    ADMUX = (ADMUX & 0xE0)|channel;
	
	    //start conversion
	    SET_BIT(ADCSRA , ADSC);
		
		read_flag = 0;
	}

	
}
u16 ADC_GetReading()
{
	//wait until conversion complete
	while(READ_BIT(ADCSRA , ADSC));
	
	// read
	/*adc  = ADCL;
	adc |=(ADCH<<8);*/
	
	return ADC;
}

u16 ADC_GetReadingNoBlock()
{
	return ADC;	
}

bool_t ADC_GetReading_periodicCheck(u16*pdata)
{
	bool_t status;
	if (READ_BIT(ADCSRA , ADSC)==0)
	{
		*pdata = ADC;
		status = 1;
		read_flag = 1;
	}
	else
	{
		status = 0;
	}
	return status;
}