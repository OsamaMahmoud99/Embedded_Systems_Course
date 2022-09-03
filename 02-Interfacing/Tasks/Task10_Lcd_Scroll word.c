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
	
	/*u8 i = 'A';
	LCD_GoTo(0 , 0);
	LCD_WriteNumber_4D(999);
	*/
	
	//sprintf(str , "osama");
	u8 str[100] = "OsamaMahmoud";


	u8 Len = 0;
	while(str[Len])
	Len++;
	
	while (1)
	{	
	
		for (u8 i=Len; i>=1; --i)
		{
			LCD_GoTo(0 , 0);
			LCD_WriteSentence(str+i-1);
			_delay_ms(500);
			if (i!=1)
			{
				LCD_Clear();
			}
			
		}
		LCD_Scroll(16);
	
		for(u8 i=Len; i>=1; --i)
		{
			LCD_GoTo(1 , 0);
			LCD_WriteSentence(str+i-1);
			_delay_ms(500);
			if (i!=1)
			{
				LCD_Clear();
			}
		}
		LCD_Scroll(16);
	}
}

