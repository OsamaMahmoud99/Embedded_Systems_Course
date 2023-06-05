/*
 * LCD_OS.c
 *
 * Created: 8/29/2022 1:17:14 PM
 *  Author: Osama
 */ 

#include "StdTypes.h"
#include "DIO_Interface.h"
#include "LCD_OS.h"
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"


/*States*/
#define STATE_INIT_0	((u8)0)
#define STATE_INIT_1	((u8)1)
#define STATE_INIT_2	((u8)2)
#define STATE_INIT_3	((u8)3)
#define STATE_INIT_4	((u8)4)
#define STATE_INIT_5	((u8)5)

#define STATE_0			((u8)6)
#define STATE_1			((u8)7)

#define ON_GOING		((u8)0)
#define DONE			((u8)1)

#define E_OK ((u8)0)
#define E_NOK ((u8)1)

static u8 state , WriteRequest , LCDInitialized;
static u8 gData;

void LCD_OS_Init(void)
{
	state = STATE_INIT_0;
	WriteRequest = 0;
	LCDInitialized = 0;
}


static u8 LCD_WriteCommand(u8 Command)
{
	static u8 state = 0 , counter = 0;
	u8 retVal = ON_GOING;

	switch(state)
	{
	case 0:
		DIO_WritePin(RS,LOW);

		DIO_WritePin(EN,HIGH);
		DIO_WritePort(LCD_PORT , Command);
		DIO_WritePin(EN , LOW);

		state = 1;
		break;
	case 1:
		DIO_WritePin(EN,HIGH);
		state = 2;
		break;
	case 2:
		counter++;
        /*10 ms elapsed */
		if(counter == 2){
			counter = 0;
			state = 0;
			retVal = DONE;
		}
		break;
	}

	return retVal;
}

static void LCD_WriteData_step1(void)
{
	DIO_WritePin(RS , HIGH);

	DIO_WritePin(EN , HIGH);

	DIO_WritePort(LCD_PORT , gData);

	DIO_WritePin(EN , LOW);
}

static void LCD_WriteData_step2(void)
{
	DIO_WritePin(EN , HIGH);
}

void LCD_OS_Task(void* pvoid)
{
	u8 retval;

	while(1)
	{
		switch(state)
		{
		case STATE_INIT_0:
			retval = LCD_WriteCommand(LCD_FUNCTION_8BIT_2LINES);
			if (retval == DONE)
			{
				state = STATE_INIT_1;
			}
			break;
		case STATE_INIT_1:
			retval = LCD_WriteCommand(LCD_DISP_ON);
			if (retval == DONE)
			{
				state = STATE_INIT_2;
			}
			break;
		case STATE_INIT_2:
			retval = LCD_WriteCommand(LCD_CLR_SCREEN);
			if (retval == DONE)
			{
				state = STATE_INIT_3;
			}
			break;
		case STATE_INIT_3:
			retval = LCD_WriteCommand(LCD_ENTRY_MODE);
			if (retval == DONE)
			{
				state = STATE_0;
				LCDInitialized = 1;
			}
			break;
		case STATE_0:
			if (WriteRequest == 1)
			{
				LCD_WriteData_step1();
				state = STATE_1;
			}
			break;
		case STATE_1:
			LCD_WriteData_step2();
			state = STATE_0;
			WriteRequest = 0;
			break;

		}	
		vTaskDelay(5);
	}

}

u8 LCD_OS_WriteChar(u8 character)
{
	if ((LCDInitialized==1) && (WriteRequest==0))
	{
		WriteRequest = 1;
		gData = character;
		return E_OK;
	}
	else{
		return E_NOK;
	}
}


