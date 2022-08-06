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


#define  NUMOFFUNC        6
s8 index;
static u8 flag = 0;
u8 str[50]={0};

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
void RGB_ShowRoomMode(void)
{
	RGB_SetDuty(RED);
	
	u8 i=0;
	
	for (i=0; i<255&&flag; ++i)
	{
		OCR1A--;
		_delay_ms(5);
		OCR1B++;
		_delay_ms(5);
		if(string_compare(str , "normal"))
		{
			flag = 0;
		}
	}
	for (i=0; i<255&&flag; ++i)
	{
		OCR0++;
		_delay_ms(5);
		OCR1B--;
		_delay_ms(5);
		if(string_compare(str , "normal"))
		{
			flag = 0;
		}
	}
	for (i=0; i<255&&flag; ++i)
	{
		OCR0--;
		_delay_ms(5);
		OCR1B++;
		_delay_ms(5);
		if(string_compare(str , "normal"))
		{
			flag = 0;
		}
	}
	for (i=0; i<255&&flag; ++i)
	{
		OCR1A++;
		_delay_ms(5);
		OCR1B--;
		_delay_ms(5);
		if(string_compare(str , "normal"))
		{
			flag = 0;
		}
	}

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

void red(void)
{
	if (flag == 0)
	{
		RGB_SetDuty(RED);
	}
	
}
void green(void)
{
	if (flag == 0)
	{
		RGB_SetDuty(GREEN);
	}

}
void blue(void)
{
	if (flag == 0)
	{
		RGB_SetDuty(BLUE);
	}
	
}
void yellow(void)
{
	if (flag == 0)
	{
		RGB_SetDuty(YELLOW);
	}
	
}

void show(void)
{
	flag = 1;
	RGB_ShowRoomMode();
}

void normal(void)
{
	flag = 0;
}


int main(void)
{
	sei();
	DIO_Init();
	UART_Init();
	LCD_Init();
	
	Timer0_Init(TIMER0_FASTPWM_MODE , TIMER0_SCALER_8 , OCO_NON_INVERTING);
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE , TIMER1_SCALER_8 ,OCRA_NON_INVERTING , OCRB_NON_INVERTING);
	ICR1 = 255;
	
	u8 s[50]={0} , status=0;
	u8 *arr[NUMOFFUNC] = {"normal" , "red" , "green" , "blue" , "Yellow" , "show"};
	void (*Pfarr[NUMOFFUNC])(void) = {normal , red , green , blue , yellow , show};

    LCD_WriteSentence("RGB");
	UART_ReceiveString_Asynch(str);
	while(1)
	{
	
		   index = String_Searchwithindex(arr , str);
		   if((index != -1)){
				 Pfarr[index]();
			}
	}
	
	return 0;
}


