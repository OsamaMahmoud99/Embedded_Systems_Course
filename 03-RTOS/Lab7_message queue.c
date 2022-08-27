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

void T_Send(void *param);
void T_Receive(void *param);
void System_Init(void);

/* Os Services */
xQueueHandle   mqUart = NULL;

u8 strings[3][11] ={"Osama\r\n" , "Mahmoud\r\n" , "Hanafi\r\n"};
int main(void)
{
	System_Init();
	/* create tasks */
	
	xTaskCreate(&T_Send , NULL , 100 , NULL , 1 , NULL);
	xTaskCreate(&T_Receive  , NULL , 100 , NULL , 2 , NULL);
	
    mqUart = xQueueCreate(10 , 11);
	
	/* start os */
	vTaskStartScheduler();
	
	while (1)
	{
	}
}


void T_Send(void *param)
{
	u8 str_index = 0;
	while(1)
	{
		/*if(UART_Receive_PeriodicCheck(&data))
		{
			xQueueSend(mqUart , &data , portMAX_DELAY);
		}*/
		xQueueSend(mqUart , strings[str_index] , portMAX_DELAY);
		str_index++;
		if (str_index == 3)
		{
			str_index = 0;
		}
		vTaskDelay(1000);
	}
}


void T_Receive(void *param)
{
	//u8 recmsg = 0;
	u8 str[11] = {0};
	while(1)
	{                                                              
		/*if(xQueueReceive(mqUart , &recmsg , portMAX_DELAY))
		{
			vTaskDelay(3000);
			UART_SendByte(recmsg);
		}*/
		if (xQueueReceive(mqUart , str , portMAX_DELAY))
		{
			UART_SendString(str);
		}
		
	}
}

void System_Init()
{
	DIO_Init();
	UART_Init();
	UART_SendString("System start \r\n");
}