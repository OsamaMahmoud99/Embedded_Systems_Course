 /*
 * AVR.c
 *
 * Created: 7/4/2022 1:58:41 PM
 * Author : Osama
 */ 


#define  F_CPU    8000000
#include <util/delay.h>

#include "MemMap.h"
#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "TIMER_Interface.h"
#include "EXTI_Interface.h"


#define LED_BLINKED      PINB0

typedef enum
{   
	APP_LED_STATE_INIT=0,
	APP_LED_STATE_WAIT,
	APP_LED_STATE_BLINK_LED
}APP_LED_STATES;

typedef struct  
{
	APP_LED_STATES state;
	
	volatile int Timer_Count;
	
}APP_LED_DATA;

APP_LED_DATA appledData;

void APP_LED_Initialize( void );

void APP_LED_Tasks( void );

void DELAY_MS(void);

int main(void)
{
	APP_LED_Initialize();
	
	while(1)
	{
		APP_LED_Tasks();
	}
		
	return 0;
}

void DELAY_MS(void)
{
	appledData.Timer_Count++;
}
void APP_LED_Initialize( void )
{
	sei();
	DIO_Init();
	Timer1_Init(TIMER1_NORMAL_MODE , TIMER1_SCALER_8 , OCRA_DISCONNECTED , OCRB_DISCONNECTED);
	Timer1_OVF_SetCallBack(DELAY_MS);
	Timer1_OVF_InterruptEnable();
	appledData.state = APP_LED_STATE_INIT;
}

void APP_LED_Tasks(void)
{
	switch(appledData.state)
	{
		case APP_LED_STATE_INIT:
		{
			appledData.state = APP_LED_STATE_WAIT;
			break;
		}
		case APP_LED_STATE_WAIT:
		{
			if (appledData.Timer_Count >= 7)      //500ms 7*65535
			{
				appledData.state = APP_LED_STATE_BLINK_LED;
				appledData.Timer_Count = 0;
			}
			break;
		}
		case APP_LED_STATE_BLINK_LED:
		{
			DIO_TogglePin(LED_BLINKED);
			appledData.state = APP_LED_STATE_WAIT;
			break;
		}
		default:
		{
			break;
		}
		
	}
	
}


