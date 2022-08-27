/*
 * UART_Service.h
 *
 * Created: 7/28/2022 4:19:01 PM
 *  Author: Osama
 */ 


#ifndef UART_SERVICE_H_
#define UART_SERVICE_H_

#include "UART_Interface.h"


void UART_SendString(u8 *pstr);
void UART_ReceiveString(u8 *pstr);
void UART_SendNumber(u32 num);


void UART_SendStringCheckSum(u8 *str);
u8   UART_ReceiveStringCheckSum(u8 *str);


void UART_ReceiveString_Asynch(u8 *Str);

void UART_SendStringAsynch(u8 *pstr);
void UART_ReceiveStringAsynch(u8 *pstr);

void UART_BCM_Init(void);
void UART_BCM_Runnable(u8 *pstr);


#endif /* UART_SERVICE_H_ */