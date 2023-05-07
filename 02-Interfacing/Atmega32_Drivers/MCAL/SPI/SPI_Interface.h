/*
 * SPI_Interface.h
 *
 * Created: 8/1/2022 9:04:13 AM
 *  Author: Osama
 */ 


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

void SPI_Init(void);
u8   SPI_SendReceive(u8 Copy_u8Data);
void SPI_Send(u8 data);
u8 SPI_Receive(void);
u8 SPI_ReceivePeriodic(u8 *data);
void SPI_Send_NoBlock(u8 data);
u8 SPI_Receive_NoBlock(void);
void SPI_EnableInterrupt(void);
void SPI_DisableInterrupt(void);
void SPI_SetCallBack(void (*PtrToSPI_ISR)(void));


#endif /* SPI_INTERFACE_H_ */