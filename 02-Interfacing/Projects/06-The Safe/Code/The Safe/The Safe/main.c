/*
 * The Safe.c
 *
 * Created: 11/9/2020 6:24:53 PM
 * Author : OsamaMahmoud
 */ 

#define  F_CPU  8000000UL
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Mem_Map32.h"

#include "DIO_interface.h"
#include "EEPROM_interface.h"
#include "Timers_interface.h"

#include "LCD_interface.h"
#include "KEYPAD_interface.h"
#include "Servo_interface.h"

#define  EEPROM_STATUS_LOCATION          0x20
#define  EEPROM_PASSWORD_LOCATION1       0x21
#define  EEPROM_PASSWORD_LOCATION2       0x22
#define  EEPROM_PASSWORD_LOCATION3       0x23
#define  EEPROM_PASSWORD_LOCATION4       0x24

#define  MAX_Tries        3
#define  Number_OfDigits  4       // for password

u8 Pass[Number_OfDigits];


int main(void)
{
	
    DIO_Init();
	LCD_Init();
	KEYPAD_voidInit();
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8,OCRA_NON_INVERTING,OCRB_NON_INVERTING);
	ICR1=19999;  //20000us to get 50hz
	
	u8 Local_u8Value = 0xff;
	u8 flag = 0 , i;
	u8 Local_u8Tries = MAX_Tries;
	
	if (EEPROM_u8Read(EEPROM_STATUS_LOCATION) == 0xff)
	{
		LCD_GoTo(0,0);
		LCD_WriteSentence("Set pass:");
		for (i=0; i<=3; i++)
		{
			Local_u8Value =KEYPAD_u8GetPressed();
			LCD_WriteChar(Local_u8Value);
			_delay_ms(500);
			LCD_GoTo(0,9+i);
			LCD_WriteChar('*');
			_delay_ms(500);
			EEPROM_voidWrite(EEPROM_PASSWORD_LOCATION1+i,Local_u8Value);
		}
		EEPROM_voidWrite(EEPROM_STATUS_LOCATION , 0x00);
	}
	
	
	while(1)
	{
		while (flag == 0)
		{		
			for (u8 i=0; i<Number_OfDigits; ++i)
			{
				Pass[i] = 0xff;
			}
			
			LCD_Clear();
			LCD_GoTo(0,0);
			LCD_WriteSentence("Check Pass:");
			
			for (i=0; i<=3; i++)
			{
				Pass[i]=KEYPAD_u8GetPressed();
				LCD_WriteChar(Pass[i]);
				_delay_ms(500);
				LCD_GoTo(0,11+i);
				LCD_WriteChar('*');
				_delay_ms(500);
			}
			
			if (EEPROM_u8Read(EEPROM_PASSWORD_LOCATION1)==Pass[0] && EEPROM_u8Read(EEPROM_PASSWORD_LOCATION2)==Pass[1] && EEPROM_u8Read(EEPROM_PASSWORD_LOCATION3)==Pass[2] && EEPROM_u8Read(EEPROM_PASSWORD_LOCATION4)==Pass[3])
			{
				LCD_Clear();
				LCD_GoTo(0 , 0);
				LCD_WriteSentence("Right Pass");
				LCD_GoTo(1,0);
				LCD_WriteSentence("Safe opened");
				
				SERVO_SetAngle(90);    // open the safe
				flag = 1;
			}
			else
			{
				Local_u8Tries =Local_u8Tries - 1;
				
				if (Local_u8Tries > 0)
				{
					LCD_Clear();
					LCD_GoTo(0 , 0);
					LCD_WriteSentence("wrong pass");
					_delay_ms(1000);
					LCD_Clear();
					LCD_WriteSentence("tries left:");
					LCD_WriteChar(Local_u8Tries+48);
					_delay_ms(1000);
					
				}
				else
				{
					LCD_Clear();
					LCD_GoTo(0,0);
					LCD_WriteSentence("wrong pass");
					LCD_GoTo(1,0);
					LCD_WriteSentence("safe closed");
					flag = 1;
				}
			}
			
			
		}
	}
	
    

}
