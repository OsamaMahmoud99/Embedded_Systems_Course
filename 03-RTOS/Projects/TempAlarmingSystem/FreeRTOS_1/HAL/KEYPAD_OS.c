/*
 * KEYPAD_OS.c
 *
 * Created: 8/29/2022 12:35:37 PM
 *  Author: Osama
 */ 

#include "KEYPAD_OS.h"

static u8 Key;

void KEYPAD_OS_Task(void *param)
{

	u8 R , C;
	/* set rows to high */
	DIO_WritePin(FIRST_OUTPUT , HIGH);
	DIO_WritePin(FIRST_OUTPUT+1 , HIGH);
	DIO_WritePin(FIRST_OUTPUT+2 , HIGH);
	DIO_WritePin(FIRST_OUTPUT+3 , HIGH); 
	
	while(1)
	{
		Key = NOTPRESSED;
		for(R=0; R<ROW; ++R)
		{
			DIO_WritePin(FIRST_OUTPUT+R , LOW);
			
			for (C=0; C<COL; ++C)
			{
				if (DIO_ReadPin(FIRST_INPUT+C) == LOW)
				{
					Key = keypadchars[R][C];
					while(DIO_ReadPin(FIRST_INPUT+C) == LOW);
				}
			}
			DIO_WritePin(FIRST_OUTPUT+R , HIGH);
		}
		vTaskDelay(200);
	}
	
}
u8 KEYPAD_GetChar(void)
{
	return Key;
}


