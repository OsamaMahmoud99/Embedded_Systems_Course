/*
 * APPc.c
 *
 * Created: 7/15/2021 9:19:53 PM
 *  Author: Osama Mahmoud
 */ 

#include "APP.h"


int Ones_Count , Tens_Count;

PB_Config PB_PINS_Config[1] = 
{
	{PC , PINC0 , PC , PINC1 , PC , PINC2 , PC , PINC3}
};

LED_Config LED_PINS_Config[1]=
{
	{PA , PINA0 , PA , PINA1 , PA , PINA2 , PA , PINA3}
};


void LED_Init(void){
	
	LED_Direction(LED_PINS_Config[0].LED_Green_Port , LED_PINS_Config[0].LED_Green_Pin , OUTPUT);
	LED_Direction(LED_PINS_Config[0].LED_Red_Port   , LED_PINS_Config[0].LED_Red_Pin   , OUTPUT);
	LED_Direction(LED_PINS_Config[0].LED_Yellow_Port, LED_PINS_Config[0].LED_Yellow_Pin, OUTPUT);
	LED_Direction(LED_PINS_Config[0].Buzzer_Port    , LED_PINS_Config[0].Buzzer_Pin    , OUTPUT);
}

void LED_On(void){
	
	LED_State(LED_PINS_Config[0].LED_Green_Port , LED_PINS_Config[0].LED_Green_Pin , ON);
}

void LED_Off(void){
	
	LED_State(LED_PINS_Config[0].LED_Green_Port , LED_PINS_Config[0].LED_Green_Pin , OFF);
}

void Buzzer_On(void){
	
	LED_State(LED_PINS_Config[0].Buzzer_Port , LED_PINS_Config[0].Buzzer_Pin , ON);
}

void Buzzer_Off(void){
	
	LED_State(LED_PINS_Config[0].Buzzer_Port , LED_PINS_Config[0].Buzzer_Pin , OFF);
}

void LED_Animation(void){
	
	for (u8 i=0; i<10; ++i)
	{
		LED_State(LED_PINS_Config[0].LED_Green_Port , LED_PINS_Config[0].LED_Green_Pin , ON);
		LED_State(LED_PINS_Config[0].LED_Yellow_Port , LED_PINS_Config[0].LED_Yellow_Pin , ON);
		LED_State(LED_PINS_Config[0].LED_Red_Port , LED_PINS_Config[0].LED_Red_Pin , ON);
		
		_delay_ms(1000);
		
		LED_State(LED_PINS_Config[0].LED_Green_Port , LED_PINS_Config[0].LED_Green_Pin , OFF);
		LED_State(LED_PINS_Config[0].LED_Yellow_Port , LED_PINS_Config[0].LED_Yellow_Pin , OFF);
		LED_State(LED_PINS_Config[0].LED_Red_Port , LED_PINS_Config[0].LED_Red_Pin , OFF);
		
		_delay_ms(1000);
	}
}

void Switch_Init(void){
	
	Switch_Direction(PB_PINS_Config[0].PB_Ones_Port , PB_PINS_Config[0].PB_Ones_Pin , INPUT);
	Switch_Direction(PB_PINS_Config[0].PB_Tens_Port , PB_PINS_Config[0].PB_Tens_Pin , INPUT);
	Switch_Direction(PB_PINS_Config[0].PB_Enter_Port, PB_PINS_Config[0].PB_Enter_Pin, INPUT);
}

SWITCH_t PB_CheckPressed(void){
	SWITCH_t Push_Button = NO_PB_PRESSSED;
	
	if (Switch_CheckPressed(PB_PINS_Config[0].PB_Ones_Port , PB_PINS_Config[0].PB_Ones_Pin) == Close)
	{
		Push_Button = ONES_SS;
		while(Switch_CheckPressed(PB_PINS_Config[0].PB_Ones_Port , PB_PINS_Config[0].PB_Ones_Pin) == Close);
	}
	else if (Switch_CheckPressed(PB_PINS_Config[0].PB_Tens_Port , PB_PINS_Config[0].PB_Tens_Pin) == Close)
	{
		Push_Button = TENS_SS;
		while(Switch_CheckPressed(PB_PINS_Config[0].PB_Tens_Port , PB_PINS_Config[0].PB_Tens_Pin) == Close);
	}
	else if (Switch_CheckPressed(PB_PINS_Config[0].PB_Enter_Port , PB_PINS_Config[0].PB_Enter_Pin) == Close)
	{
		Push_Button = ENTER;
		while(Switch_CheckPressed(PB_PINS_Config[0].PB_Enter_Port , PB_PINS_Config[0].PB_Tens_Pin) == Close);
	}
	else if (Switch_CheckPressed(PB_PINS_Config[0].PB_Reset_Port , PB_PINS_Config[0].PB_Reset_Pin) == Close)
	{
		Push_Button = RESET;
		while(Switch_CheckPressed(PB_PINS_Config[0].PB_Reset_Port , PB_PINS_Config[0].PB_Reset_Pin) == Close);
	}
	return Push_Button;
}

void SEG_Init(void){
	SEG_Direction(0);
	SEG_Direction(1);
	Ones_Count = 0;
	Tens_Count = 0;
}

void SEG_Enable_PinDot(u8 Value , SS_EN_t SS_EN){
	
	switch(SS_EN)
	{
		case ONES_ENABLE:
		     DIO_setpinvalue(SEG_PINMAP[0].SEG_Dot_Port,SEG_PINMAP[0].SEG_Dot_Pin,LOW);
			 SEG_voidDisplayNumber(0 , Value);
			 break;
		case TENS_ENABLE:
		     DIO_setpinvalue(SEG_PINMAP[1].SEG_Dot_Port,SEG_PINMAP[1].SEG_Dot_Pin,LOW);
		     SEG_voidDisplayNumber(1 , Value);
		     break;
	}
}

void SEG_Increment_Ones(void){
	
	Ones_Count++;
	if (Ones_Count > 9)
	{
		Ones_Count = 0;
	}
}

void SEG_Increment_Tens(void){
	
	Tens_Count++;
	if (Tens_Count > 9)
	{
		Tens_Count = 0;
	}
}

SS_NUM_t SEG_DEF_Password(void){
	
	if ( (Ones_Count + (Tens_Count * 10)) == 49 )
	{
		return PASS;
	}
	else
	{
		return WRONG;
	}
}