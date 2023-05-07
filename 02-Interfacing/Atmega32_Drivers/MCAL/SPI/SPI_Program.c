/*
 * SPI_Program.c
 *
 * Created: 8/1/2022 9:03:46 AM
 *  Author: Osama
 */ 

#define  F_CPU   8000000
#include <util/delay.h>
#include "SPI_Interface.h"
#include "SPI_Config.h"

static void (*SPI_ISR)(void);
void SPI_Init(void)
{
	#if   Data_Order == LSB
	SET_BIT(SPCR , DORD);
	#elif Data_Order == MSB
	CLR_BIT(SPCR ,DORD);
	#endif
	
	#if   Master_Slave_Select == SPI_Master
	SET_BIT(SPCR , MSTR);
	#elif Master_Slave_Select == SPI_Slave
	CLR_BIT(SPCR , MSTR);
	#endif
	
	#if   OPERATING_LEVEL ==  SPI_IDLE_LOW
	CLR_BIT(SPCR , CPOL);
	#elif OPERATING_LEVEL == SPI_IDLE_HIGH
	SET_BIT(SPCR , CPOL);
	#endif
	
	#if   SAMPLING_EDGE == SPI_RISING
	SET_BIT(SPCR , CPHA);
	#elif SAMPLING_EDGE == SPI_FALLING
	CLR_BIT(SPCR , CPHA);
	#endif
	
	SPCR|=CLK_RATE;
	
	#if   SPI_Double_SPEED == SPI_Double_SPEED_ON
	SET_BIT(SPSR , SPI2X);
	#elif SPI_Double_SPEED == SPI_Double_SPEED_OFF
	CLR_BIT(SPSR , SPI2X);
	#endif
	
	#if   SPI_STATE  == SPI_ENABLE
	SET_BIT(SPCR , SPE);
	#elif SPI_STATE  == SPI_DISABLE
	CLR_BIT(SPCR , SPE);
	#endif
	
}
u8 SPI_SendReceive(u8 Copy_u8Data)
{
	SPDR = Copy_u8Data;   // send data
	while(READ_BIT(SPSR , SPIF) == 0);
	return SPDR;       // received data
}

u8 SPI_SendReceive_RunTimeOut(u8 Copy_u8Data ,u8*pdata, u8 time)
{
	u8 c = 0;
	SPDR = Copy_u8Data;   // send data
	while(READ_BIT(SPSR , SPIF) == 0  &&(c<time))
	{
		c++;
		_delay_ms(1);
	}
	if (c == time)
	{
		return 0;	
	}
	else
	{
		*pdata = SPDR;
		return 1;
	}
}



void SPI_Send(u8 data)
{
	SPDR = data;
	while(READ_BIT(SPSR , SPIF) == 0);
}

u8 SPI_Receive(void)
{
	while(READ_BIT(SPSR , SPIF) == 0);
	return SPDR;
}
void SPI_Send_NoBlock(u8 data)
{
	SPDR = data;
}

u8 SPI_Receive_NoBlock(void) 
{
	return SPDR;
}


u8 SPI_ReceivePeriodic(u8 *data)
{
	if (READ_BIT(SPSR , SPIF))
	{
		*data = SPDR;
		return 1;
	}
	return 0;
}

void SPI_EnableInterrupt(void)
{
	SET_BIT(SPCR , SPIE);
}
void SPI_DisableInterrupt(void)
{
	CLR_BIT(SPCR , SPIE);
}
void SPI_SetCallBack(void (*PtrToSPI_ISR)(void))
{
	SPI_ISR = PtrToSPI_ISR;
}

ISR(SPI_STC_vect)
{
	
	SPI_ISR();
}
