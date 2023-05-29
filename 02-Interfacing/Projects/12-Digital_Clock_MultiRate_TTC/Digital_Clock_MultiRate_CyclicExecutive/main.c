/*
 * TrafficLight.c
 *
 * Created: 3/10/2023 6:22:47 AM
 * Author : osama
 */ 

#include <util/delay.h>
#include "MemMap.h"
#include "StdTypes.h"
#include "DIO_Interface.h"
#include "STTS_interface.h"
#include "SW.h"
#include "TIME.h"
#include "SSD.h"

int main(void)
{

    DIO_Init();



    u8 i = 0;

    while (1) 
    {
    	SSD_Update();

    	i++;

    	if(i%4 == 0)
    	{
    		i = 0;
    		SW_Update();
    		TIME_Update();
    	}
    	_delay_ms(5);

    }
}

