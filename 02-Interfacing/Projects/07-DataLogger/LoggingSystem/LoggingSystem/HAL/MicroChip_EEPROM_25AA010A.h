/*
 * MicroChip_EEPROM_25AA010Ah.h
 *
 * Created: 8/25/2021 2:42:22 PM
 *  Author: Osama Mahmoud
 */ 


#ifndef MICROCHIP_EEPROM_25AA010A_H_
#define MICROCHIP_EEPROM_25AA010A_H_

#include "DIO_interface.h"
#include "SPI_interface.h"

#define  WREN_OPCODE      0x06
#define  WRITE_OPCODE     0x02
#define  READ_OPCODE      0x03

#define  DUMMY_DATA       0x00

#define CHIP_SELECT_PIN   PINB4

void EEPROM_Init(void);
void EEPROM_WriteByte(u8 Data , u16 Address);
u8   EEPROM_ReadByte(u16 Address);




#endif /* MICROCHIP_EEPROM_25AA010AH_H_ */