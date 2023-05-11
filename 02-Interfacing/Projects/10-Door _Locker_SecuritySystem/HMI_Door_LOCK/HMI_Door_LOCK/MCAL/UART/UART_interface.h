

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Mem_Map32.h"



void UART_Init(void);

void UART_SendByte(u8 data);
u8 UART_ReceiveByte(void);
u8 UART_Receive_NoBlock(u8*pdata);





void UART_RX_InterruptEnable(void);
void UART_RX_InterruptDisable(void);

void UART_TX_InterruptEnable(void);
void UART_TX_InterruptDisable(void);

void UART_RX_SetCallBack(void (*LocalFptr)(void));
void UART_TX_SetCallBack(void (*LocalFptr)(void));





void UART_SendByteNoBlock(u8 data);
u8 UART_ReceiveByteNoBlock(void);




#endif /* UART_H_ */
