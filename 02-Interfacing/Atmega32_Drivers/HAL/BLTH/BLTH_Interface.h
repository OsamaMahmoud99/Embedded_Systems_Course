/*
 * BLTH_Interface.h
 *
 * Created: 7/31/2022 11:21:26 AM
 *  Author: Osama
 */ 


#ifndef BLTH_INTERFACE_H_
#define BLTH_INTERFACE_H_

#include "UART_Interface.h"

void BLTH_Init(void);

void BLTH_GetData(u8 *pdata);  //with polling



#endif /* BLTH_INTERFACE_H_ */