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
#include "LCD_Interface.h"
#include "TIMER_Interface.h"
#include "EXTI_Interface.h"
#include "ADC_Interface.h"

void func1(void)
{
	static u8 Angle=0;
	OCR1A = 999+((u32)Angle*1000)/180;
	Angle += 9;
}

int main(void)
{
	sei();
	DIO_Init();
	EXI_Enable(EX_INT0);
	EXI_TriggerEdge(EX_INT0,FALLING_EDGE);
	LCD_Init();
	EXI_SetCallBack(EX_INT0,func1);
	ADC_Init(ADC_VCC , divfact64);
	
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE , TIMER1_SCALER_8 , OCRA_NON_INVERTING , OCRB_NON_INVERTING);
	ICR1 = 19999;
	LCD_WriteSentence("servo");
	_delay_ms(500);
	LCD_Clear();
	
	u16 adc , angle;
	while(1)
	{
			LCD_GoTo(0,0);
			adc=ADC_Read(ADC7);
			LCD_WriteNumber_4D(adc);
			angle=((u32)adc*180)/1023;
			OCR1B=999+((u32)angle*1000)/180;
			LCD_GoTo(1,0);
			LCD_WriteNumber_3D(angle);
	}
	
	return 0;
}


