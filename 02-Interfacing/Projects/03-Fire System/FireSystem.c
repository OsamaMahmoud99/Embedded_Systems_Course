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
#include "ADC_Interface.h"


#define LED_Y     PINC6
#define LED_R     PINC7




int main(void)
{
	DIO_Init();
	LCD_Init();
    ADC_Init(ADC_VCC , divfact64);
     
	u16 Temp;
	u8 percent;
	u8 enteredPasswordLength = 0;	
	
	u8 pass[] = "123";
	u8 Input_pass[4];
	u8* input_ptr = Input_pass;	
	u8 Key;
	
	bool_t Fire_Flag = FALSE;
	
	LCD_GoTo(0 , 0);
	LCD_WriteSentence("T=");
	 
	while (1)
	{   
		
		 Temp = LM35_GetTemp();
		 LCD_GoTo(0 , 3);
		 LCD_WriteNumber(Temp/10);
		 LCD_WriteChar('.');
		 LCD_WriteNumber(Temp%10);
		
		 if ((Temp < 400) && Fire_Flag==FALSE)
		 {
			 LCD_GoTo(1 , 5);
			 LCD_WriteSentence("Fine");
			 DIO_WritePin(LED_Y , LOW);
			 DIO_WritePin(LED_R , LOW);
			 MOTOR_Stop(M1);
		 }
		 else if (Temp > 450)
		 {
			  if ((percent < 50) && (Fire_Flag==FALSE))
			  {     
				  
				    LCD_GoTo(1 , 5);
				    LCD_WriteSentence("Heat");
				    DIO_WritePin(LED_Y , HIGH);
			  }
			
			  LCD_GoTo(0 , 9);
			  LCD_WriteSentence("S=");
			  percent = POT_GetPercentage();
		      LCD_WriteNumber(percent);
		      LCD_WriteChar('%');
			  if (percent > 50)
			  {
				    LCD_GoTo(1 , 5);
				    LCD_WriteSentence("Fire");
					DIO_WritePin(LED_Y , LOW);
				    DIO_WritePin(LED_R , HIGH);
				    MOTOR_CW(M1);
					Fire_Flag = TRUE;
			  }
			
		 }
		 
		Key = KEYPAD_GetChar();
		if (Key != NOTPRESSED)
		{
			    *input_ptr = Key;
			 	 input_ptr++;
			 	 enteredPasswordLength++;
		}
		if (enteredPasswordLength == 3)
		{
		 if (string_compare(Input_pass , pass) == 1)
		 {
			Fire_Flag = FALSE;
		 }
			enteredPasswordLength = 0;
			input_ptr = Input_pass;
			LCD_GoTo(0 , 9);
			LCD_WriteSentence("      ");
		}
	}
}

