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

int main(void)
{
	sei();
	DIO_Init();
    LCD_Init();
	Timer1_Init(TIMER1_NORMAL_MODE , TIMER1_SCALER_8 , OCRA_DISCONNECTED , OCRB_DISCONNECTED);
	u32 freq=0;
	u8 duty=0;
    LCD_WriteSentence("freq:");
	LCD_GoTo(1,0);
	LCD_WriteSentence("duty:");

	
	while(1)
	{
		PWM_Measure(&freq , &duty);
		LCD_GoTo(0,6);
		LCD_WriteNumber_4D(freq);
		LCD_GoTo(1,6);
		LCD_WriteNumber_3D(duty);
	}
	
	return 0;
}

