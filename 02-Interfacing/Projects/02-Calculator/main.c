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

int main(void)
{
	DIO_Init();
	LCD_Init();
	
	
   u8 Key , flag = 0 , saved_key , state_flag=0 , sign_flag=0;
   u16 Number1=0 , Number2=0 , i=0;
   s64  Result=0 , Result2=0 ;
   
   LCD_GoTo(0 , 0);
   LCD_WriteSentence("Calculator");
   _delay_ms(500);
   LCD_Clear();
   LCD_GoTo(0 , 0);
   
	while (1)
	{   
		Key = KEYPAD_GetChar();
		if (Key != NOTPRESSED)
		{
				switch(Key)
				{
					case '0' ... '9':
					if (flag == 0 && sign_flag != 2)
					{
						LCD_GoTo(0 , 0);
						LCD_WriteSentence("             ");
						LCD_GoTo(0 , 0);
						flag = 1;
					}
				
					if (state_flag == 0)
					{
						LCD_WriteChar(Key);
					    Number1 = Number1*10 + Key-'0';
						sign_flag = 0;
					}
					else if (state_flag == 1)
					{
						LCD_WriteChar(Key);
						Number2 = Number2*10 + Key-'0';
					}
				
					break;
					case '+':
					if(sign_flag == 0)
					{
						LCD_WriteChar(Key);
						saved_key = '+';
						state_flag = 1;
						sign_flag = 1;
					}
					else if(sign_flag == 1)
					{
						LCD_GoTo(0 , 0);
						LCD_WriteNumber(Result);
						LCD_WriteChar(Key);
						LCD_GoTo(0 , i+1);
						LCD_WriteSentence("             ");
						LCD_GoTo(0 , i+1);
						
						saved_key = '+';
						state_flag = 1;
						Number2 = 0;
						sign_flag = 2;
					}
					
					break;
					case '-':
				    if(sign_flag == 0)
					{
						LCD_WriteChar(Key);
						saved_key = '-';
						state_flag = 1;
						sign_flag = 1;
					}
					else if(sign_flag == 1)
					{
						LCD_GoTo(0 , 0);
						LCD_WriteNumber(Result);
						LCD_WriteChar(Key);
						LCD_GoTo(0 , i+1);
						LCD_WriteSentence("             ");
						LCD_GoTo(0 , i+1);
						
						saved_key = '-';
						state_flag = 1;
						Number2 = 0;
						sign_flag = 2;
					}
					break;
					case '*':
					if(sign_flag == 0)
					{
						LCD_WriteChar(Key);
						saved_key = '*';
						state_flag = 1;
						sign_flag = 1;
					}
					else if(sign_flag == 1)
					{
						LCD_GoTo(0 , 0);
						LCD_WriteNumber(Result);
						LCD_WriteChar(Key);
						LCD_GoTo(0 , i+1);
						LCD_WriteSentence("             ");
						LCD_GoTo(0 , i+1);
						
						saved_key = '*';
						state_flag = 1;
						Number2 = 0;
						sign_flag = 2;
					}
					break;
					case '/':
					if(sign_flag == 0)
					{
						LCD_WriteChar(Key);
						saved_key = '/';
						state_flag = 1;
						sign_flag = 1;
					}
					else if(sign_flag == 1)
					{
						LCD_GoTo(0 , 0);
						LCD_WriteNumber(Result);
						LCD_WriteChar(Key);
						LCD_GoTo(0 , i+1);
						LCD_WriteSentence("             ");
						LCD_GoTo(0 , i+1);
						
						saved_key = '/';
						state_flag = 1;
						Number2 = 0;
						sign_flag = 2;
					}
					break;
					case '=':
					if ((saved_key == '+')&&(sign_flag == 1 ))
					{
						Result = (s64)Number1 + Number2;
					}
					else if ((saved_key == '+')&&(sign_flag == 2))
					{
						Result = (s64)Result + Number2;
					}
					if ((saved_key == '-')&&(sign_flag == 1 ))
					{
						Result = (s64)Number1 - Number2;
					}
					else if ((saved_key == '-')&&(sign_flag == 2))
					{
						Result = (s64)Result - Number2;
					}
					if (saved_key == '*'&&(sign_flag == 1 ))
					{
						Result = (s64)Number1 * Number2;
					}
					else if ((saved_key == '*')&&(sign_flag == 2))
					{
						Result = (s64)Result * Number2;
					}
					if (saved_key == '/'&&(sign_flag == 1 ))
					{
						Result = (s64)Number1 / Number2;
						if (Number2 != 0)
						{
							Result = (s64)Result / Number2;
						}
						else{
							LCD_GoTo(1 , 0);
							LCD_WriteSentence("Error");
						}
					}
					else if ((saved_key == '/')&&(sign_flag == 2))
					{
						if (Number2 != 0)
						{
							Result = (s64)Result / Number2;
						}
						else{
							LCD_GoTo(1 , 0);
							LCD_WriteSentence("Error");
						}
					}
				    
					if (Number2 != 0)
					{
							LCD_GoTo(1 , 0);
							LCD_WriteNumber(Result);
							LCD_WriteSentence("               ");
					}
				

					Number1 = 0;
					Number2 = 0;
					state_flag = 0;
					flag = 0;
					
					i = 0;
					Result2 = Result;
					if (Result2 < 0)
					{
						Result2 *= -1;
						i = 1;
					}
					while(Result2)
					{
						Result2 = Result2/10;
						i++;		
					}
					if (sign_flag == 2)
					{
						sign_flag = 1;
					}
					break;
					case 'c':
					LCD_Clear();
					LCD_GoTo(0 , 0);
					state_flag = 0;
					sign_flag = 0;
					break;
				}
		}
	
	}
}

