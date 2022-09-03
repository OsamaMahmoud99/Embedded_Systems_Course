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

volatile u16 c=0,flag,ton,ttotal;
volatile s32 T_total;
void  func1(void)
{
	static u16 x=0;
	if (flag==0)
	{
		ton=10;
		flag=1;
	}
	else if (flag==1)
	{
		ton=15;
		flag=2;
	}
	else if (flag==2)
	{
		ton=20;
		flag=0;
	}
}

void func2(void)
{
	static u8 c=0;
	c++;
	if (c==ton)
	{
		DIO_WritePin(PIND4,LOW);
	}
	else if (c==ttotal)
	{
		DIO_WritePin(PIND4,HIGH);
		c=0;
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
	
	Timer0_Oc_SetCallBack(func2);
	Timer0_Init(TIMER0_CTC_MODE,TIMER0_SCALER_8,OCO_DISCONNECTED);
	OCR0=99;
	LCD_WriteSentence("servo");
	ttotal=200;
	Timer0_OC_InterruptEnable();
	
	while(1)
	{
		
	}
	
	
	return 0;
}


