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

u32 is_change(u32 x)
{
	static u32 t=0;
	if(x==t)return 0;
	else{t=x;return 1;}
}
volatile u16 freq=1000;
void func1(void)
{
	freq+=1000;
}
void func2(void)
{
	freq-=1000;
}
int main(void)
{
	sei();
	DIO_Init();
	LCD_Init();
	EXI_SetCallBack(EX_INT0,func1);
	EXI_TriggerEdge(EX_INT0,FALLING_EDGE);
	EXI_Enable(EX_INT0);
	EXI_SetCallBack(EX_INT1,func2);
	EXI_TriggerEdge(EX_INT1,FALLING_EDGE);
	EXI_Enable(EX_INT1);
	ADC_Init(ADC_VCC,divfact64);
	LCD_WriteSentence("PWM");
	PWM_Init();
	
	u16 adc,duty;
	while(1)
	{
		PWM_Freq_HZ(freq);
		if (is_change(freq))
		{
			LCD_GoTo(1,0);
			LCD_WriteSentence("      ");
		}
		LCD_GoTo(1,0);
		LCD_WriteNumber(freq);
		adc=ADC_Read(ADC7);
		duty=((u32)adc*100)/1023;
		PWM_Duty(duty);
		LCD_GoTo(1,7);
		LCD_WriteNumber_3D(duty);
	}
	return 0;
}
