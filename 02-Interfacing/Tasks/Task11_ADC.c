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
#include "Motor_Interface.h"
#include "LCD_Interface.h"
#include "KEYPAD_Interface.h"
#include "STEPPER_Interfaceh.h"
#include "ADC_Interface.h"

int main(void)
{
	DIO_Init();
	LCD_Init();
	
     ADC_Init(ADC_VCC , divfact64);
     
	 u8 p[]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
	 LCD_Create_Character(p , 1);
	 LCD_GoTo(0 , 0);
	 LCD_WriteChar(1);
	 
	 u16 num;
	 u8 percent , i;
	
	 
	while (1)
	{   
		/* num = ADC_Get_Voltage(ADC0);
		 LCD_GoTo(1 , 0);
		 LCD_WriteNumber(num);
		 LCD_WriteSentence("  ");
		 */
		
		 /*num = LM35_GetTemp();
		 LCD_GoTo(1 , 0);
		 LCD_WriteNumber(num/10);
		 LCD_WriteChar('.');
		 LCD_WriteNumber(num%10);
		 LCD_WriteSentence("   ");
		 */
		 
		 percent = POT_GetPercentage();
		 LCD_GoTo(0 , 0);
		 LCD_WriteNumber(percent);
		 LCD_WriteChar('%');
		 LCD_WriteSentence("   ");
		 LCD_GoTo(1 , 0);
		 for (i=0; i<(16*percent)/100; i++)
		 {
			 LCD_WriteChar(1);
		 }
		 LCD_WriteSentence("       ");
		 
		
		//STEPPER_Bibolar_CCW();
			
			//STEPPER_Unibolar_CW();
			//STEPPER_Unibolar_CCW();
			//STEPPER_Unibolar_HS_CW();
	
	}
}

