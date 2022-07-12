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


#define SPACE_HEX      5
#define SPACE_BINARY   10

int main(void)
{
	DIO_Init();
	LCD_Init();
	
	
   u8 Key , flag = 0 , state_flag = 0 , saved_key , converted_key , i=0 , H=0;
   u8 space_hex = SPACE_HEX , space_bin = SPACE_BINARY;
   u16 Number=0;
   LCD_GoTo(0 , 0);
   LCD_WriteSentence("Hello Osama");
   _delay_ms(1000);
   LCD_Clear();
   
	while (1)
	{   
		if (state_flag == 0)
		{
			    LCD_GoTo(0 , 0);
				LCD_WriteSentence("convert from");
		        LCD_GoTo(1 , 0);
		        LCD_WriteSentence("1 D   2 H    3 B");
		}
	
		if (state_flag == 0)
		{
				Key = KEYPAD_GetChar();
				if (Key != NOTPRESSED)
				{
						switch(Key)
						{
							case '1':
							LCD_Clear();
							LCD_GoTo(0 , 0);
							LCD_WriteSentence("convert D to");
							LCD_GoTo(1, 0);
							LCD_WriteSentence("1 D   2 H    3 B");
						    saved_key = 'D';
							break;
							case '2':
							LCD_Clear();
							LCD_GoTo(0 , 0);
							LCD_WriteSentence("convert H to");
							LCD_GoTo(1, 0);
							LCD_WriteSentence("1 D   2 H    3 B");
							saved_key = 'H';
							break;
							case '3':
							LCD_Clear();
							LCD_GoTo(0 , 0);
							LCD_WriteSentence("convert B to");
							LCD_GoTo(1, 0);
							LCD_WriteSentence("1 D   2 H    3 B");
							saved_key = 'B';
							break;
						}
						if (Key>='1'&&Key<='3')
						{
							state_flag = 1;	
						}
						else{
							LCD_Clear();
							LCD_GoTo(0 , 0);
							LCD_WriteSentence("wrong choice");
							_delay_ms(500);
						}
					
				}
			}
			
		if (state_flag == 1)
		{
				Key = KEYPAD_GetChar();
				if (Key != NOTPRESSED)
				{		
		                switch(Key)
						{
							case '1':
							LCD_Clear();
							LCD_GoTo(0 , 0);
						    LCD_WriteChar(saved_key);
							LCD_GoTo(0 , 2);
							LCD_WriteChar(':');
							LCD_GoTo(1, 0);
							LCD_WriteChar('D');
							LCD_GoTo(1 , 2);
							LCD_WriteChar(':');
							converted_key = 'D';
							break;
							case '2':
							LCD_Clear();
							LCD_GoTo(0 , 0);
							LCD_WriteChar(saved_key);
							LCD_GoTo(0 , 2);
							LCD_WriteChar(':');
							LCD_GoTo(1, 0);
							LCD_WriteChar('H');
							LCD_GoTo(1 , 2);
							LCD_WriteChar(':');
							converted_key = 'H';
							break;
							case '3':
							LCD_Clear();
							LCD_GoTo(0 , 0);
							LCD_WriteChar(saved_key);
							LCD_GoTo(0 , 2);
							LCD_WriteChar(':');
							LCD_GoTo(1, 0);
							LCD_WriteChar('B');
							LCD_GoTo(1 , 2);
							LCD_WriteChar(':');
							converted_key = 'B';
							break;
						}
						state_flag = 2;
				}
			}
	
	     if (state_flag == 2)
	     {
			Key = KEYPAD_GetChar();
			if (Key != NOTPRESSED)
			{
				if (saved_key == 'D')
				{
					if (converted_key == 'B' || converted_key == 'H')
					{
						if (Key>='0'&&Key<='9')
						{
							if (flag == 0)
							{
								LCD_GoTo(0 , 4);
								LCD_WriteSentence("        ");
								LCD_GoTo(0 , 4);
								flag = 1;
							}
							LCD_WriteChar(Key);
							Number = Number*10 + Key-'0';
						}
						if (Key == '=')
						{
								LCD_GoTo(1 , 4);
								if (converted_key == 'B')
								{
									LCD_WriteBinary(Number);
								}
								else if (converted_key == 'H')
								{
									LCD_WriteHex(Number);
								}
								
								LCD_WriteSentence("      ");
								Number = 0;
								flag = 0;
						}
					
					}
				}
				else if (saved_key == 'B')
				{
					if (converted_key == 'D' || converted_key == 'H')
					{
						if (Key>='0'&&Key<='1')
						{
							if (flag == 0)
							{
								LCD_GoTo(0 , 3);
								LCD_WriteSentence("        ");
								LCD_GoTo(0 , 3);
								flag = 1;
							}
							LCD_GoTo(0 , space_bin--);
							LCD_WriteChar(Key);
							Number = ((Key-'0')<<i)+Number;
							i++;
						}
						if (Key == '=')
						{
								LCD_GoTo(1 , 10);
								if (converted_key == 'D')
								{
									LCD_WriteNumber(Number);
								}
								else if (converted_key == 'H')
								{
									LCD_WriteHex(Number);
								}
								LCD_WriteSentence("         ");
								Number = 0;
								flag = 0;
								i=0;
								space_bin = SPACE_BINARY;
						}
					}
				}
				else if (saved_key == 'H')
				{
					if (converted_key == 'D' || converted_key == 'B')
					{
						if ((Key>='A'&&Key<='F'))
						{
							if (flag == 0)
							{
								LCD_GoTo(0 , 3);
								LCD_WriteSentence("        ");
								LCD_GoTo(0 , 3);
								flag = 1;
							}
							LCD_GoTo(0 , space_hex--);
							LCD_WriteChar(Key);
							Number = ((Key+10-'A')<<H)+Number;
							H = H+4;
						}
						else if ((Key>='0'&&Key<='9'))
						{
							if (flag == 0)
							{
								LCD_GoTo(0 , 3);
								LCD_WriteSentence("        ");
								LCD_GoTo(0 , 3);
								flag = 1;
							}
							LCD_GoTo(0 , space_hex--);
							LCD_WriteChar(Key);
							Number = ((Key-'0')<<H)+Number;
							H = H+4;
							
						}
						if (Key == '=')
						{
							LCD_GoTo(1 , 4);
							if (converted_key == 'D')
							{
								LCD_WriteNumber(Number);
							}
							else if (converted_key == 'B')
							{
								LCD_WriteBinary(Number);
							}
							LCD_WriteSentence("           ");
							Number = 0;
							flag = 0;
							space_hex=SPACE_HEX;
							H=0;
						}
				 }
	         }
			 
			 if (Key == 'c')
			 {
				 state_flag = 0;
			 }
		 }
	 }
  }
}

