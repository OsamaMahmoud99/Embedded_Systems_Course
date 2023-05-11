/*
 * Security_System.c
 *
 * Created: 7/15/2021 6:32:56 PM
 * Author : Osama Mahmoud
 */ 

#define  F_CPU   1000000UL
#include <util/delay.h>

#include "Mem_Map32.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "Switch.h"
#include "LED.h"
#include "SEG_interface.h"

#include "APP.h"


int main(void)
{
	LED_Init();
	Switch_Init();
	SEG_Init();
    
    while (1) 
    {
		
		switch(PB_CheckPressed())
		{
			case ONES_SS:
			SEG_Increment_Ones();
			break;
			case TENS_SS:
			SEG_Increment_Tens();
			break;
			case ENTER:
			     switch(SEG_DEF_Password())
				 {
			       case PASS:
				   LED_On();
				   _delay_ms(5000);
				   LED_Off();
				   break;
				   case WRONG:
				   Buzzer_On();
				   LED_Animation();
				   Buzzer_Off();
				   break;
				 }
			break;
			default:
			SEG_Enable_PinDot(Ones_Count , ONES_ENABLE);
			SEG_Enable_PinDot(Tens_Count , TENS_ENABLE);
			break;	
		}
    }
}

