/*
 * SPI_Service.h
 *
 * Created: 8/1/2022 4:08:18 PM
 *  Author: Osama
 */ 


#ifndef SPI_SERVICE_H_
#define SPI_SERVICE_H_

#include "SPI_Interface.h"

void SPI_SendString(u8 *pstr , u8 size);
void SPI_SendNumber(u16 Number);


#endif /* SPI_SERVICE_H_ */
