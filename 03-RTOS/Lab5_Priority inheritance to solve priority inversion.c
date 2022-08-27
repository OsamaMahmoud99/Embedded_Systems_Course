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
#include "queue.h"


void T_L(void *param);
void T_M(void *param);
void T_H(void *param);
void System_Init(void);

/* Os Services */
xSemaphoreHandle  sem = NULL;

TaskHandle_t  T_L_Handler;


u8 pr;

int main(void)
{
	System_Init();
	/* create tasks */
	
	xTaskCreate(&T_L , NULL , 100 , NULL , 1 , &T_L_Handler);
	
	
	
	/* create semaphore */
	sem = xSemaphoreCreateBinary();
	//sem = xSemaphoreCreateMutex();
	xSemaphoreGive(sem);
	
	/* start os */
	vTaskStartScheduler();
	
	while (1)
	{
	}
}


void T_L(void *param)
{
	UART_SendString("T_L started \r\n");
	
	xSemaphoreTake(sem , portMAX_DELAY);
	
	pr = uxTaskPriorityGet(T_L_Handler);
	UART_SendString("T_L priority before T_H created ");
	UART_SendByte(pr+'0');
	UART_SendString("\r\n");
	
	xTaskCreate(&T_H , NULL , 100 , NULL , 3 , NULL);
	
	pr = uxTaskPriorityGet(T_L_Handler);
	UART_SendString("T_L priority after T_H created ");
	UART_SendByte(pr+'0');
	UART_SendString("\r\n");
	
	xTaskCreate(&T_M , NULL , 100 , NULL , 2 , NULL);
	
	pr = uxTaskPriorityGet(T_L_Handler);
	UART_SendString("T_L priority after T_M created ");
	UART_SendByte(pr+'0');
	UART_SendString("\r\n");
	
	xSemaphoreGive(sem);
	
	while(1)
	{
	}
}
void T_M(void *param)
{
	UART_SendString("T_M started \r\n");
	_delay_ms(5000);
	vTaskDelay(5000);
	
	while(1)
	{
	
	}
}

void T_H(void *param)
{
	UART_SendString("T_H started \r\n");
	xSemaphoreTake(sem , portMAX_DELAY);
	
	pr = uxTaskPriorityGet(T_L_Handler);
	UART_SendString("T_L priority after semaphore is given ");
	UART_SendByte(pr+'0');
	UART_SendString("\r\n");
	
	while(1)
	{
	}
}

void System_Init()
{
	DIO_Init();
	UART_Init();
	UART_SendString("System start \r\n");
}