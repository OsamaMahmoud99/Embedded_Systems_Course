/*
 * UART_Stack.h
 *
 * Created: 7/31/2022 12:26:54 PM
 *  Author: Osama
 */ 


#ifndef UART_STACK_H_
#define UART_STACK_H_

#include "StdTypes.h"

/***********************************/
#define  STACK_SIZE  10
/***********************************/

typedef enum
{
	STACK_EMPTY,
	STACK_FULL,
	DONE
}Stack_Status_Type;

Stack_Status_Type Push(u8 data);
Stack_Status_Type Pop(u8 *Pdata);


#endif /* UART_STACK_H_ */