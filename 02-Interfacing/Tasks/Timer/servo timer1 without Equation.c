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

volatile u8 flag=0;
void func1(void)
{
	if (flag==0)
	{
		OCR1A = 999;
		flag=1;
	}
	else if (flag==1)
	{
		OCR1A = 1499;
		flag=2;
	}
	else if (flag==2)
	{
		OCR1A = 1999;
		flag=0;
	}
}

int main(void)
{
	sei();
	DIO_Init();
	EXI_Enable(EX_INT0);
	EXI_TriggerEdge(EX_INT0,FALLING_EDGE);
	LCD_Init();
	EXI_SetCallBack(EX_INT0,func1);
	
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE , TIMER1_SCALER_8 , OCRA_NON_INVERTING , OCRB_DISCONNECTED);
	ICR1 = 19999;
	LCD_WriteSentence("servo");
	while(1)
	{
		
	}
	
	return 0;
}


