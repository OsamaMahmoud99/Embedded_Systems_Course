#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Mem_Map32.h"
#include "DIO_config.h"

typedef enum
{
	PA=0,
	PB,
	PC,
	PD,
	}Port_type;
	
typedef enum
{
	LOW=0,
	HIGH=1,
	}VoltageLevel_type;

/* If you want to use DIO_Init and define all Pins as output or Input from DIO_config.c use these functions and that case you should not make 
   an Init function for Keypad or Lcd to define its pins used  */
void DIO_Init(void);
void DIO_WritePort(Port_type Port, u8 Value);
void DIO_WriteBitsInPort(Port_type Port,u8 Value,u8 Mask);
u8 DIO_ReadPort(Port_type Port);
void DIO_WritePin(PinNum_type Pin,VoltageLevel_type Value);
void DIO_TogglePin(PinNum_type Pin);
VoltageLevel_type DIO_ReadPin(PinNum_type Pin);
/************************************************************************************************************/
void DIO_setpinDirection( Port_type port, u8 pin,PinStatus_type Direction);
void DIO_setpinvalue(Port_type port,u8 pin,VoltageLevel_type value);
VoltageLevel_type	 DIO_Getpinvalue(Port_type port,u8 pin);
void DIO_voidSetPortDirection(Port_type port , u8 Copy_u8Direction);
void DIO_voidSetPortValue(Port_type port , u8 Copy_u8Value);
void DIO_higher_nibble_Direction(Port_type portNumber);
void DIO_lower_nibble_Direction(Port_type  portNumber);
void DIO_higher_nibble_Value(Port_type portNumber,u8 value);
void DIO_lower_nibble_value(Port_type  portNumber,u8 value);
u8   DIO_get_lower_nibble(Port_type port);
u8   DIO_get_higher_nibble(Port_type port);

#endif
