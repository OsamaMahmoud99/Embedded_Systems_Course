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
}APP_LED_DATA;

APP_LED_DATA appledData;

void APP_LED_Initialize( void );

void APP_LED_Tasks( void );


int main(void)
{
	APP_LED_Initialize();
	
	while(1)
	{
		APP_LED_Tasks();
	}
		
	return 0;
}

void APP_LED_Initialize( void )
{
	DIO_Init();
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
			_delay_ms(500);
			appledData.state = APP_LED_STATE_BLINK_LED;
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


