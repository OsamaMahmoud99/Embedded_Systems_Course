/*
 * FreeRTOS_1.c
 *
 * Created: 8/21/2022 9:44:16 AM
 * Author : Osama
 */ 

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "event_groups.h"


#include "StdTypes.h"
#include "DIO_Interface.h"
#include "UART_Interface.h"

void T_CheckSwitch(void *param);
void T_UpdateTime(void *param);
void T_UpdateSSD(void *param);
void System_Init(void);


///* Os Services */
//EventGroupHandle_t egEvents;
//EventBits_t        ebBits;

xSemaphoreHandle   Reset_sem = NULL;
xSemaphoreHandle   Pause_sem = NULL;
xSemaphoreHandle   Resume_sem = NULL;
 
//#define E_RESET        (1<<0)
//#define E_RESUME       (1<<1)
//#define E_PAUSE        (1<<2)

#define RESET_SW        PINB_0
#define RESUME_SW       PINB_1
#define PAUSE_SW        PINB_2

u16 second = 0;
u16 minute = 0;
u16 hour = 0;

int main(void)
{
	System_Init();
	
	/* create tasks */
	xTaskCreate(&T_CheckSwitch    , NULL , 150 , NULL , 1 , NULL);
	xTaskCreate(&T_UpdateTime    , NULL , 150 , NULL , 2 , NULL);
	xTaskCreate(&T_UpdateSSD  , NULL , 150 , NULL , 3 , NULL);
	
	/* create event group */
	//egEvents = xEventGroupCreate();
	
	Reset_sem = xSemaphoreCreateBinary();
	Pause_sem = xSemaphoreCreateBinary();
	Resume_sem = xSemaphoreCreateBinary();
	
	/* start os */
	vTaskStartScheduler();
	
	while (1)
	{
	}
}




void T_CheckSwitch(void *param)
{
	while(1)
	{
		if (!DIO_ReadPin(RESET_SW))
		{
			//xEventGroupSetBits(egEvents , E_RESET);
			xSemaphoreGive(Reset_sem);
			while(!DIO_ReadPin(RESET_SW));
		}
		
		if (!DIO_ReadPin(PAUSE_SW))
		{
			//xEventGroupSetBits(egEvents , E_PAUSE);
			xSemaphoreGive(Pause_sem);
			while(!DIO_ReadPin(PAUSE_SW));
		}
		
		if (!DIO_ReadPin(RESUME_SW))
		{
			//xEventGroupSetBits(egEvents , E_RESUME);
			xSemaphoreGive(Resume_sem);
			while(!DIO_ReadPin(RESUME_SW));
		}
		
		vTaskDelay(50);
	}

}
void T_UpdateTime(void *param)
{
	static u8 flag = 0;
	while(1)
	{
	
    	if (xSemaphoreTake(Reset_sem , 10))
    	{
			second = 0;
			minute = 0;
			hour = 0;
    	}
		if (xSemaphoreTake(Pause_sem , 10))
		{
			flag = 1;
		} 
		if (xSemaphoreTake(Resume_sem , 10))
		{
			flag = 0;
		}
		if (flag == 0)
		{
				second++;
				if (second == 60)
				{
					second = 0;
					minute++;
				}
				if (minute == 60)
				{
					second = 0;
					minute = 0;
					hour++;
				}
		}
		vTaskDelay(1000);
	}
}
void T_UpdateSSD(void *param)
{
	while(1)
	{
		DIO_WritePin(PINA_0 , LOW);
		DIO_WritePin(PINA_2 , LOW);
		DIO_WritePin(PINA_3 , LOW);
		DIO_WritePin(PINA_4 , LOW);
		DIO_WritePin(PINA_5 , LOW);
		DIO_WritePin(PINA_1 , HIGH);
		DIO_lower_nibble_value(PC , second%10);
		vTaskDelay(5);
		
		DIO_WritePin(PINA_1 , LOW);
		DIO_WritePin(PINA_2 , LOW);
		DIO_WritePin(PINA_3 , LOW);
		DIO_WritePin(PINA_4 , LOW);
		DIO_WritePin(PINA_5 , LOW);
		DIO_WritePin(PINA_0 , HIGH);
		DIO_lower_nibble_value(PC , second/10);
		vTaskDelay(5);
		
		DIO_WritePin(PINA_0 , LOW);
		DIO_WritePin(PINA_1 , LOW);
		DIO_WritePin(PINA_2 , LOW);
		DIO_WritePin(PINA_4 , LOW);
		DIO_WritePin(PINA_5 , LOW);
		DIO_WritePin(PINA_3 , HIGH);
		DIO_lower_nibble_value(PC , minute%10);
		vTaskDelay(5);
		DIO_WritePin(PINA_0 , LOW);
		DIO_WritePin(PINA_1 , LOW);
		DIO_WritePin(PINA_3 , LOW);
		DIO_WritePin(PINA_4 , LOW);
		DIO_WritePin(PINA_5 , LOW);
		DIO_WritePin(PINA_2 , HIGH);
		DIO_lower_nibble_value(PC , minute/10);
		vTaskDelay(5);
		
		DIO_WritePin(PINA_0 , LOW);
		DIO_WritePin(PINA_1 , LOW);
		DIO_WritePin(PINA_2 , LOW);
		DIO_WritePin(PINA_3 , LOW);
		DIO_WritePin(PINA_4 , LOW);
		DIO_WritePin(PINA_5 , HIGH);
		DIO_lower_nibble_value(PC , hour%10);
		vTaskDelay(5);
		DIO_WritePin(PINA_0 , LOW);
		DIO_WritePin(PINA_1 , LOW);
		DIO_WritePin(PINA_2 , LOW);
		DIO_WritePin(PINA_3 , LOW);
		DIO_WritePin(PINA_5 , LOW);
		DIO_WritePin(PINA_4 , HIGH);
		DIO_lower_nibble_value(PC , hour/10);
		vTaskDelay(5);
		
	}
}

void System_Init()
{
	DIO_Init();
	UART_Init();
}