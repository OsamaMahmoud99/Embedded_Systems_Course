/*
 * EEPROM_interface.h
 *
 * Created: 4/29/2022 2:16:18 PM
 *  Author: Osama Mahmoud
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

#define I2C_ADDRESS 0b0000001

#define EEPROM_ADDRESS    0xA0

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void EEPROM_writeByte(u16 u16addr,u8 u8data);
void EEPROM_readByte(u16 u16addr,u8 *u8data);
 

#endif /* EEPROM_INTERFACE_H_ */