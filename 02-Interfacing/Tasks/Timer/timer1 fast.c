 /*
 * AVR.c
 *
 * Created: 7/4/2022 1:58:41 PM
 * Author : Osama
 */ 


#define  F_CPU    8000000
#include <util/delay.h>

#include "MemMap.h"
#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "Motor_Interface.h"
#include "LCD_Interface.h"
#include "KEYPAD_Interface.h"
#include "TIMER_Interface.h"
#include "ADC_Interface.h"



int main(void)
{
	DIO_Init();
	LCD_Init();
	ADC_Init(ADC_VCC,divfact64);
	
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8,OCRA_NON_INVERTING,OCRB_INVERTING);
	ICR1=99;
	OCR1A=39;
	OCR1B=39;
	LCD_WriteSentence("duty: ");
	LCD_GoTo(1,0);
	LCD_WriteSentence("freq:");
	u16 x=0,adc,duty,freq;
	while(1)
	{
		freq=1000000/(ICR1+1);
		duty=((OCR1A+1)*100)/(ICR1+1);
		LCD_GoTo(0,5);
		LCD_WriteNumber_3D(duty);
		LCD_GoTo(1,5);
		LCD_WriteNumber(freq);	
	}
	
	return 0;
}

