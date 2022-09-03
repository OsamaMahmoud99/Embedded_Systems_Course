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

volatile u8 data[20] , flag=0;

void RX_Func(void)
{
	static u8 i = 0;
	data[i] = UART_ReceiveByteNoBlock();
	i++;
	flag++;
}
int main(void)
{
	sei();
	DIO_Init();
	LCD_Init();
	
	UART_RX_SetCallBack(RX_Func);
	UART_RX_InterruptEnable();
	UART_Init();
	LCD_WriteSentence("Uart Init");
	
	
	u8 i=0,x=0;
	
	while(1)
	{
		if (flag > 0)
		{
			LCD_GoTo(1 , i);
					
			LCD_WriteChar(data[i]);
			i++;
			flag--;
		}
		
		LCD_GoTo(0 , 11);
		LCD_WriteNumber(x);
		x++;
		if (x == 10)
		{
			x = 0;
		}
		_delay_ms(200);

	}
	
	return 0;
}


