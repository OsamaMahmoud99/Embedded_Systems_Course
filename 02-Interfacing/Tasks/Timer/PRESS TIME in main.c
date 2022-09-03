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
#include "EXTI_Interface.h"

volatile u16 c=0;
volatile u8 flag=0;
volatile u16 time , t1 , t2;


void exti_func(void)
{
	if (flag == 0)
	{
		t1 = TCNT0;
		c=0;
		EXI_TriggerEdge(EX_INT0 , RISING_EDGE);
		flag = 1;
	}
	else if (flag == 1)
	{
		t2 = TCNT0;
		EXI_TriggerEdge(EX_INT0 , FALLING_EDGE); 
		flag = 2;
		Timer1_OVF_InterruptDisable();
	}
}

void func_Ov(void)
{
	c++;
}
int main(void)
{
	sei();
	DIO_Init();
	LCD_Init();
	
	Timer0_OVF_SetCallBack(func_Ov);
	EXI_SetCallBack(EX_INT0 , exti_func);
	EXI_TriggerEdge(EX_INT0 , FALLING_EDGE);
	Timer0_Init(TIMER0_NORMAL_MODE , TIMER0_SCALER_8 , OCO_DISCONNECTED);
	Timer0_OV_InterruptEnable();
	EXI_Enable(EX_INT0);
	
	u8 x=0;
	while (1)
	{   
		LCD_GoTo(1 , 0);
		LCD_WriteNumber(x);
		x++;
		if (x==10)
		{
			x=0;
		}
		_delay_ms(300);
		if (flag == 2)
		{
			LCD_GoTo(1 , 3);
			LCD_WriteSentence("         ");
			time = (t2-t1+((u32)c*256))/1000;
			LCD_GoTo(1 , 3);
			LCD_WriteNumber(time/1000);
			LCD_WriteChar('.');
			LCD_WriteNumber(time%1000);
			flag = 0;
			Timer0_OV_InterruptEnable();
		}
	
	}
}



