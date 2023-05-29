/*
 * DIO_Program.c
 *
 * Created: 7/7/2022 10:00:47 PM
 *  Author: Osama
 */ 

#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

#include "DIO_Interface.h"
#include "DIO_Private.h"

static void DIO_InitPin(DIO_Pin_type pin , DIO_PinStatus_type status)
{
	DIO_Port_type port = pin/8;
	u8 pin_num  = pin % 8;
	switch(status)
	{
		case OUTPUT:
		switch(port)
		{
			case PA:
			SET_BIT(DDRA , pin_num);
			CLR_BIT(PORTA , pin_num);
			break;
			case PB:
			SET_BIT(DDRB , pin_num);
			CLR_BIT(PORTB , pin_num);
			break;
			case PC:
			SET_BIT(DDRC , pin_num);
			CLR_BIT(PORTC , pin_num);
			break;
			case PD:
			SET_BIT(DDRD , pin_num);
			CLR_BIT(PORTD , pin_num);
			break;
		}
		break;
		case INFREE:
		switch(port)
		{
			case PA:
			CLR_BIT(DDRA , pin_num);
			CLR_BIT(PORTA , pin_num);
			break;
			case PB:
			CLR_BIT(DDRB , pin_num);
			CLR_BIT(PORTB , pin_num);
			break;
			case PC:
		    CLR_BIT(DDRC , pin_num);
			CLR_BIT(PORTC , pin_num);
			break;
			case PD:
			CLR_BIT(DDRD , pin_num);
			CLR_BIT(PORTD , pin_num);
			break;
		}
		break;
		case INPULLUP:
		switch(port)
		{
			case PA:
			CLR_BIT(DDRA , pin_num);
			SET_BIT(PORTA , pin_num);
			break;
			case PB:
			CLR_BIT(DDRB , pin_num);
			SET_BIT(PORTB , pin_num);
			break;
			case PC:
			CLR_BIT(DDRC , pin_num);
			SET_BIT(PORTC , pin_num);
			break;
			case PD:
			CLR_BIT(DDRD , pin_num);
			SET_BIT(PORTD , pin_num);
			break;
		}
		break;
	}
}


void DIO_Init(void)
{
	DIO_Pin_type counter;
	for (counter=PINA0; counter<TOTAL_PINS; ++counter)
	{
		DIO_InitPin(counter , PinsStatusArray[counter]);
	}
}

void DIO_WritePin(DIO_Pin_type pin, DIO_PinVoltage_type volt)
{
	DIO_Port_type port = pin/8;
	u8 pin_num  = pin % 8;
	
	if (volt == LOW)
	{
		switch(port)
		{
			case PA:
			CLR_BIT(PORTA,pin_num);
			break;
			case PB:
			CLR_BIT(PORTB,pin_num);
			break;
			case PC:
			CLR_BIT(PORTC,pin_num);
			break;
			case PD:
			CLR_BIT(PORTD,pin_num);
			break;
		}
	}
	else if (volt == HIGH)
	{
		switch(port)
		{
			case PA:
			SET_BIT(PORTA,pin_num);
			break;
			case PB:
			SET_BIT(PORTB,pin_num);
			break;
			case PC:
			SET_BIT(PORTC,pin_num);
			break;
			case PD:
			SET_BIT(PORTD,pin_num);
			break;
		}
	}
}

DIO_PinVoltage_type DIO_ReadPin(DIO_Pin_type pin)
{
	DIO_PinVoltage_type volt = LOW;
	DIO_Port_type port = pin/8;
	u8 pin_num  = pin % 8;
	
	switch (port)
	{
		case PA:
		volt = READ_BIT(PINA,pin_num);
		break;
		case PB:
		volt = READ_BIT(PINB,pin_num);
		break;
		case PC:
		volt = READ_BIT(PINC,pin_num);
		break;
		case PD:
		volt = READ_BIT(PIND,pin_num);
		break;
	}
	return volt;
}

void DIO_TogglePin(DIO_Pin_type pin)
{
	DIO_Port_type port = pin/8;
	u8 pin_num  = pin % 8;
	switch (port)
	{
		case PA:
		TOG_BIT(PORTA,pin_num);
		break;
		case PB:
		TOG_BIT(PORTB,pin_num);
		break;
		case PC:
		TOG_BIT(PORTC,pin_num);
		break;
		case PD:
		TOG_BIT(PORTD,pin_num);
		break;
	}
}

void DIO_WritePort(DIO_Port_type port , u8 Value)
{
	switch(port)
	{
		case PA:
		PORTA = Value;
		break;
		case PB:
		PORTB = Value;
		break;
		case PC:
		PORTC = Value;
		break;
		case PD:
		PORTD = Value;
		break;
	}
}
void DIO_WriteBitsInPort(DIO_Port_type Port,u8 Value,u8 Mask)
{
	switch (Port)
	{
		case PA:
		CLR_BITS_REG(PORTA,Mask);
		SET_BITS_REG(PORTA,Value&Mask);
		break;
		case PB:
		CLR_BITS_REG(PORTB,Mask);
		SET_BITS_REG(PORTB,Value&Mask);
		break;
		case PC:
		CLR_BITS_REG(PORTC,Mask);
		SET_BITS_REG(PORTC,Value&Mask);
		break;
		case PD:
		CLR_BITS_REG(PORTD,Mask);
		SET_BITS_REG(PORTD,Value&Mask);
		break;
	}
}
void DIO_higher_nibble_Value(DIO_Port_type portNumber,u8 value)
{
	value<<=4;
	switch(portNumber)
	{
		case PA:
		PORTA&=0x0f;
		PORTA|=value;
		//higher_nibble_value(PORTA,value);
		break;
		case PB:
		PORTB&=0x0f;
		PORTB|=value;
		//higher_nibble_value(PORTB,value);
		break;
		case PC:
		PORTC&=0x0f;
		PORTC|=value;
		//higher_nibble_value(PORTC,value);
		break;
		case PD:
		PORTD&=0x0f;
		PORTD|=value;
		//higher_nibble_value(PORTD,value);
		break;
	}
	
}

void DIO_lower_nibble_value(DIO_Port_type portNumber,u8 value)
{
	value&=0x0f;
	switch(portNumber)
	{
		case PA:
		PORTA&=0xf0;
		PORTA|=value;
		//lower_nibble_value(PORTA,value);
		break;
		case PB:
		PORTB&=0xf0;
		PORTB|=value;
		//lower_nibble_value(PORTB,value);
		break;
		case PC:
		PORTC&=0xf0;
		PORTC|=value;
		//lower_nibble_value(PORTC,value);
		break;
		case PD:
		PORTD&=0xf0;
		PORTD|=value;
		//lower_nibble_value(PORTD,value);
		break;
		
	}
}
