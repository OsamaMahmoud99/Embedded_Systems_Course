/*
 * DIO_Interface.h
 *
 * Created: 7/7/2022 10:01:10 PM
 *  Author: Osama
 */ 


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "StdTypes.h"
#include "Utils.h"


typedef enum
{	
	PA=0,
	PB,
	PC,
	PD
}DIO_Port_type;
	
typedef enum
{
	LOW=0,
	HIGH=1,
}DIO_PinVoltage_type;

typedef enum{
	OUTPUT,
	INFREE,
	INPULLUP
	}DIO_PinStatus_type;

typedef enum
{
	PINA_0=0,
	PINA_1=1,
	PINA_2,
	PINA_3,
	PINA_4,
	PINA_5,
	PINA_6,
	PINA_7,
	PINB_0,
	PINB_1,
	PINB_2,
	PINB_3,
	PINB_4,
	PINB_5,
	PINB_6,
	PINB_7,
	PINC_0,
	PINC_1,
	PINC_2,
	PINC_3,
	PINC_4,
	PINC_5,
	PINC_6,
	PINC_7,
	PIND_0,
	PIND_1,
	PIND_2,
	PIND_3,
	PIND_4,
	PIND_5,
	PIND_6,
	PIND_7,
	TOTAL_PINS
}DIO_Pin_type;

extern void DIO_Init(void);
extern void DIO_WritePin(DIO_Pin_type pin, DIO_PinVoltage_type volt);
extern DIO_PinVoltage_type DIO_ReadPin(DIO_Pin_type pin);
extern void DIO_TogglePin(DIO_Pin_type pin);
extern void DIO_WritePort(DIO_Port_type port , u8 Value);


#endif /* DIO_INTERFACE_H_ */