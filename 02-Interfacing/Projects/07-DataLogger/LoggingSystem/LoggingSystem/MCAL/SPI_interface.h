/*
 * SPI.h
 *
 * Created: 9/18/2020 1:09:11 PM
 *  Author: OsamaMahmoud
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Mem_Map32.h"

void SPI_voidInit(void);
void SPI_voidSendByte(u8 Copy_u8Data);
u8   SPI_u8ReceiveByte(void);
u8   SPI_u8SendReceive(u8 Copy_u8Data);
void SPI_voidEnableInterrupt(void);
void SPI_voidDisableInterrupt(void);
void SPI_voidSetCallBack(void (*PtrToSPI_ISR)(void));




#endif /* SPI_H_ */