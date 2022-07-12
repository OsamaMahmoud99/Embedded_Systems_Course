/*
 * KEYPAD_Program.c
 *
 * Created: 7/10/2022 4:32:40 PM
 *  Author: Osama
 */ 

#include "KEYPAD_Interface.h"

u8 KEYPAD_GetChar(void)
{
	u8 R , C , Key = NOTPRESSED;
	
	DIO_WritePin(FIRST_OUTPUT , HIGH);
	DIO_WritePin(FIRST_OUTPUT+1 , HIGH);
	DIO_WritePin(FIRST_OUTPUT+2 , HIGH);
	DIO_WritePin(FIRST_OUTPUT+3 , HIGH);
	
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
	
	return Key;
}