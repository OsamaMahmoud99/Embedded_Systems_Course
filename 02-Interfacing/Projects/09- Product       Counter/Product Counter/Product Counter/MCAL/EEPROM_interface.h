/*
 * ُeeprom.h
 *
 * Created: 9/11/2018 1:34:49 PM
 *  Author: Osama Mahmoud
 */ 
#ifndef EEPROM_H_
#define EEPROM_H_

static void (*EEPROM_FPTR)(void) = NULLPTR;
									
void EEPROM_voidWrite(u16 Copy_u16Address, u8 Copy_u8Data);
u8 EEPROM_u8Read(u16 Copy_u16Address);
u32 EEPROM_READ_4byte(u16 Copy_u16Address);
void EEPROM_WRITE_4byte(u16 Copy_u16Address,u32 Copy_u32Data);
void EEPROM_voidSetCallBack(void (*FPTR)(void));

#endif /* ُEEPROM_H_ */
