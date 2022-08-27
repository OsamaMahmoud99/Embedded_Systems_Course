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
#include "UART_Service.h"
#include "ADC_Interface.h"
#include "LCD_Interface.h"
#include "LM35_Interface.h"



void T_UserInput(void *param);
void T_GetTemp(void *param);
void T_Display(void *param);
void T_CheckTemp(void *param);
void T_SetAlaram(void *param);
void System_Init(void);


/* used to trigger the T_Alarm task */
#define E_Alarm          (1<<0)        //is set by T_CheckTemp task

/* used to trigger the T_Display task */
#define E_MainScreen     (1<<1)
#define E_ConfigScreen   (1<<2)
#define E_AlarmScreen    (1<<3)
#define E_CTempUpdated   (1<<4)
#define E_TTempUpdated   (1<<5)
#define E_ASUpdated      (1<<6)
#define E_TConfigUpdated (1<<7)

#define E_DispEvents     (0x7F)

EventGroupHandle_t    egEvents = NULL;
EventBits_t           ebBits = NULL;
SemaphoreHandle_t     bsCheck;


#define DISP_MAIN_L0      (u8*)"C:      T:      AS: "
#define DISP_MAIN_L1      (u8*)"  TC:C        AT:T  "

#define DISP_CTEMP_ROW    0
#define DISP_CTEMP_COL    3
#define DISP_TTEMP_ROW    0
#define DISP_TTEMP_COL    9
#define DISP_AS_ROW       0
#define DISP_AS_COL       16


#define DISP_CONFIG_L0    (u8*)"        T:          "
#define DISP_CONFIG_L1    (u8*)"  OK:O        CN:C  "

#define DISP_ALARM_L0     (u8*)"  !!!ALARMING!!!    "
#define DISP_ALARM_L1     (u8*)"        AS:S        "


typedef enum
{
	MAIN_S,
	ALARM_S,
	CONFIG_S	
}state_t;

typedef struct
{
	state_t	     SystemState;
	u8 CTemp;
	u8 TTemp;
	u8 AlarmStatus;
	
}TAS_t;

TAS_t     TAS; 
u8 digitcounter;
u8 digitvalue;
int main(void)
{
	System_Init();
	
	/* create tasks */
	xTaskCreate(&T_Display    , NULL , 150 , NULL , 1 , NULL);
	xTaskCreate(&T_GetTemp    , NULL , 150 , NULL , 2 , NULL);
	xTaskCreate(&T_UserInput  , NULL , 150 , NULL , 3 , NULL);
	xTaskCreate(&T_CheckTemp  , NULL , 150 , NULL , 4 , NULL);
	xTaskCreate(&T_SetAlaram  , NULL , 100 , NULL , 5 , NULL);
	
	egEvents = xEventGroupCreate();
	bsCheck = xSemaphoreCreateBinary();

	/* start os */
	vTaskStartScheduler();
	
	while (1)
	{
	}
}


void T_UserInput(void *param)
{
	u8 data = 0;
	u16 recTTemp = 0;
	while(1)
	{
		if (UART_Receive_PeriodicCheck(&data))
		{
			switch(TAS.SystemState)
			{
				case MAIN_S:
				     if (data == 'C')
				     {
						 TAS.SystemState = CONFIG_S;
						 digitcounter = 0;
						 recTTemp = 0;
						 xEventGroupSetBits(egEvents , E_ConfigScreen);
				     }
					 else if (data == 'T')
					 {
						 if (TAS.AlarmStatus == 'E')
						 {
							 TAS.AlarmStatus = 'D';
						 }
						 else
						 {
							 TAS.AlarmStatus = 'E';
						 }
						 xEventGroupSetBits(egEvents , E_ASUpdated);
						 xSemaphoreGive(bsCheck);
						 
					 }
					 break;
					 
				case ALARM_S:
				     if (data == 'S')
				     {
						 TAS.AlarmStatus = 'D';
						 xSemaphoreGive(bsCheck);
				     }
					 break;
				case CONFIG_S:
				     if (data == 'O')
				     {
						 TAS.TTemp = recTTemp;
						 TAS.SystemState = MAIN_S;
						 xEventGroupSetBits(egEvents , 
						              E_MainScreen|E_TTempUpdated|E_TTempUpdated|E_ASUpdated);
						 xSemaphoreGive(bsCheck);
				     }
					 else if (data == 'C')
					 {
						 TAS.SystemState = MAIN_S;
						 xEventGroupSetBits(egEvents , 
						              E_MainScreen|E_TTempUpdated|E_TTempUpdated|E_ASUpdated);
					 }
					 else if (data>='0'&&data<='9'&&digitcounter<3)
					 {
						 digitcounter++;
						 recTTemp = recTTemp*10 + (data-'0');
						 digitvalue = data;
						 xEventGroupSetBits(egEvents , E_TConfigUpdated); 
					 }
					 break;
			}
		}
		vTaskDelay(10);
	}
}


void T_GetTemp(void *param)
{	
	u16 NewTemp = 0;
	
	while(1)
	{                                                              
		NewTemp = LM35_GetTemp();
		
		if (NewTemp != TAS.CTemp)
		{
			TAS.CTemp = NewTemp;
			if (TAS.SystemState = MAIN_S)
			{
				xSemaphoreGive(bsCheck);
				xEventGroupSetBits(egEvents , E_CTempUpdated);
			}
		}
		
		vTaskDelay(100);
	}
}

void T_CheckTemp(void *param)
{
	while(1)
	{
		
		if (xSemaphoreTake(bsCheck , portMAX_DELAY))
		{
			if (TAS.SystemState == MAIN_S && TAS.CTemp>=TAS.TTemp && TAS.AlarmStatus == 'E')
			{
				TAS.SystemState = ALARM_S;
				xEventGroupSetBits(egEvents , E_Alarm); //trigger the T_Alarm task
				xEventGroupSetBits(egEvents , E_AlarmScreen); //trigger the T_Display task
			}
			else if (TAS.SystemState == ALARM_S && (TAS.CTemp<TAS.TTemp||TAS.AlarmStatus == 'D'))
			{
				TAS.SystemState = MAIN_S;
				xEventGroupClearBits(egEvents , E_Alarm);
				
				/* For T_Display task */
				xEventGroupSetBits(egEvents , 
				                   E_MainScreen|E_TTempUpdated|E_TTempUpdated|E_ASUpdated);
				
			}
		}
		
	}
}

void T_Display(void *param)
{
	
	while(1)
	{
		ebBits = xEventGroupWaitBits(egEvents , E_DispEvents , 1 , 0 , portMAX_DELAY);
		if (ebBits & E_MainScreen)
		{
			LCD_GoToWriteString(0 , 0 , DISP_MAIN_L0);
			LCD_GoToWriteString(1 , 0 , DISP_MAIN_L1);
		}
		if (ebBits & E_AlarmScreen)
		{
			LCD_GoToWriteString(0 , 0 , DISP_ALARM_L0);
			LCD_GoToWriteString(1 , 0 , DISP_ALARM_L1);
		}
		if (ebBits & E_ConfigScreen)
		{
			LCD_GoToWriteString(0 , 0 , DISP_CONFIG_L0);
			LCD_GoToWriteString(1 , 0 , DISP_CONFIG_L1);
		}
		if (ebBits & E_CTempUpdated)
		{
			LCD_GoTo(DISP_CTEMP_ROW , DISP_CTEMP_COL);
			LCD_WriteNumber(TAS.CTemp);
		}
		if (ebBits & E_TTempUpdated)
		{
			LCD_GoTo(DISP_TTEMP_ROW , DISP_TTEMP_COL);
			LCD_WriteNumber(TAS.TTemp);
		}
		if (ebBits & E_TConfigUpdated)
		{
			LCD_GoTo(DISP_TTEMP_ROW , DISP_TTEMP_COL+digitcounter);
			LCD_WriteChar(digitvalue);
		}
		if (ebBits & E_ASUpdated)
		{
			LCD_GoTo(DISP_AS_ROW , DISP_AS_COL);
			LCD_WriteChar(TAS.AlarmStatus);
		}
		
	}
}

void T_SetAlaram(void *param)
{
	
	while(1)
	{
		ebBits = xEventGroupWaitBits(egEvents , E_Alarm , 0 , 0 , portMAX_DELAY);
		if (ebBits & (E_Alarm))
		{
			DIO_TogglePin(PINA_6);
			vTaskDelay(500);
		}
			
	}
}

void System_Init()
{
	/* init system parameters */
	TAS.SystemState = MAIN_S;
	TAS.AlarmStatus = 'E';
	TAS.CTemp = 0;
	TAS.TTemp = 30;
	
	DIO_Init();
	UART_Init();
	LCD_Init();
	ADC_Init(ADC_VCC , divfact64);
	UART_SendString("System start \r\n");
}