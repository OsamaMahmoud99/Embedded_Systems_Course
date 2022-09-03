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
	Timer0_Init(TIMER0_PHASECORRECT_MODE,TIMER0_SCALER_8,OCO_NON_INVERTING);
	
	while(1)
	{
		if (DIO_ReadPin(PINA7)==1)
		{
			OCR0=64;     //25%
		}
		else
		{
			OCR0=127;     //50%
		}	
	}
	return 0;
}

