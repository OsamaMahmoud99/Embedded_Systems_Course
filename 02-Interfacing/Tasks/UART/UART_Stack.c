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
#include "EXTI_Interface.h"
#include "UART_Stack.h"
#include "UART_Interface.h"

static void EX_Func(void);
static void RX_Func(void);
static volatile u8 flag = 0 , stack_flag = 0;
int main(void)
{
	sei();
	DIO_Init();
	LCD_Init();
    UART_Init();
	EXI_TriggerEdge(EX_INT0 , FALLING_EDGE);
	EXI_SetCallBack(EX_INT0 , EX_Func);
	EXI_Enable(EX_INT0);
	UART_RX_SetCallBack(RX_Func);
	UART_RX_InterruptEnable();
	
	u8 x=0 , data = 0;
	Stack_Status_Type status=DONE;

	while(1)
	{
		
		if (flag == 1)
		{
			status = Pop(&data);
			if (status == STACK_EMPTY)
			{
				LCD_GoTo(1 , 0);
				LCD_WriteSentence("Stack empty");
			}
			else if (status == DONE)
			{
				LCD_GoTo(1 , 0);
				LCD_WriteSentence("            ");
				LCD_GoTo(1 , 0);
				LCD_WriteChar(data);
			}
			flag = 0;
		}
		
		if (stack_flag == 1)
		{
			UART_SendString("stack full\r\n");
			LCD_GoTo(1 , 0);
			LCD_WriteSentence("stack full");
			stack_flag = 0;
		}
		LCD_GoTo(0 , 0);
		LCD_WriteNumber(x);
		x++;
		_delay_ms(300);
		if (x==10)
		{
			x=0;
		}
			
	}
	
	return 0;
}


static void RX_Func(void)
{
	u8 data = UART_ReceiveByteNoBlock();
	if (Push(data) == STACK_FULL)
	{
		stack_flag = 1;
	}
}

static void EX_Func(void)
{
	flag = 1;
}