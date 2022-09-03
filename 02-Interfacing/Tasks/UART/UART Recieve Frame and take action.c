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
#include "ULTRASONIC_Interface.h"
#include "SERVO_Interface.h"
#include "RGB_Interface.h"
#include "KEYPAD_Interface.h"
#include "UART_Interface.h"
#include "UART_Service.h"


#define  NUMOFFUNC        3
u8 pin_num;
s8 index;

u8 Frame(u8* Str , u8* S , u8* Pnum)
{
	u8 i = 0 , Status = 1; 
	u8 digit = 0;
	u8 num = 0;
	u8 Flag = 0 , j = 0;
	
	while (Str[i] != '\0')
	{
		if (Str[i] == ',')
		{
			Flag++;
		}
		else
		{
				if(Flag == 0){
					S[j++] = Str[i];
				}
				else if(Flag == 1){
				digit = Str[i] - '0';
				num = digit + num*10;
		        }
		}
		i++;
	}
	S[j] = '\0';
	*Pnum = num;
	
	return Status;
}

void Ledon(void)
{
	SET_BIT(PORTA , pin_num);
}
void Ledoff(void)
{
	CLR_BIT(PORTA , pin_num);
}

void Servo(void)
{
	SERVO_SetAngle(pin_num);
}
u8 string_compare(u8 *str1,u8 *str2)
{
	int i;

	for(i=0; str1[i]||str2[i]; ++i)
	{
		if(str1[i] != str2[i])
		{
			return 0;
		}
	}
	return 1;
}
s8 String_Searchwithindex(u8 **arr , u8 *str)
{
	s8 i;
	for (i=0; i<NUMOFFUNC; ++i)
	{
		if (string_compare(arr[i] , str))
		{
			return i;
		}
	}
	return -1;
}
int main(void)
{
	sei();
	DIO_Init();
	UART_Init();
	LCD_Init();
	SERVO_Init();
	
	u8 str[50]={0} , s[50]={0} , status=0;
	u8 *arr[NUMOFFUNC] = {"ledon" , "ledoff" , "servo"};
	void (*Pfarr[NUMOFFUNC])(void) = {Ledon , Ledoff , Servo};
	while(1)
	{
		UART_ReceiveString(str);
	    
		status = Frame(str , s , &pin_num);
		index = String_Searchwithindex(arr , s);
		if((status==1) && (index != -1)){
			Pfarr[index]();
		}
		
	}
	
	return 0;
}


