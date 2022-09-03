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
#include "ADC_Interface.h"
#include "EXTI_Interface.h"


void func1(void)
{
	DIO_TogglePin(PINB7);
}

int main(void)
{
	sei();
	DIO_Init();
	LCD_Init();
	
    EXI_TriggerEdge(EX_INT0 , FALLING_EDGE);
	EXI_Enable(EX_INT0);
	EXI_TriggerEdge(EX_INT1 , RISING_EDGE);
	EXI_Enable(EX_INT1);
    EXI_SetCallBack(EX_INT0 , func1); 
	LCD_WriteSentence("interrupt");
	_delay_ms(1000);
	LCD_Clear();
	
	u8 x=0; 
	while (1)
	{   
		LCD_GoTo(0 , 10);
		LCD_WriteNumber(x);
		x++;
		_delay_ms(400);
		if (x == 10)
		{
			DIO_WritePin(PIND2 , HIGH);
			_delay_ms(100);
			DIO_WritePin(PIND2 , LOW);
			x = 0;
		}
	}
}

