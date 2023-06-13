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

#define PB               PINB0

typedef enum
{   
	APP_LED_STATE_INIT=0,
	APP_LED_STATE_WAIT,
	APP_LED_STATE_BLINK_LED,
	APP_LED_STATE_STOP
}APP_LED_STATES;

typedef enum
{
	APP_KEY_STATE_INIT=0,
	APP_KEY_STATE_HIGH,
	APP_KEY_STATE_LOW,
	APP_KEY_STATE_DEBOUNCE
}APP_KEY_STATES;

typedef struct  
{
	APP_LED_STATES state;

	volatile u8 TimerCount;

}APP_LED_DATA;

APP_LED_DATA appledData;

typedef struct
{
	APP_KEY_STATES state;

	u8 DebounceCount;

}APP_KEY_DATA;

APP_KEY_DATA appkeyData;

void APP_LED_Initialize( void );
void APP_KEY_Initialize( void );

void APP_LED_Tasks( void );
void APP_KEY_Tasks( void );

void DELAY_MS(void);

int main(void)
{
	sei();
	DIO_Init();
	Timer1_SetInterruptTime_ms (10, DELAY_MS);


	APP_LED_Initialize();
	APP_KEY_Initialize();
	
	while(1)
	{
		APP_KEY_Tasks();
		APP_LED_Tasks();
	}
		
	return 0;
}

void DELAY_MS(void)
{
	appledData.TimerCount++;

	if (appkeyData.state == APP_KEY_STATE_DEBOUNCE)
	{
		appkeyData.DebounceCount++;
	}

}
void APP_LED_Initialize( void )
{
	appledData.state = APP_LED_STATE_INIT;

	appledData.TimerCount = 0;
}

void APP_KEY_Initialize( void )
{
	appkeyData.state = APP_KEY_STATE_INIT;

	appkeyData.DebounceCount = 0;
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
			if (appledData.TimerCount >= 50)     //500ms
			{
				appledData.state = APP_LED_STATE_BLINK_LED;
				appledData.TimerCount = 0;
			}
			break;
		}
		case APP_LED_STATE_BLINK_LED:
		{
			DIO_TogglePin(LED_BLINKED);
			appledData.state = APP_LED_STATE_WAIT;
			break;
		}
		case APP_LED_STATE_STOP:
		{
			DIO_WritePin(LED_BLINKED , LOW);
			break;
		}
		default:
		{
			break;
		}
		
	}
	
}

void APP_KEY_Tasks( void )
{
	switch(appkeyData.state)
	{
		case APP_KEY_STATE_INIT:
		{
			if (DIO_ReadPin(PB) == LOW){                   // key pressed
				appkeyData.state = APP_KEY_STATE_LOW;
			}
			else{
				appkeyData.state = APP_KEY_STATE_HIGH;
			}
			break;
		}
		case APP_KEY_STATE_LOW:
		{
			if(DIO_ReadPin(PB) == HIGH)
			{
				appkeyData.state = APP_KEY_STATE_DEBOUNCE;
				appkeyData.DebounceCount = 0;
			}
			break;
		}
		case APP_KEY_STATE_HIGH:
		{
			if (DIO_ReadPin(PB) == LOW)
			{
				appkeyData.state = APP_KEY_STATE_DEBOUNCE;
				appkeyData.DebounceCount = 0;
			}
			break;
		}
		case APP_KEY_STATE_DEBOUNCE:
		{
			if (appkeyData.DebounceCount >= 2)    // 10 * 2 = 20ms
			{
				if (DIO_ReadPin(PB) == LOW)
				{
					appkeyData.state = APP_KEY_STATE_LOW;
					if (appledData.state == APP_LED_STATE_STOP)
					{
						appledData.state = APP_LED_STATE_BLINK_LED;
					}
					else
					{
						appledData.state = APP_LED_STATE_STOP;
					}

				}
				else
				{
					appkeyData.state = APP_KEY_STATE_HIGH;
				}
			}
			break;

		}
		default:
		{
			break;
		}
	}
}
