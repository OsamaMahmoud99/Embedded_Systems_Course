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

volatile u16 c;

int main(void)
{
	DIO_Init();
	LCD_Init();
	
	
	LCD_WriteSentence("Timer");
	sei();
	u16 num2;
	
    TCCR0 = 3;
    TIMSK = 1;
	u8 num = 0;
	u16 time;
	TCNT0 = 0;
	for (u8 i=0; i<100; ++i)
	{
		_delay_us(3);
	}
	
	time = c*256 + TCNT0;
	TIMSK = 0;
	LCD_GoTo(0 , 10);
	LCD_WriteNumber(time);
	LCD_GoTo(1 , 10);
	LCD_WriteNumber(c);
	
	/*DIO_WritePin(PINB5 , HIGH);
	_delay_ms(10);
	DIO_WritePin(PINB5 , LOW);
	*/
	while (1)
	{   
			LCD_GoTo(1 , 0);
			LCD_WriteNumber(num);
			num++;
			if (num == 10)
			{
				num = 0;
			}
			_delay_us(200);
		
	}
}

ISR(TIMER0_OVF_vect)
{
	c++;
	//c = TCNT0;
}

