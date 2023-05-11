/*
 * MicroChip_EEPROM_25AA010A.c
 *
 * Created: 8/25/2021 2:41:48 PM
 *  Author: Osama Mahmoud
 */ 

#include <util/delay.h>
#include "MicroChip_EEPROM_25AA010A.h"


void EEPROM_Init(void)
{
	DIO_WritePin(CHIP_SELECT_PIN , HIGH);
	SPI_voidInit();	
}

void EEPROM_WriteByte(u8 Data , u16 Address)
{
	/* Select EEPROM by Applying 0 to cs */
	DIO_WritePin(CHIP_SELECT_PIN , LOW);
	/* Write Latch Enable */
	SPI_u8SendReceive(WREN_OPCODE);
	/* Apply High to cs to Make write Latch Enable Instruction Executed */
	DIO_WritePin(CHIP_SELECT_PIN , HIGH);
	_delay_ms(50);
	/*Select EEPROM by Applying 0 to cs */
	DIO_WritePin(CHIP_SELECT_PIN , LOW);
	SPI_voidSendByte(WRITE_OPCODE); 
	SPI_voidSendByte(Address);
	SPI_voidSendByte(Data);
	DIO_WritePin(CHIP_SELECT_PIN , HIGH);
}
u8 EEPROM_ReadByte(u16 Address)
{
	u8 ReadData = 0;
	/* Select EEPROM by Applying 0 to cs */
	DIO_WritePin(CHIP_SELECT_PIN , LOW);
	SPI_voidSendByte(READ_OPCODE);
	SPI_voidSendByte(Address);
	ReadData = SPI_u8SendReceive(DUMMY_DATA);
	DIO_WritePin(CHIP_SELECT_PIN , HIGH);
	return ReadData;
}
