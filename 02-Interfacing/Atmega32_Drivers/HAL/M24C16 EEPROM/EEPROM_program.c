/*
 * EEPROM_program.c
 *
 * Created: 4/29/2022 2:15:55 PM
 *  Author: Osama Mahmoud
 */ 

#include "MemMap.h"
#include "StdTypes.h"
#include "I2C_interface.h"
#include "EEPROM_interface.h"


void EEPROM_writeByte(u16 u16addr, u8 u8data)
{
	I2C_writeByte(EEPROM_ADDRESS , (u8)u16addr , u8data);
}

void EEPROM_readByte(u16 u16addr, u8 *u8data)
{
   *u8data = I2C_ReadByte(EEPROM_ADDRESS , (u8)u16addr);
}
