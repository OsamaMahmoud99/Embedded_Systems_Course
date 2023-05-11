/*
 * HMI_Door_LOCK.c
 *
 * Created: 4/30/2022 12:50:03 AM
 * Author : Osama Mahmoud
 */ 

#define  F_CPU              8000000UL
#include "HMI_Door_Lock_interface.h"

int main(void)
{
	HMI_InitSystem();
	
	HMI_Processing_UpdataSystem();
    
    while (1) 
    {
    }
}

