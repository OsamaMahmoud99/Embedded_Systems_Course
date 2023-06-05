/*
 * FreeRTOS_1.c
 *
 * Created: 8/21/2022 9:44:16 AM
 * Author : Osama
 */ 

#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/FreeRTOSConfig.h"
#include "FreeRTOS/task.h"



#include "StdTypes.h"
#include "DIO_Interface.h"
#include "KEYPAD_OS.h"
#include "LCD_OS.h"

void APP_OS_TASK(void* pvoid)
{
	u8 enuPressedKey;
	while(1)
	{
		enuPressedKey = KEYPAD_OS_GetChar();

		if (enuPressedKey != NOTPRESSED){
			LCD_OS_WriteChar(enuPressedKey);
		}

		vTaskDelay(200);
	}
}

int main(void)
{
	DIO_Init();

	LCD_OS_Init();

	xTaskCreate(KEYPAD_OS_Task,NULL,configMINIMAL_STACK_SIZE,NULL,
		 			1,NULL);

	xTaskCreate(APP_OS_TASK,NULL,configMINIMAL_STACK_SIZE,NULL,
		 			2,NULL);

	xTaskCreate(LCD_OS_Task,NULL,configMINIMAL_STACK_SIZE,NULL,
		 			3,NULL);

	vTaskStartScheduler();
	
	while (1)
	{
	}
}


