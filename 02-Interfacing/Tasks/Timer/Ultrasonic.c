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
#include "SERVO_Interface.h"
#include "ULTRASONIC_Interface.h"

int main(void)
{
	sei();
	DIO_Init();
	LCD_Init();
	ULTRASONIC_Init();
	

	
	LCD_WriteSentence("Ultrasonic");
	_delay_ms(1000);
	LCD_Clear();


    u16 Distance , time;
	u8 x=0;
	while (1)
	{   
		/*LCD_GoTo(0 , 1);
		LCD_WriteNumber(c);
		LCD_GoTo( 0 , 13);
		LCD_WriteNumber(x);
		x++;
		if (x==10)
		{
			x=0;
		}
		_delay_us(200);*/
		// 4 ultrasonic
		/*Distance = ULTRASONIC_GetDistance(ULTRASONIC1);
		LCD_GoTo(1 , 0);
		LCD_WriteNumber(Distance);
		Distance = ULTRASONIC_GetDistance(ULTRASONIC2);
		LCD_GoTo(1 , 4);
		LCD_WriteNumber(Distance);
		Distance = ULTRASONIC_GetDistance(ULTRASONIC3);
		LCD_GoTo(1 , 8);
		LCD_WriteNumber(Distance);
		Distance = ULTRASONIC_GetDistance(ULTRASONIC4);
		LCD_GoTo(1 , 12);
		LCD_WriteNumber(Distance);*/
	
	    // No block
		ULTRASONIC_GetTrigger(ULTRASONIC1);
		LCD_GoTo( 0 , 13);
		LCD_WriteNumber(x);
		x++;
		if (x==10)
		{
			x=0;
		}
		_delay_us(200);
		if (ULTRASONIC_GetDistance_PeridicCheck(&Distance))
		{
			
				LCD_GoTo(1 , 0);
				LCD_WriteNumber(Distance);
			
			if (Distance > 48)
			{
				DIO_WritePin(PINC7 , HIGH);
			}
			
		}
		
		 /*Distance = ULTRASONIC_GetDistance2(ULTRASONIC1);
		 LCD_GoTo(1 , 0);
		 LCD_WriteNumber(Distance);*/
		 
		 /*Distance = ULTRASONIC_GetDistance3(ULTRASONIC1);
		 LCD_GoTo(1 , 0);
		 LCD_WriteNumber(Distance);*/
	}
}



