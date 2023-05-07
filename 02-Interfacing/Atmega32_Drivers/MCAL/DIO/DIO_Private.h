/*
 * DIO_Private.h
 *
 * Created: 7/7/2022 10:02:07 PM
 *  Author: Osama
 */ 


#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_


extern const DIO_PinStatus_type PinsStatusArray[TOTAL_PINS];

static void DIO_InitPin(DIO_Pin_type pin, DIO_PinStatus_type status);

#endif /* DIO_PRIVATE_H_ */