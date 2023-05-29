/*
 * Kernel_Program.c
 *
 * Created: 8/17/2022 10:01:07 AM
 *  Author: Osama
 */

/***********************************************************************************/
/*                                Includes                                         */
/***********************************************************************************/
#include "StdTypes.h"
#include "MemMap.h"

#include "Timer_Service.h"

#include "STTS_Interface.h"
#include "STTS_cfg.h"

/***********************************************************************************/
/*                                Important variables                              */
/***********************************************************************************/

/*Global array used as a task pool*/
static task_t SystemTasks[NUMBER_OF_TASKS];


#define OK		0
#define NOK		1

static void Scheduler (void)
{
	u8 Local_u8TaskCounter;

	for(Local_u8TaskCounter=0;Local_u8TaskCounter<NUMBER_OF_TASKS;Local_u8TaskCounter++)
	{

		if (SystemTasks[Local_u8TaskCounter].State == TASK_READY)
		{
			if(SystemTasks[Local_u8TaskCounter].FirstDelay == 0)
			{
				/*Invoke the task function if it is not NULL*/
				if(SystemTasks[Local_u8TaskCounter].TaskHandler != NULL)
				{
					SystemTasks[Local_u8TaskCounter].TaskHandler();
				}

				SystemTasks[Local_u8TaskCounter].FirstDelay = SystemTasks[Local_u8TaskCounter].priodicity-1;

			}
			else
			{
				SystemTasks[Local_u8TaskCounter].FirstDelay--;
					/*Do nothing*/
			}

		}
		else
		{
			/* Task is suspended */
		}

	}
}


void STTS_voidStart(void)
{
	/*Configure timer to generate interrupt every 1 ms*/
	Timer1_SetInterruptTime_ms(5,&Scheduler);

	/*Enable global interrupts*/
	sei();
}

u8 STTS_u8CreateTask(u8 Copy_u8Priority,void (*Copy_pvTaskFunc)(void),u16 Copy_u16Periodicity,u16 Copy_u16FirstDelay)
{
	u8 Local_u8ErrorState= OK;
	if(Copy_pvTaskFunc != NULL)
	{
		/*check if the given priority is available or not*/
		if(SystemTasks[Copy_u8Priority].TaskHandler == NULL)
		{
			SystemTasks[Copy_u8Priority].priodicity= Copy_u16Periodicity;
			SystemTasks[Copy_u8Priority].TaskHandler= Copy_pvTaskFunc;
			SystemTasks[Copy_u8Priority].State= TASK_READY;
			SystemTasks[Copy_u8Priority].FirstDelay = Copy_u16FirstDelay;
		}
		else
		{
			/*priority is not available*/
		}
	}
	else
	{
		Local_u8ErrorState= NOK;
	}
	return Local_u8ErrorState;
}

void STTS_voidSuspendTask(u8 Copy_u8Priority)
{
	SystemTasks[Copy_u8Priority].State=TASK_SUSPENDED;
}

void STTS_voidResumeTask(u8 Copy_u8Priority)
{
	SystemTasks[Copy_u8Priority].State= TASK_READY;
}

void STTS_voidDeleteTask(u8 Copy_u8Priority)
{
	SystemTasks[Copy_u8Priority].TaskHandler= NULL;
}


