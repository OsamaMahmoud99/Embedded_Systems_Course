/*
 * RTOS_Basic.c
 *
 * Created: 8/17/2022 10:36:16 AM
 * Author : Osama
 */ 


#define F_CPU        8000000
#include <util/delay.h>

#include "MemMap.h"
#include "StdTypes.h"
#include "DIO_Interface.h"
#include "TIMER_Interface.h"
#include "Timer_Service.h"
#include "Kernel_Interface.h"


void Task1(void)
{
	DIO_TogglePin(PINA0);
}
int main(void)
{
    DIO_Init();
	
	RTOS_u8CreateTask(0 , &Task1 , 1000 , 1);
	
	RTOS_voidStart();
	
    while (1) 
    {
    }
}

