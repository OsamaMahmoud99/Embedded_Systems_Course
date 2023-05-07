/*
 * EXTI_Program.c
 *
 * Created: 7/20/2022 12:30:22 PM
 *  Author: Osama
 */ 

#include "EXTI_Interface.h"

/****************************Pointer to functions to be assigned to ISR*********************************/

static void (*INT0_Fptr) (void)=NULLPTR;
static void (*INT1_Fptr) (void)=NULLPTR;
static void (*INT2_Fptr) (void)=NULLPTR;

/************************************Call back functions*********************************************/
void EXI_SetCallBack(ExInterruptSource_type Interrupt,void(*LocalPtr)(void))
{
	switch(Interrupt){
		case EX_INT0:
		INT0_Fptr=LocalPtr;
		break;
		case EX_INT1:
		INT1_Fptr=LocalPtr;
		break;
		case EX_INT2:
		INT2_Fptr=LocalPtr;
		break;
	}
}
/************************************Enable/Disable functions***********************************/
void EXI_Enable(ExInterruptSource_type Interrupt)
{
	switch(Interrupt){
		case EX_INT0:
		SET_BIT(GICR,INT0);
		break;
		case EX_INT1:
		SET_BIT(GICR,INT1);
		break;
		case EX_INT2:
		SET_BIT(GICR,INT2);
		break;
	}
}

void EXI_Disable(ExInterruptSource_type Interrupt)
{
	switch(Interrupt){
		case EX_INT0:
		CLR_BIT(GICR,INT0);
		break;
		case EX_INT1:
		CLR_BIT(GICR,INT1);
		break;
		case EX_INT2:
		CLR_BIT(GICR,INT2);
		break;
	}
}
/************************************Control function*****************************/
void EXI_TriggerEdge(ExInterruptSource_type Interrupt,TriggerEdge_type Edge)
{
	switch(Interrupt){
		case EX_INT0:
		switch(Edge){
			case LOW_LEVEL:
			CLR_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
			break;
			case ANY_LOGIC_CHANGE:
			SET_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
			break;
			case FALLING_EDGE:
			CLR_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
			
		}
		break;
		case EX_INT1:
		switch(Edge){
			case LOW_LEVEL:
			CLR_BIT(MCUCR,ISC10);
			CLR_BIT(MCUCR,ISC11);
			break;
			case ANY_LOGIC_CHANGE:
			SET_BIT(MCUCR,ISC10);
			CLR_BIT(MCUCR,ISC11);
			break;
			case FALLING_EDGE:
			CLR_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
			
		}
		break;
		case EX_INT2:
		switch(Edge){
			case FALLING_EDGE:
			CLR_BIT(MCUCSR,ISC2);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCSR,ISC2);
			break;
			default:
			CLR_BIT(MCUCSR,ISC2);
		}
		break;
	}
}
/*******************************ISR********************************/
ISR(INT0_vect)
{
	if (INT0_Fptr!=NULLPTR)
	{
		INT0_Fptr();
	}
}
ISR(INT1_vect)
{
	if (INT1_Fptr!=NULLPTR)
	{
		INT1_Fptr();
	}
}
ISR(INT2_vect)
{
	if (INT2_Fptr!=NULLPTR)
	{
		INT2_Fptr();
	}
}

