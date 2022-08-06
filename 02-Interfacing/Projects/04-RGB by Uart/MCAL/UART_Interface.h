/*
 * UART_Interface.h
 *
 * Created: 7/28/2022 8:47:50 AM
 *  Author: Osama
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include "MemMap.h"
#include "StdTypes.h"
#include "Utils.h"

void UART_Init(void);
void UART_SendByte(u8 data);
u8 UART_ReceiveByte(void);
u8 UART_Receive_PeriodicCheck(u8*pdata);

/************************ used in interrupt **************************/
void UART_SendByteNoBlock(u8 data);
u8   UART_ReceiveByteNoBlock(void);


void UART_RX_InterruptEnable(void);
void UART_RX_InterruptDisable(void);

void UART_TX_InterruptEnable(void);
void UART_TX_InterruptDisable(void);

void UART_RX_SetCallBack(void (*LocalFptr)(void));
void UART_TX_SetCallBack(void (*LocalFptr)(void));




#endif /* UART_INTERFACE_H_ */