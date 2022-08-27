/*
 * FreeRTOS_1.c
 *
 * Created: 8/21/2022 9:44:16 AM
 * Author : Osama
 */ 

#include "StdTypes.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "UART_Interface.h"
#include "UART_Service.h"


#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "event_groups.h"

void T_FireDetect(void *param);
void T_FireAlarm(void *param);
void System_Init(void);

/* Os Services */
EventGroupHandle_t egEvents;
EventBits_t        ebBits;
#define E_SMOKE        (1<<0)
#define E_HEAT         (1<<1)

int main(void)
{
	System_Init();
	/* create tasks */
	
	xTaskCreate(&T_FireDetect , NULL , 100 , NULL , 1 , NULL);
	xTaskCreate(&T_FireAlarm  , NULL , 100 , NULL , 2 , NULL);
	
	/* create event group */
	egEvents = xEventGroupCreate();
	
	/* start os */
	vTaskStartScheduler();
	
	while (1)
	{
	}
}


void T_FireDetect(void *param)
{
	u8 data = 0;
	while(1)
	{
		if (UART_Receive_PeriodicCheck(&data))
		{
			switch(data)
			{
				case 'H':
				xEventGroupSetBits(egEvents , E_HEAT);
				break;
				case 'h':
				xEventGroupClearBits(egEvents , E_HEAT);
				break;
				case 'S':
				xEventGroupSetBits(egEvents , E_SMOKE);
				break;
				case 's':
				xEventGroupClearBits(egEvents , E_SMOKE);
				break;
			}
		}
	}
}


void T_FireAlarm(void *param)
{
	while(1)
	{                                                              
		ebBits = xEventGroupWaitBits(egEvents , (E_SMOKE|E_HEAT) , 0 , 1 , portMAX_DELAY);
		
		if ((ebBits&(E_SMOKE|E_HEAT)) == (E_SMOKE|E_HEAT) )
		{
			DIO_TogglePin(PINA_0);
			vTaskDelay(1000);
		}
	}
}

void System_Init()
{
	DIO_Init();
	UART_Init();
	UART_SendString("System start \r\n");
}