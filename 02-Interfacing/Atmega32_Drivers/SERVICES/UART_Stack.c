/*
 * UART_Stack.c
 *
 * Created: 7/31/2022 12:27:09 PM
 *  Author: Osama
 */ 

#include "UART_Stack.h"

static u8 Stack[STACK_SIZE];
static u8 SP=0;


Stack_Status_Type Push(u8 data)
{
	Stack_Status_Type Status;
	if(SP==STACK_SIZE)
	{
		Status= STACK_FULL;
	}
	else
	{
		Stack[SP]=data;
		SP++;
		Status= DONE;
	}
	return Status;
}

Stack_Status_Type Pop(u8 *Pdata)
{
	Stack_Status_Type Status;
	if(SP==0)
	{
		Status= STACK_EMPTY;
	}
	else
	{
		SP--;
		*Pdata=Stack[SP];
		Status= DONE;
	}
	return Status;
}
