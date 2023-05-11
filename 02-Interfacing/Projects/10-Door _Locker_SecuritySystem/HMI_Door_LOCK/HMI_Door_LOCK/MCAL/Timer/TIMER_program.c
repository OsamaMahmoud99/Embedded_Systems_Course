 
#include "Mem_Map32.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include"TIMER_interface.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back functions in the application */
static volatile void (*g_Timer0_callBackPtr)(void) = NULLPTR;
static volatile void (*g_Timer1_callBackPtr)(void) = NULLPTR;
static volatile void (*g_Timer2_callBackPtr)(void) = NULLPTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

/************************************ Timer0 ************************************/

/*
 * Description :
 * Calls the call back function of timer 0 in case of OVERFLOW interrupt occurs
 */
ISR(TIMER0_OVF_vect)
{
	if(g_Timer0_callBackPtr != NULLPTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer0_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*
 * Description :
 * Calls the call back function of timer 0 in case of TIMER_CTC_Mode MATCH interrupt occurs
 */
ISR(TIMER0_COMP_vect)
{
	if(g_Timer0_callBackPtr != NULLPTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer0_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/************************************ Timer1 ************************************/

/*
 * Description :
 * Calls the call back function of timer 1 in case of OVERFLOW interrupt occurs
 */
ISR(TIMER1_OVF_vect)
{
	if(g_Timer1_callBackPtr != NULLPTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer1_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*
 * Description :
 * Calls the call back function of timer 1 in case of TIMER_CTC_Mode MATCH interrupt occurs
 */
ISR(TIMER1_COMPA_vect)
{
	if(g_Timer1_callBackPtr != NULLPTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer1_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/************************************ Timer2 ************************************/

/*
 * Description :
 * Calls the call back function of timer 2 in case of OVERFLOW interrupt occurs
 */
ISR(TIMER2_OVF_vect)
{
	if(g_Timer2_callBackPtr != NULLPTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer2_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*
 * Description :
 * Calls the call back function of timer 2 in case of TIMER_CTC_Mode MATCH interrupt occurs
 */
ISR(TIMER2_COMP_vect)
{
	if(g_Timer2_callBackPtr != NULLPTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer2_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function to Initialize the Timer by following predefined configurations
 * 		1. Choose which Timer to work with 							--> Timer0 / Timer1 / Timer2
 * 		2. Choose which mode to operate in 							--> Overflow Mode / Compare Mode
 * 		3. Choose which initial value to start the counting from
 * 		4. Choose the prescaler of the CPU clock to generate a clock for Timer to operate by
 * 		5. Choose Compare Value ((if)) the Timer operate in Compare Mode
 */
void Timer_init(const TIMER_ConfigType * Config_Ptr)
{
	/* Select which Timer depending on the configuration structure */
	switch(Config_Ptr->timer_ID)
	{
	/************************************ Timer0 ************************************/
	case TIMER0_ID:

		/*
		 * As we work in non-PWM Phase because we implement it in seperate driver
		 * Set Bit of Force Output Compare (FOC0) in Register (TCCR0)
		 * And we will use PWM Driver to generate waves
		 * Clear Bits Compare Match Output Mode (COM00, COM01)
		 */
		TCCR0 |= ( 1 << FOC0 );

		/*
		 * Configure Timer wave generation in the selected mode
		 * Insert it depending on the configuration
		 */
		TCCR0 = ( TCCR0 & 0xF7 ) | ( ( Config_Ptr->timer_mode ) << 3 );

		/*
		 * Put the required prescaler for the clock
		 * In the first three bits of Register (TCCR0)
		 */
		TCCR0 = ( TCCR0 & 0xF8 ) | ( Config_Ptr->timer_clock );

		/*
		 * Enable the Required Intterupt mode
		 * Depending on configuration
		 */
		TIMSK |= (1<<(Config_Ptr->timer_mode));

		/* Insert the required initial value in TCNT0 register */
		TCNT0 = (Config_Ptr->timer_intial_value);

		/*
		 * Enable the Required Interrupt Modes
		 * Insert data depending on configuration
		 */
		if ( Config_Ptr->timer_mode == TIMER_CTC_Mode )
		{
			/* Insert the required compare value in OCR0 register */
			OCR0 = Config_Ptr->timer_compare_value;
			/* Enable Compare Mode flag */
			TIMSK |= (1<<OCIE0);
		}
		else if ( Config_Ptr->timer_mode == TIMER_CTC_Mode )
		{
			/* Enable overflow Mode flag */
			TIMSK |= (1<<TOIE0);
		}

		break; /* End Timer0 */

	/************************************ Timer1 ************************************/
	case TIMER1_ID:

		/*
		 * Configure compare output mode to work with normal port operation [ OC1A/OC1B Disconnected ]
		 * 					Clear the last 4-Bits of (TCCR1A) Register to Clear ( COM1A0 / COM1A1 / COM1B0 /COM1B1 )
		 * As we work in non-PWM Phase because we implement it in seperate driver
		 * 					Set Bit of Force Output Compare (FOC1A / FOC1B) in Register (TCCR1A)
		 */
		TCCR1A = (1<<FOC1A) | (1<<FOC1B);

		/*
		 * Put the required prescaler for the clock
		 * In the first three bits of Register (TCCR1)
		 */
		TCCR1B = Config_Ptr->timer_clock;

		/*
		 * Configure Timer wave generation in the selected mode
		 * Insert it depending on the configuration
		 */
		TCCR1B = (TCCR1B & 0xF7) | ((Config_Ptr->timer_mode)<<WGM12);

		/* Insert the required initial value in TCNT1 register */
		TCNT1 = Config_Ptr->timer_intial_value;

		/*
		 * Enable the Required Interrupt Modes
		 * Insert data depending on configuration
		 */
		if ( Config_Ptr->timer_mode == TIMER_CTC_Mode )
		{
			/* Insert the required compare value in OCR1A register */
			OCR1A = Config_Ptr->timer_compare_value;
			/* Enable Compare Mode flag */
			TIMSK |= (1<<OCIE1A);
		}
		else if ( Config_Ptr->timer_mode == TIMER_CTC_Mode )
		{
			/* Enable overflow Mode flag */
			TIMSK |= (1<<TOIE1);
		}

		break; /* End Timer1 */

	/************************************ Timer2 ************************************/
	case TIMER2_ID:

		/*
		 * As we work in non-PWM Phase because we implement it in seperate driver
		 * Set Bit of Force Output Compare (FOC0) in Register (TCCR0)
		 * And we will use PWM Driver to generate waves
		 * Clear Bits Compare Match Output Mode (COM00, COM01)
		 */
		TCCR0 |= ( 1 << FOC2 );

		/*
		 * Configure Timer wave generation in the selected mode
		 * Insert it depending on the configuration
		 */
		TCCR2 = ( TCCR2 & 0xF7 ) | ( ( Config_Ptr->timer_mode ) << 3 );

		/*
		 * Put the required prescaler for the clock
		 * In the first three bits of Register (TCCR0)
		 */
		TCCR2 = ( TCCR2 & 0xF8 ) | ( Config_Ptr->timer_clock );

		/*
		 * Enable the Required Intterupt mode
		 * Depending on configuration
		 */
		TIMSK |= (1<<(Config_Ptr->timer_mode));

		/* Insert the required initial value in TCNT0 register */
		TCNT2 = (Config_Ptr->timer_intial_value);

		/*
		 * Enable the Required Interrupt Modes
		 * Insert data depending on configuration
		 */
		if ( Config_Ptr->timer_mode == TIMER_CTC_Mode )
		{
			/* Insert the required compare value in OCR0 register */
			OCR0 = Config_Ptr->timer_compare_value;
			/* Enable Compare Mode flag */
			TIMSK |= (1<<OCIE2);
		}
		else if ( Config_Ptr->timer_mode == TIMER_CTC_Mode )
		{
			/* Enable overflow Mode flag */
			TIMSK |= (1<<TOIE2);
		}

		break; /* End Timer2 */
	} /* End of the outer switch */
} /* End Timer_init Function */





/*
 * Description :
 * Function to set the Call Back Function Address
 */
void Timer_setCallBack(void(*a_ptr)(void), TIMER_ID timer_number)
{
	switch(timer_number)
	{
	/************************************ Timer0 ************************************/
	case TIMER0_ID:
		/* Save the address of the Call back function in a global variable */
		g_Timer0_callBackPtr = a_ptr;
		break;

	/************************************ Timer1 ************************************/
	case TIMER1_ID:
		/* Save the address of the Call back function in a global variable */
		g_Timer1_callBackPtr = a_ptr;
		break;

	/************************************ Timer2 ************************************/
	case TIMER2_ID:
		/* Save the address of the Call back function in a global variable */
		g_Timer2_callBackPtr = a_ptr;
		break;
	} /* End of switch case */
} /* End Timer_setCallBack Function */





/*
 * Description :
 * Function to stop the clock and DeInit the whole Timer
 */
void Timer_DeInit(TIMER_ID timer_number)
{
	switch(timer_number)
	{
	/***************************************** Timer0 *****************************************/
	case TIMER0_ID:
		/* Clear Registers in Timer0 */
		TCCR0 &= 0x00;
		TCNT0 &= 0x00;
		OCR0 &= 0x00;
		TIMSK &= ( 1 << OCIE0 ); /* Disable Output Compare Match Interrupt */
		TIMSK &= ( 1 << TOIE0 ); /* Disable Overflow Interrupt */
		break;

	/***************************************** Timer1 *****************************************/
	case TIMER1_ID:
		/* Clear Registers in Timer1 */
		TCCR1A &= 0x00;
		TCCR1B &= 0x00;
		TCNT1 &= 0x0000;
		OCR1A &= 0x0000;
		TIMSK &= ( 1 << OCIE1A ); /* Disable Output Compare Match Interrupt --> Channel A */
		TIMSK &= ( 1 << OCIE1B ); /* Disable Output Compare Match Interrupt --> Channel B */
		TIMSK &= ( 1 << TOIE1 ); /* Disable Overflow Interrupt */
		break;

	/***************************************** Timer2 *****************************************/
	case TIMER2_ID:
		/* Clear Registers in Timer2 */
		TCCR2 &= 0x00;
		TCNT2 &= 0x00;
		OCR2 &= 0x00;
		TIMSK &= ( 1 << OCIE2 ); /* Disable Output Compare Match Interrupt */
		TIMSK &= ( 1 << TOIE2 ); /* Disable Overflow Interrupt */
		break;
	} /* End of switch case */
} /* End Timer_DeInit Function */
