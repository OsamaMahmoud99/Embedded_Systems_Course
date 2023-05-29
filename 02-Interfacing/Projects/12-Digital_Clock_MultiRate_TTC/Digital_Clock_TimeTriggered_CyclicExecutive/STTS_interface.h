/*
 * Kernel_Interface.h
 *
 * Created: 8/17/2022 9:58:31 AM
 *  Author: Osama
 */


#ifndef STTS_INTERFACE_H_
#define STTS_INTERFACE_H_


/**************************************************************************************/
/*                                Interfacing macros                                  */
/**************************************************************************************/
#define TASK_READY                          (1)
#define TASK_SUSPENDED                      (2)

/**************************************************************************************/
/*                                Interfacing task structure                          */
/**************************************************************************************/

typedef struct{
	
	u16  priodicity;
	u16  FirstDelay;
	void (*TaskHandler)(void);
	u8   State;
}task_t;


/**************************************************************************************/
/*                                Interfacing Functions                               */
/**************************************************************************************/

void STTS_voidStart(void);

u8 STTS_u8CreateTask(u8 Copy_u8Priority,void (*Copy_pvTaskFunc)(void),u16 Copy_u16Periodicity,u16 Copy_u16FirstDelay);

void STTS_voidSuspendTask(u8 Copy_u8Priority);

void STTS_voidResumeTask(u8 Copy_u8Priority);

void STTS_voidDeleteTask(u8 Copy_u8Priority);

/*sleep modes*/
//Bits 6..4 – SM2..0: Sleep Mode Select Bits 2, 1, and 0
#define IDLE_MODE                (0)
#define ADC_NOISE_REDUCTION      (1)
#define POWER_DOWN_MODE          (2)
#define POWER_SAVE_MODE          (3)
#define STAND_BY_MODE            (6)

/*Sleep enable bit*/
#define SE               (7)

/* sleep mode operations */
#define SELECT_SLEEP_MODE(mode)                  MCUCR |= ((1<<SE)|(mode << 4))

// it is recommended to set the Sleep Enable (SE) bit just before the execution of theSLEEP instruction.
#define MCU_GTS()                                asm("sleep \r \n")



#endif /* KERNEL_INTERFACE_H_ */
