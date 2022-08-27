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


void T_Low(void *param);
void T_UserInput(void *param);
void T_UserAction(void *param);
void System_Init(void);

/* Os Services */
xSemaphoreHandle  sem_buttonpressed = NULL;

int main(void)
{
	System_Init();
	/* create tasks */
	
	xTaskCreate(&T_Low , NULL , 100 , NULL , 1 , NULL);
	xTaskCreate(&T_UserInput , NULL , 100 , NULL , 2 , NULL);
	xTaskCreate(&T_UserAction , NULL , 100 , NULL , 3 , NULL);
	
	/* create semaphore */
	sem_buttonpressed = xSemaphoreCreateBinary();

	/* start os */
	vTaskStartScheduler();
	
	while (1)
	{
	}
}

void T_Low(void *param)
{
	UART_SendString("T_Low started \r\n");
	
	while(1)
	{
		UART_SendString("T_Low \r\n");
		vTaskDelay(1000);
	}
}

void T_UserInput(void *param)
{
	
	while(1)
	{
		if (DIO_ReadPin(PINB_0) == 0)
		{
			xSemaphoreGive(sem_buttonpressed);  // sem = 1
			while(DIO_ReadPin(PINB_0)==0)
			{
				vTaskDelay(50);
			}
		}
		vTaskDelay(50);
		
	}
}
void T_UserAction(void *param)
{

	while(1)
	{
		if (xSemaphoreTake(sem_buttonpressed , 5000))
		{
			DIO_TogglePin(PINA_0);
		}
		else{
			/*       Timeout      */
			UART_SendString("Time out \r\n");
		}
	}
}

void System_Init()
{
	DIO_Init();
	UART_Init();
	UART_SendString("System start \r\n");
}