/*
 * LoggingSystem.c
 *
 * Created: 8/25/2021 12:20:02 PM
 * Author : Osama Mahmoud
 */ 


#define  F_CPU  8000000UL
#include <util/delay.h>
#include "Mem_Map32.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "SPI_interface.h"
#include "UART_interface.h"
#include "UART_services.h"

#include "MicroChip_EEPROM_25AA010A.h"
#include "LoggingSystem.h"

int main(void)
{
    DIO_Init();
    

    DATALogger_Init();
	
    while (1) 
    {
		DATALogger_Start();
    }
}

