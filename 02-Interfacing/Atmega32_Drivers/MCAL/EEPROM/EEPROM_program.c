/*
 * eeprom.c
 *
 * Created: 9/11/2018 1:35:59 PM
 *  Author: Osama Mahmoud
 */ 
#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"
#include "EEPROM_interface.h"



u8 EEPROM_u8Read(u16 Copy_u16Address)
{
	
	/* Set up address register */
	EEARL = (u8)Copy_u16Address;
	EEARH = (u8)(Copy_u16Address>>8);
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from data register */
	return EEDR;
}

void EEPROM_voidWrite(u16 Copy_u16Address, u8 Copy_u8Data)
{
	/* Set up address and data registers */
	EEARL = (u8)Copy_u16Address;
	EEARH = (u8)(Copy_u16Address>>8);
	EEDR = Copy_u8Data;
	
	/* Write logical one to EEMWE */
	EECR |= (1<<EEMWE);
	/* Start eeprom write by setting EEPROM_WRITE_ENABLE */
	EECR |= (1<<EEWE);
	
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE));
}
u32 EEPROM_READ_4byte(u16 Copy_u16Address)
{
	u8 val=0;
	u32 result=0;
	for(int i=0;i<4;i++)
	{
		val=EEPROM_u8Read(Copy_u16Address+i);
		result=result+(val<<i*8);
	}
	return result;
}
void EEPROM_WRITE_4byte(u16 Copy_u16Address,u32 Copy_u32Data)
{
	for(int i=0;i<4;i++)
	{
	   EEPROM_voidWrite(Copy_u16Address,(u8)(Copy_u32Data>>i*8));
	}
	
}

void EEPROM_voidSetCallBack(void (*FPTR)(void))
{
	EEPROM_FPTR = FPTR;
}
ISR(EE_RDY_vect)
{
	if (EEPROM_FPTR !=NULLPTR)
	{
		EEPROM_FPTR();
	}
	
}