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
#include "Timer_Service.h"
#include "SW.h"
#include "TIME.h"
#include "SSD.h"

/* Time-riggered Cyclic Executive is More Deterministic than Multi rate 
            Cyclic Executive and less power consumption due to using sleep mode */
			
void sEos_ISR(void)
{
	static u8 i = 0;
	SSD_Update();

	i++;
	if(i%4 == 0)
	{
		SW_Update();
		TIME_Update();
		i = 0;

	}
}

int main(void)
{

    DIO_Init();

    /************ First way using Timer1 directly and sEos_ISR Function *************/
    /*Enable global interrupts*/
    sei();

    /* set interrupt each 5 ms */
	Timer1_SetInterruptTime_ms(5,&sEos_ISR);

	/* set sleep mode to idle */
//	When the SM2:0 bits are written to 000, the SLEEP instruction makes the MCU enter Idle mode, stopping the CPU
//	but allowing SPI, USART, Analog Comparator, ADC, Two-wire Serial Interface, Timer/Counters, Watchdog, and
//	the interrupt system to continue operating.
	SELECT_SLEEP_MODE(IDLE_MODE);

/***********************************************************************************/

/************** second way using STTS Module ***************************************/

    /* tick=5ms */
   // STTS_u8CreateTask(0 ,SW_Update, 4 , 0);       // every 20 ms
   // STTS_u8CreateTask(1 ,TIME_Update, 4 , 0);     // every 20 ms
    //STTS_u8CreateTask(2 ,SSD_Update, 1 , 0);         // every 5 ms

   // STTS_voidStart();
/***********************************************************************************/

    //SELECT_SLEEP_MODE(IDLE_MODE); /* for test sleep mode */

    while (1) 
    {
    	MCU_GTS();

    	//DIO_WritePin(PINC0 , HIGH);  /* for test sleep mode */
    }
}

