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



#include "APP.h"


int main(void)
{
	System_Init();
	
		/* OS Object Creation */
	egControl = xEventGroupCreate();
	egDisplay = xEventGroupCreate();
	bsCheck = xSemaphoreCreateBinary();


	//xTaskCreate(T_Indication, )
	xTaskCreate(T_Display, 	 NULL, 170, NULL, 2, NULL);
	xTaskCreate(T_Sensing, 	 NULL, 100,  NULL, 3, NULL);
	xTaskCreate(T_Terminal,  NULL, 70, NULL, 4, NULL);
	xTaskCreate(T_SysCheck,  NULL, 70,  NULL, 5, NULL);
	xTaskCreate(T_Control,	 NULL, 150, NULL, 6, NULL);

	/* start os */
	vTaskStartScheduler();
	
	while (1)
	{
	}
}




void T_Display(void* pvParam)
{


	while(1)
	{
		ebDisplayBits = xEventGroupWaitBits(egDisplay,E_DISPLAYMASK,1,0,portMAX_DELAY);
		
		if( (ebDisplayBits & E_MainScreen) == E_MainScreen)
		{
			vTaskDelay(2000);

			if( MainState == SFS.SystemState )
			{
				LCD_CLR();
				LCD_WriteSentence(LCD_MAIN_SCREEN_L1);

				LCD_GoTo(0,LCD_TEMP_COL);
				LCD_WriteSentence("   ");
				LCD_GoTo(0,LCD_TEMP_COL);
				LCD_WriteNumber(SFS.SensorData.TempData);

				LCD_GoTo(0,LCD_HUMI_COL);
				LCD_WriteSentence("   ");
				LCD_GoTo(0,LCD_HUMI_COL);
				LCD_WriteNumber(SFS.SensorData.HumiData);

				LCD_GoTo(1,0);
				LCD_WriteSentence(LCD_MAIN_SCREEN_L2);

				LCD_GoTo(1,LCD_TEMP_COL);
				LCD_WriteSentence("   ");
				LCD_GoTo(1,LCD_TEMP_COL);
				LCD_WriteNumber(SFS.SensorThreshold.TempT);
				//LCD_goToRowColumn(1,LCD_TEMP_COL);

				LCD_GoTo(1,LCD_HUMI_COL);
				LCD_WriteSentence("   ");
				LCD_GoTo(1,LCD_HUMI_COL);
				LCD_WriteNumber(SFS.SensorThreshold.HumiT);

				LCD_GoTo(2,0);
				LCD_WriteSentence(LCD_MAIN_SCREEN_L3);
				
				if(Motors_State.Water_Pump == ON)
				{
					LCD_GoTo(2,LCD_PUMP_COL);
					LCD_WriteSentence("   ");
					LCD_GoTo(2,LCD_PUMP_COL);
					LCD_WriteSentence("ON");
				}
				else
				{
					LCD_GoTo(2,LCD_PUMP_COL);
					LCD_WriteSentence("   ");
					LCD_GoTo(2,LCD_PUMP_COL);
					LCD_WriteSentence("OFF");
				}

				if(Motors_State.Heater == ON)
				{
					LCD_GoTo(2,LCD_HEATER_COL);
					LCD_WriteSentence("   ");
					LCD_GoTo(2,LCD_HEATER_COL);
					LCD_WriteSentence("ON");
				}
				else
				{
					LCD_GoTo(2,LCD_HEATER_COL);
					LCD_WriteSentence("   ");
					LCD_GoTo(2,LCD_HEATER_COL);
					LCD_WriteSentence("OFF");
				}

				if(Motors_State.Cooler == ON)
				{
					LCD_GoTo(2,LCD_COOLER_COL);
					LCD_WriteSentence("   ");
					LCD_GoTo(2,LCD_COOLER_COL);
					LCD_WriteSentence("ON");
				}
				else
				{
					LCD_GoTo(2,LCD_COOLER_COL);
					LCD_WriteSentence("   ");
					LCD_GoTo(2,LCD_COOLER_COL);
					LCD_WriteSentence("OFF");
				}
				
				
				
				LCD_GoTo(3,0);
				LCD_WriteSentence(LCD_MAIN_SCREEN_L4);
				
			} /*end of if MainState*/
			

		}

		if( (ebDisplayBits & E_ConfigScreen) == E_ConfigScreen)
		{
			if(ConfigState == SFS.SystemState)
			{			
				LCD_CLR();
				LCD_WriteSentence(LCD_CONFIG_SCREEN_L1);
				LCD_WriteSentence(LCD_CONFIG_SCREEN_L2);
				LCD_WriteSentence(LCD_CONFIG_SCREEN_L4);

				LCD_GoTo(0,LCD_CONFIG_COL);
				//LCD_sendCommand(CURSOR_BLINK);
			}

		}
		
		if( (ebDisplayBits & E_TTUpdated) == E_TTUpdated)
		{
			LCD_GoTo(0,LCD_CONFIG_COL);
			//LCD_sendCommand(CURSOR_OFF);
			LCD_WriteNumber(SFS.SensorThreshold.TempT);
		}

		if( (ebDisplayBits & E_HTUpdated) == E_HTUpdated)
		{
			UART_SendString("E_HTUpdated");
			LCD_GoTo(2,LCD_CONFIG_COL);
			//LCD_sendCommand(CURSOR_OFF);
			LCD_WriteNumber(SFS.SensorThreshold.HumiT);
		}

		if( (ebDisplayBits & E_Next) == E_Next)
		{
			LCD_goToRowColumn(2,LCD_CONFIG_COL);
			LCD_sendCommand(CURSOR_BLINK);
		}

		if( (ebDisplayBits & E_TUpdated) == E_TUpdated)
		{
			LCD_goToRowColumn(0,LCD_TEMP_COL);
			LCD_displayString("   ");
			LCD_goToRowColumn(0,LCD_TEMP_COL);
			LCD_intgerToString(SFS.SensorData.TempData);
		}

		if( (ebDisplayBits & E_HUpdated) == E_HUpdated)
		{
			LCD_goToRowColumn(0,LCD_HUMI_COL);
			LCD_displayString("   ");
			LCD_goToRowColumn(0,LCD_HUMI_COL);
			LCD_intgerToString(SFS.SensorData.HumiData);
		}


if(MainState == SFS.SystemState)
{
	if( (ebDisplayBits & E_MotorState) == E_MotorState)
	{
		if(Motors_State.Water_Pump == ON)
		{
			LCD_goToRowColumn(2,LCD_PUMP_COL);
			LCD_displayString("   ");
			LCD_goToRowColumn(2,LCD_PUMP_COL);
			LCD_displayString("ON");
		}
		else
		{
			LCD_goToRowColumn(2,LCD_PUMP_COL);
			LCD_displayString("   ");
			LCD_goToRowColumn(2,LCD_PUMP_COL);
			LCD_displayString("OFF");
		}

		if(Motors_State.Heater == ON)
		{
			LCD_goToRowColumn(2,LCD_HEATER_COL);
			LCD_displayString("   ");
			LCD_goToRowColumn(2,LCD_HEATER_COL);
			LCD_displayString("ON");
		}
		else
		{
			LCD_goToRowColumn(2,LCD_HEATER_COL);
			LCD_displayString("   ");
			LCD_goToRowColumn(2,LCD_HEATER_COL);
			LCD_displayString("OFF");
		}

		if(Motors_State.Cooler == ON)
		{
			LCD_goToRowColumn(2,LCD_COOLER_COL);
			LCD_displayString("   ");
			LCD_goToRowColumn(2,LCD_COOLER_COL);
			LCD_displayString("ON");
		}
		else
		{
			LCD_goToRowColumn(2,LCD_COOLER_COL);
			LCD_displayString("   ");
			LCD_goToRowColumn(2,LCD_COOLER_COL);
			LCD_displayString("OFF");
		}
	} /* if motorState*/
	
}

		
		
	}
}
void T_Indication(void* pvParam)
{
	EventBits_t ebControlBits;
	ebControlBits = xEventGroupWaitBits(egControl, E_HEATERON | E_COOLERON |E_PUMPON ,0,0,portMAX_DELAY);
	if( ( (ebControlBits & E_HEATERON) == E_HEATERON) || ( (ebControlBits & E_COOLERON) == E_COOLERON ) || ( (ebControlBits & E_PUMPON) == E_PUMPON))
	{
		DIO_WritePin(PINA_0 , HIGH);
		vTaskDelay(500);
		DIO_WritePin(PINA_0 , LOW);
		vTaskDelay(500);
	}
}
void System_Init()
{

	
	DIO_Init();
	UART_Init();
	LCD_Init();
	
	/*Defaults initialize */
	SFS.SensorThreshold.TempT = 20;
	SFS.SensorThreshold.HumiT = 30;

	ADC_Init(ADC_VCC , divfact64);
	UART_SendString("System start \r\n");
}