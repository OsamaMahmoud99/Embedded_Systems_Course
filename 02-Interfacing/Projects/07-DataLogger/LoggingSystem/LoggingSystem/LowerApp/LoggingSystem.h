/*
 * LoggingSystem.h
 *
 * Created: 8/25/2021 7:00:00 PM
 *  Author: Osama Mahmoud
 */ 


#ifndef LOGGINGSYSTEM_H_
#define LOGGINGSYSTEM_H_

#include "UART_interface.h"
#include "UART_services.h"
#include "MicroChip_EEPROM_25AA010A.h"


#define  NEWLINE    0x0d

void DATALogger_Init(void);
void DATALogger_Start(void);


#endif /* LOGGINGSYSTEM_H_ */