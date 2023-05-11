/*
 * Product Counter.c
 *
 * Created: 11/25/2020 10:08:59 PM
 * Author : OsamaMahmoud
 */ 

#define  F_CPU  8000000UL

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Mem_Map32.h"

#include "DIO_interface.h"
#include "EEPROM_interface.h"
#include "EXTI_interface.h"

#include "LCD_interface.h"
#include "KEYPAD_interface.h"

 
 typedef enum
 {
	 OFF_MOTOR,
	 ON_MOTOR
 }State_Motor;

 #define SETTING     PINA0
 #define START       PINA1
 #define STARTMOTOR  PINA2
 #define STOPMOTOR   PINA3
 #define BUZZER      PIND0
 #define MOTOR       PINA5

 #define FirstTime         0xFF
 #define StatusLocation    0x00
 #define ProductLocation   0x10
 #define CountLocation     0x20
 #define RemainderLocation 0x30
 #define PassLocation      0x40

 void System_Init(void);
 void Count(void);
 void Setting(void);
 void Get_NumOfProducts(void);
 void On_Motor(void);
 void Off_Motor(void);

u8 NumOfProducts;
volatile u8  ProductCount;
State_Motor Status = OFF_MOTOR;
volatile u8 Count_Flag = 0;

int main(void)
{
	sei();   // enable global Interrupt
	DIO_Init();
	LCD_Init();
	KEYPAD_voidInit();
	
	EXI_Enable(EX_INT0);
	EXI_TriggerEdge(EX_INT0,FALLING_EDGE);
	EXI_SetCallBack(EX_INT0,Count);
	
	EXI_Enable(EX_INT1);
	EXI_TriggerEdge(EX_INT1,FALLING_EDGE);
	EXI_SetCallBack(EX_INT1,On_Motor);
	
	EXI_Enable(EX_INT2);
	EXI_TriggerEdge(EX_INT2,FALLING_EDGE);
	EXI_SetCallBack(EX_INT2,Off_Motor);
	
	DIO_WritePin(MOTOR , LOW);  // off motor
	DIO_WritePin(BUZZER , LOW);  // off buzzer
	
	if (EEPROM_u8Read(StatusLocation) == FirstTime)
	{
		Get_NumOfProducts();
	}
	else
	{
		NumOfProducts = EEPROM_u8Read(ProductLocation);
		ProductCount = EEPROM_u8Read(PassLocation);
		LCD_GoTo(0,0);
		LCD_WriteSentence("Req Number =");
		LCD_GoTo(0,13);
		LCD_WriteNumber(NumOfProducts);
		LCD_GoTo(1,0);
		LCD_WriteSentence("Product Number=");
		LCD_GoTo(1,15);
		LCD_WriteNumber(ProductCount);
		
	}
	while (1)
	{
		if (Count_Flag == 1)
		{
			ProductCount+=1;
			EEPROM_voidWrite(PassLocation , ProductCount);
			LCD_Clear();
			LCD_GoTo(0,0);
			LCD_WriteSentence("Req Number=");
			LCD_GoTo(0,13);
			LCD_WriteNumber(NumOfProducts);
			LCD_GoTo(1,0);
			LCD_WriteSentence("Pass product=");
			LCD_GoTo(1,15);
			LCD_WriteNumber(ProductCount);
			EEPROM_voidWrite(RemainderLocation , (NumOfProducts - ProductCount));
			LCD_GoTo(2,0);
			LCD_WriteSentence("Remainder=");
			LCD_GoTo(2,13);
			LCD_WriteNumber(EEPROM_u8Read(RemainderLocation));
			if (NumOfProducts == ProductCount)
			{
				LCD_Clear();
			}
			
			Count_Flag = 0;
		}
		if (ProductCount < NumOfProducts)
		{
			DIO_WritePin(BUZZER , LOW);
			
			if (DIO_ReadPin(START) == 0)
			{
				
				if (Status == ON_MOTOR)
				{
					DIO_WritePin(MOTOR , HIGH);
				}
				else if (Status == OFF_MOTOR)
				{
					DIO_WritePin(MOTOR , LOW);
					
				}
				
			}
		}
		else
		{
			LCD_Clear();
			LCD_GoTo(0,0);
			LCD_WriteSentence("Finish!");
			DIO_WritePin(BUZZER , HIGH);
			DIO_WritePin(MOTOR , LOW);
		}
		
		if (DIO_ReadPin(SETTING) == 0)
		{
			Setting();
		}
	}
}
/**************************** Interrupt Functions****************************/
void On_Motor(void)
{
	Status = ON_MOTOR;
}

void Off_Motor(void)
{
	Status = OFF_MOTOR;
}

void Count(void)
{
	Count_Flag = 1;
}
/***************************************************************************/

void Get_NumOfProducts(void)
{
	LCD_Clear();
	LCD_GoTo(0,0);
	LCD_WriteSentence("Set Products:");
	
	u8 Flag = 1;
	
	do
	{
		
		u8 Local_u8Num = KEYPAD_u8GetPressed();
		
		if (Local_u8Num != '=')
		{
			LCD_GoTo(0,14);
			LCD_WriteChar(Local_u8Num);
			NumOfProducts = Local_u8Num - 48;
		}
		
		if (Local_u8Num == '=')
		{
			LCD_Clear();
			LCD_GoTo(0,0);
			LCD_WriteSentence("Req Number =");
			LCD_GoTo(0,13);
			LCD_WriteNumber(NumOfProducts);
			
			EEPROM_voidWrite(ProductLocation,NumOfProducts);
			EEPROM_voidWrite(StatusLocation,0x00);
			EEPROM_voidWrite(PassLocation , 0x00);
			EEPROM_voidWrite(RemainderLocation , (NumOfProducts - ProductCount));
			
			LCD_GoTo(1,0);
			LCD_WriteSentence("Pass product=");
			LCD_GoTo(1,14);
			LCD_WriteNumber(ProductCount);
			LCD_GoTo(2,0);
			LCD_WriteSentence("Remainder=");
			LCD_GoTo(2,14);
			LCD_WriteNumber(EEPROM_u8Read(RemainderLocation));
			
			Flag = 0;
		}
		
	} while (Flag == 1);
	
	
}

void Setting(void)
{
	DIO_WritePin(BUZZER , LOW);
	LCD_Clear();
	LCD_GoTo(0,0);
	LCD_WriteSentence("Setting");
	LCD_GoTo(1,0);
	LCD_WriteSentence("Set Products:");
	
	u8 Flag = 1;
	
	do
	{
		
		u8 Local_u8Num = KEYPAD_u8GetPressed();
		
		if (Local_u8Num != '=')
		{
			LCD_GoTo(1,14);
			LCD_WriteChar(Local_u8Num);
			NumOfProducts = Local_u8Num - 48;
		}
		
		if (Local_u8Num == '=')
		{
			LCD_Clear();
			LCD_GoTo(0,0);
			LCD_WriteSentence("Req Number =");
			LCD_GoTo(0,13);
			LCD_WriteNumber(NumOfProducts);
			
			EEPROM_voidWrite(ProductLocation,NumOfProducts);
			EEPROM_voidWrite(StatusLocation,0x00);
			EEPROM_voidWrite(PassLocation , 0x00);
			ProductCount = EEPROM_u8Read(PassLocation);
			EEPROM_voidWrite(RemainderLocation , (NumOfProducts - ProductCount));
			
			LCD_GoTo(1,0);
			LCD_WriteSentence("Pass product=");
			LCD_GoTo(1,14);
			LCD_WriteNumber(ProductCount);
			LCD_GoTo(2,0);
			LCD_WriteSentence("Remainder=");
			LCD_GoTo(2,14);
			LCD_WriteNumber(EEPROM_u8Read(RemainderLocation));
			
			Flag = 0;
		}
		
	} while (Flag == 1);
}
