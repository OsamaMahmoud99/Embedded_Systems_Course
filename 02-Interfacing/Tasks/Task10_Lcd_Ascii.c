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

int main(void)
{
	DIO_Init();
	LCD_Init();
	
	//LCD_WriteNumber(-500);
	//LCD_WriteBinary(10);
	//LCD_WriteHex(128);
	
	u8 i = 'A';
	LCD_GoTo(0 , 0);
	LCD_WriteSentence("Ascii: ");
	LCD_GoTo(1 , 0);
	LCD_WriteSentence("char: ");
	
	while (1)
	{		
			LCD_GoTo( 0 , 8);
			LCD_WriteNumber(i);
			LCD_GoTo(1 , 8);
			LCD_WriteChar(i);
			_delay_ms(400);
			i++;
	}
}

