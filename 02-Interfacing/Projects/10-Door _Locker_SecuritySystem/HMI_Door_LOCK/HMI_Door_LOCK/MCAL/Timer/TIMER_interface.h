#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_


/*******************************************************************************
 *                               Message                                       *
 *******************************************************************************/

// NOTE: This Timer Driver work with ((Channel A Only)) in Timer1

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	TIMER0_ID, TIMER1_ID, TIMER2_ID
}TIMER_ID;

typedef enum
{
	TIMER_OVF_Mode, TIMER_CTC_Mode
}TIMER_Mode;

typedef enum
{
	NO_CLOCK, F_CPU_CLOCK, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024, EXTERNAL_FAILING_CLOCK, EXTERNAL_RAISING_CLOCK
}TIMER_Clock;

typedef struct
{
	TIMER_ID timer_ID;
	TIMER_Mode timer_mode;
	u32 timer_intial_value;
	TIMER_Clock timer_clock;
	u32 timer_compare_value;
}TIMER_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function to Initialize the Timer by following predefined configurations
 * 		1. Choose which Timer to work with 							--> Timer0 / Timer1 / Timer2
 * 		2. Choose which mode to operate in 							--> Overflow Mode / Compare Mode
 * 		3. Choose which initial value to start the counting from
 * 		4. Choose the prescaler of the CPU clock to generate a clock for Timer to operate by
 * 		5. Choose Compare Value if the Timer operate in Compare Mode
 */
void Timer_init(const TIMER_ConfigType * Config_Ptr);

/*
 * Description :
 * Function to set the Call Back Function Address
 */
void Timer_setCallBack(void(*a_ptr)(void), TIMER_ID timer_number);

/*
 * Description :
 * Function to stop the clock and DeInit the whole Timer
 */
void Timer_DeInit(TIMER_ID timer_number);


#endif /* TIMER_INTERFACE_H_ */
