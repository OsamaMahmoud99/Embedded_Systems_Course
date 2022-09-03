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


int main(void)
{
	sei();
	DIO_Init();
	LCD_Init();
	UART_Init();
	

	u8 n=0 , i=0 , x;
	u8 str[255];
	LCD_GoTo(0 , 1);
	LCD_WriteSentence("Tx");
	
	while(1)
	{
		UART_ReceiveString(str);
		LCD_GoTo( 1 , 0);
		LCD_WriteSentence(str);
		LCD_WriteSentence("         ");
		UART_SendStringCheckSum(str);

	}
	
	return 0;
}

