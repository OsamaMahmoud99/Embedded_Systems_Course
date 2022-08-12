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
#include "SPI_Interface.h"
#include "SPI_Service.h"

static volatile u8 flag1 = 0 , flag2 = 0; 
static void EX2_Func(void)
{
	flag1 = 1;
}
static void EX0_Func(void)
{
	flag2 = 1;
}
int main(void)
{
	sei();
	DIO_Init();
	LCD_Init();
	
	SPI_Init();
	EXI_SetCallBack(EX_INT2 , EX2_Func);
	EXI_TriggerEdge(EX_INT2 , FALLING_EDGE);
	EXI_Enable(EX_INT2);
	EXI_SetCallBack(EX_INT0 , EX0_Func);
	EXI_TriggerEdge(EX_INT0 , FALLING_EDGE);
	EXI_Enable(EX_INT0);
	
	LCD_WriteSentence("Master");
	u16 data_recv;


	while(1)
	{
		 if (flag2 == 1)
		 {
		    data_recv = SPI_SendReceive(255);
			LCD_GoTo(1 , 0);
			LCD_WriteNumber_3D(data_recv);
			flag2 = 0;
		 }
		
		if (flag1 == 1)
		{
			data_recv = SPI_SendReceive(255);
			LCD_GoTo(1 , 0);
			LCD_WriteNumber_3D(data_recv);
			flag1 = 0;
		}
	}
	return 0;
}


