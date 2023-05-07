/*
 * BLTH_Program.c
 *
 * Created: 7/31/2022 11:21:06 AM
 *  Author: Osama
 */ 

#include "BLTH_Interface.h"

void BLTH_Init(void)
{
	UART_Init();
}

void BLTH_GetData(u8 *pdata)
{
	*pdata = UART_ReceiveByte();
}