/*
 * DIO_Program.c
 *
 * Created: 7/7/2022 10:00:47 PM
 *  Author: Osama
 */ 

#include "DIO_Private.h"
#include "DIO_Interface.h"

static void DIO_InitPin(DIO_Pin_type pin , DIO_PinStatus_type status);
extern const DIO_PinStatus_type PinsStatusArray[TOTAL_PINS];

void DIO_Init(void)
{
	DIO_Pin_type counter;
	for (counter=PINA_0; counter<TOTAL_PINS; ++counter)
	{
		DIO_InitPin(counter , PinsStatusArray[counter]);
	}
}

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
			SET_BIT(DDRA_REG , pin_num);
			CLR_BIT(PORTA_REG , pin_num);
			break;
			case PB:
			SET_BIT(DDRB_REG , pin_num);
			CLR_BIT(PORTB_REG , pin_num);
			break;
			case PC:
			SET_BIT(DDRC_REG , pin_num);
			CLR_BIT(PORTC_REG , pin_num);
			break;
			case PD:
			SET_BIT(DDRD_REG , pin_num);
			CLR_BIT(PORTD_REG , pin_num);
			break;
		}
		break;
		case INFREE:
		switch(port)
		{
			case PA:
			CLR_BIT(DDRA_REG , pin_num);
			CLR_BIT(PORTA_REG , pin_num);
			break;
			case PB:
			CLR_BIT(DDRB_REG , pin_num);
			CLR_BIT(PORTB_REG , pin_num);
			break;
			case PC:
			CLR_BIT(DDRC_REG , pin_num);
			CLR_BIT(PORTC_REG , pin_num);
			break;
			case PD:
			CLR_BIT(DDRD_REG , pin_num);
			CLR_BIT(PORTD_REG , pin_num);
			break;
		}
		break;
		case INPULLUP:
		switch(port)
		{
			case PA:
			CLR_BIT(DDRA_REG , pin_num);
			SET_BIT(PORTA_REG , pin_num);
			break;
			case PB:
			CLR_BIT(DDRB_REG , pin_num);
			SET_BIT(PORTB_REG , pin_num);
			break;
			case PC:
			CLR_BIT(DDRC_REG , pin_num);
			SET_BIT(PORTC_REG , pin_num);
			break;
			case PD:
			CLR_BIT(DDRD_REG , pin_num);
			SET_BIT(PORTD_REG , pin_num);
			break;
		}
		break;
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
			CLR_BIT(PORTA_REG,pin_num);
			break;
			case PB:
			CLR_BIT(PORTB_REG,pin_num);
			break;
			case PC:
			CLR_BIT(PORTC_REG,pin_num);
			break;
			case PD:
			CLR_BIT(PORTD_REG,pin_num);
			break;
		}
	}
	else if (volt == HIGH)
	{
		switch(port)
		{
			case PA:
			SET_BIT(PORTA_REG,pin_num);
			break;
			case PB:
			SET_BIT(PORTB_REG,pin_num);
			break;
			case PC:
			SET_BIT(PORTC_REG,pin_num);
			break;
			case PD:
			SET_BIT(PORTD_REG,pin_num);
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
		volt = READ_BIT(PINA_REG,pin_num);
		break;
		case PB:
		volt = READ_BIT(PINB_REG,pin_num);
		break;
		case PC:
		volt = READ_BIT(PINC_REG,pin_num);
		break;
		case PD:
		volt = READ_BIT(PIND_REG,pin_num);
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
		TOG_BIT(PORTA_REG,pin_num);
		break;
		case PB:
		TOG_BIT(PORTB_REG,pin_num);
		break;
		case PC:
		TOG_BIT(PORTC_REG,pin_num);
		break;
		case PD:
		TOG_BIT(PORTD_REG,pin_num);
		break;
	}
}

void DIO_WritePort(DIO_Port_type port , u8 Value)
{
	switch(port)
	{
		case PA:
		PORTA_REG = Value;
		break;
		case PB:
		PORTB_REG = Value;
		break;
		case PC:
		PORTC_REG = Value;
		break;
		case PD:
		PORTD_REG = Value;
		break;
	}
}
void DIO_WriteBitsInPort(DIO_Port_type Port,u8 Value,u8 Mask)
{
	switch (Port)
	{
		case PA:
		CLR_BITS_REG(PORTA_REG,Mask);
		SET_BITS_REG(PORTA_REG,Value&Mask);
		break;
		case PB:
		CLR_BITS_REG(PORTB_REG,Mask);
		SET_BITS_REG(PORTB_REG,Value&Mask);
		break;
		case PC:
		CLR_BITS_REG(PORTC_REG,Mask);
		SET_BITS_REG(PORTC_REG,Value&Mask);
		break;
		case PD:
		CLR_BITS_REG(PORTD_REG,Mask);
		SET_BITS_REG(PORTD_REG,Value&Mask);
		break;
	}
}
void DIO_higher_nibble_Value(DIO_Port_type portNumber,u8 value)
{
	value<<=4;
	switch(portNumber)
	{
		case PA:
		PORTA_REG&=0x0f;
		PORTA_REG|=value;
		
		break;
		case PB:
		PORTB_REG&=0x0f;
		PORTB_REG|=value;
		
		break;
		case PC:
		PORTC_REG&=0x0f;
		PORTC_REG|=value;
		
		break;
		case PD:
		PORTD_REG&=0x0f;
		PORTD_REG|=value;
		higher_nibble_value(PORTD_REG,value);
		break;
	}
	
}

void DIO_lower_nibble_value(DIO_Port_type portNumber,u8 value)
{
	value&=0x0f;
	switch(portNumber)
	{
		case PA:
		PORTA_REG&=0xf0;
		PORTA_REG|=value;
		
		break;
		case PB:
		PORTB_REG&=0xf0;
		PORTB_REG|=value;
		
		break;
		case PC:
		PORTC_REG&=0xf0;
		PORTC_REG|=value;
		
		break;
		case PD:
		PORTD_REG&=0xf0;
		PORTD_REG|=value;
		
		break;
		
	}
}