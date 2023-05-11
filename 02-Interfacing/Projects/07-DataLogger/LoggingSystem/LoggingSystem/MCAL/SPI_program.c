/*
 * SPI.c
 *
 * Created: 9/18/2020 1:09:29 PM
 *  Author: OsamaMahmoud
 */ 
#include "SPI_interface.h"
#include "SPI_config.h"

static void (*SPI_STC)(void);

void SPI_voidInit(void)
{
	#if   Data_Order == LSB
	SET_BIT(SPCR , DORD);
	#elif Data_Order == MSB
	CLEAR_BIT(SPCR ,DORD);
	#endif
	
	#if   Master_Slave_Select == SPI_Master
	SET_BIT(SPCR , MSTR);
	#elif Master_Slave_Select == SPI_Slave
	CLEAR_BIT(SPCR , MSTR);
	#endif
	
	#if   OPERATING_LEVEL ==  SPI_IDLE_LOW
	CLEAR_BIT(SPCR , CPOL);
	#elif OPERATING_LEVEL == SPI_IDLE_HIGH
	SET_BIT(SPCR , CPOL);
	#endif
	
	#if   SAMPLING_EDGE == SPI_RISING
	SET_BIT(SPCR , CPHA);
	#elif SAMPLING_EDGE == SPI_FALLING
	CLEAR_BIT(SPCR , CPHA);
	#endif
	
	SPCR|=CLK_RATE;
	
	#if   SPI_Double_SPEED == SPI_Double_SPEED_ON
	SET_BIT(SPSR , SPI2X);
	#elif SPI_Double_SPEED == SPI_Double_SPEED_OFF
	CLEAR_BIT(SPSR , SPI2X);
	#endif
	
	#if   SPI_STATE  == SPI_ENABLE
	SET_BIT(SPCR , SPE);
	#elif SPI_STATE  == SPI_DISABLE
	CLEAR_BIT(SPCR , SPE);
	#endif	 
	
}

void SPI_voidSendByte(u8 Copy_u8Data)
{
	 SPDR = Copy_u8Data;   // send data
	 while(CHECK_BIT(SPSR , SPIF) == 0);
}

u8   SPI_u8ReceiveByte(void)
{
	u8 Dummy = 0x00;
	SPDR = Dummy;
	while(CHECK_BIT(SPSR , SPIF) == 0);
	return SPDR;
}

u8 SPI_u8SendReceive(u8 Copy_u8Data)
{     
	  //CLEAR_BIT(PORTB , 0);
	  SPDR = Copy_u8Data;   // send data
	  while(CHECK_BIT(SPSR , SPIF) == 0);
	  return SPDR;       // received data
	 // SET_BIT(PORTB , 0);
}

void SPI_voidEnableInterrupt(void)
{
      SET_BIT(SPCR , SPIE);	
}

void SPI_voidDisableInterrupt(void)
{
	 CLEAR_BIT(SPCR , SPIE);	
}

void SPI_voidSetCallBack(void (*PtrToSPI_ISR)(void))
{
	SPI_STC = PtrToSPI_ISR;
}

ISR(SPI_STC_vect)
{
	if(SPI_STC != NULLPTR){
		SPI_STC();
	}
}