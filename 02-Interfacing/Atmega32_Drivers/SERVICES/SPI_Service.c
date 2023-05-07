/*
 * SPI_Service.c
 *
 * Created: 8/1/2022 4:08:03 PM
 *  Author: Osama
 */ 

#define F_CPU  8000000
#include <util/delay.h>
#include "SPI_Service.h"
#include "LCD_Interface.h"

void SPI_SendString(u8 *pstr , u8 size)
{
	u8 i = 0;
	while(i < size)
	{
		SPI_SendReceive(pstr[i]);
		_delay_ms(10);
		i++;
	}
}

void SPI_ReceiveString(u8 *pstr , u8 size)
{
	u8 i = 0;
	while(i < size)
	{
		pstr[i] = SPI_SendReceive(255);
		i++;
	}
	pstr[i] = '\0';
}

void SPI_SendReceiveString(u8 *pstr , u8 *pstr_rec)
{
	u8 i = 0;
	while((pstr[i]) != 0)
	{
		pstr_rec[i] = SPI_SendReceive(pstr[i]);
		//_delay_ms(10);
		i++;
	}
	pstr_rec[i] = 0;
}

void SPI_SendNumber(u16 Number)
{
	 u8 *p = &Number;
	 SPI_SendReceive(p[0]);
     _delay_ms(10);
	 SPI_SendReceive(p[1]);
}

u16 SPI_ReceiveNumber(void)
{
	u16 num;
	u8 *p = &num;
	p[0] = SPI_SendReceive(255);
	
	p[1] = SPI_SendReceive(255);
	
	return num;
}
