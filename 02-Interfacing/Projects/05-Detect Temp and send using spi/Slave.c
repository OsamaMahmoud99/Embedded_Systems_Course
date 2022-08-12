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
#include "ADC_Interface.h"
#include "Timer_Service.h"
#include "ULTRASONIC_Interface.h"
#include "SERVO_Interface.h"
#include "RGB_Interface.h"
#include "KEYPAD_Interface.h"
#include "SPI_Interface.h"
#include "SPI_Service.h"

static u16 adc_read=0;

int main(void)
{
	DIO_Init();
	LCD_Init();
    SPI_Init();
	ADC_Init(ADC_VCC , divfact64);
	LCD_WriteSentence("Slave");

	while(1)
	{
	     	
		adc_read = LM35_GetTemp();
		LCD_GoTo(1 , 0);
		LCD_WriteNumber_4D(adc_read/10);
		LCD_WriteChar('.');
		LCD_WriteNumber(adc_read%10);
	
	
	    SPI_Send(adc_read/10);

		if (adc_read > 450)
		{
			DIO_WritePin(PINC6 , HIGH);
			_delay_us(100);
			DIO_WritePin(PINC6 , LOW);
		}
	}
	
	return 0;
}


