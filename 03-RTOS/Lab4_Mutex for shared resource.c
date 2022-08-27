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
#include "semphr.h"


void T_SMS(void *param);
void T_Server(void *param);
void System_Init(void);

/* Os Services */
xSemaphoreHandle  bs_GSM = NULL;

int main(void)
{
	System_Init();
	/* create tasks */
	
	xTaskCreate(&T_SMS , NULL , 100 , NULL , 2 , NULL);
	xTaskCreate(&T_Server , NULL , 100 , NULL , 3 , NULL);
	
	/* create semaphore */
	bs_GSM = xSemaphoreCreateMutex();
	
	/* start os */
	vTaskStartScheduler();
	
	while (1)
	{
	}
}


void T_SMS(void *param)
{
	while(1)
	{
		if (xSemaphoreTake(bs_GSM , portMAX_DELAY))
		{
			UART_SendString("AT+SMS1 \r\n");
			UART_SendString("AT+SMS2 \r\n");
			xSemaphoreGive(bs_GSM);
		}	
	}
}
void T_Server(void *param)
{
	while(1)
	{
		if (xSemaphoreTake(bs_GSM , portMAX_DELAY))
		{
			UART_SendString("AT+Server1 \r\n");
			UART_SendString("AT+Server2 \r\n");
			xSemaphoreGive(bs_GSM);
			vTaskDelay(5);
		}	
	}
}

void System_Init()
{
	DIO_Init();
	UART_Init();
	UART_SendString("System start \r\n");
}