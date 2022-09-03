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
#include "Timer_Service.h"


void func1(void)
{
	DIO_TogglePin(PINB0);
}
int main(void)
{
	sei();
	DIO_Init();
	LCD_Init();
	Timer1_SetInterruptTime_ms(60 , func1);
	LCD_GoTo(0,0);
	LCD_WriteNumber(OCR1A);
	while(1)
	{
		
	}
	
	return 0;
}

