 /*
 * AVR.c
 *
 * Created: 7/4/2022 1:58:41 PM
 * Author : Osama
 */ 


#include "MemMap.h"
#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "TIMER_Interface.h"
#include "Timer_Service.h"



#define LED_BLINKED      PINA0

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

	Timer1_SetInterruptTime_ms(10 , DELAY_MS);

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
			if (appledData.Timer_Count >= 50)      //500ms  10 ms *50 = 500ms
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


