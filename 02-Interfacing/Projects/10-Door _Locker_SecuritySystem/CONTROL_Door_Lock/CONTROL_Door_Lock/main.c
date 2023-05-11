/*
 * CONTROL_Door_Lock.c
 *
 * Created: 4/30/2022 3:39:46 PM
 * Author : Osama Mahmoud
 */ 

#define F_CPU                8000000UL
#include "CTRL_DOOR_LOCK_interface.h"

int main(void)
{
    CONTROL_InitSystem();
	
	CONTROL_Processing_UpdataSystem();
	
    while (1) 
    {
    }
}

