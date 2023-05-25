/*
 * TrafficLight.c
 *
 * Created: 3/10/2023 6:22:47 AM
 * Author : osama
 */ 

#include "MemMap.h"
#include "StdTypes.h"
#include "DIO_Interface.h"
#include "STTS_interface.h"
#include "TIME.h"
#include "LED.h"
#include "SSD.h"

int main(void)
{

    DIO_Init();

    STTS_u8CreateTask(0 ,LED_Update, 1000 , 0);      // every 1 second
    STTS_u8CreateTask(1 ,TIME_Update, 1000 , 0);     // every 1 second
    STTS_u8CreateTask(2 ,SSD_Update, 5 , 0);         // every 5 ms

    STTS_voidStart();

    while (1) 
    {
    }
}

