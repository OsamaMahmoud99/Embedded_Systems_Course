/*
 * FreeRTOS_1.c
 *
 * Created: 8/21/2022 9:44:16 AM
 * Author : Osama
 */ 

#include "StdTypes.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "UART_Service.h"


#include "FreeRTOS.h"
#include "task.h"



void T_1(void *param);
void T_2(void *param);
void T_3(void *param);
void T_4(void *param);
void System_Init(void);

int main(void)
{
	System_Init();
	/* create tasks */
	xTaskCreate(&T_1 , NULL , 100 , NULL , 1 , NULL);
	xTaskCreate(&T_2 , NULL , 100 , NULL , 2 , NULL);
	xTaskCreate(&T_3 , NULL , 100 , NULL , 3 , NULL);
	xTaskCreate(&T_4 , NULL , 100 , NULL , 4 , NULL);
	
	/* start os */
	vTaskStartScheduler();
	
	while (1)
	{
	}
}

void T_1(void *param)
{
	UART_SendString("T1 started \r\n");
	while(1)
	{
		
	}
}
void T_2(void *param)
{
	UART_SendString("T2 started \r\n");
	while(1)
	{
		
	}
}
void T_3(void *param)
{
	UART_SendString("T3 started \r\n");
	while(1)
	{

	}
}

void T_4(void *param)
{
	UART_SendString("T4 started \r\n");
	while(1)
	{
		UART_SendString("T4 \r\n");
		vTaskDelay(1000);
	}
}
void System_Init()
{
	DIO_Init();
	UART_Init();
	UART_SendString("System start \r\n");
}