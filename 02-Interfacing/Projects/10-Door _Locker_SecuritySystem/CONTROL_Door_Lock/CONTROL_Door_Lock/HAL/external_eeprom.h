#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

#define TWI_ADDRESS 0b0000001

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

u8 EEPROM_writeByte(u16 u16addr,u8 u8data);
u8 EEPROM_readByte(u16 u16addr,u8 *u8data);
 
#endif /* EXTERNAL_EEPROM_H_ */
