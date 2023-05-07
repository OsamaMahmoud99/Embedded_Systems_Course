/*
 * Motot_Program.c
 *
 * Created: 7/9/2022 2:26:53 PM
 *  Author: Osama
 */ 

#include "DIO_Interface.h"
#include "Motor_Interface.h"

void MOTOR_CW(MOTOR_type motor)
{
	switch(motor)
	{
		case M1:
		DIO_WritePin(IN1_M1 , HIGH);
		DIO_WritePin(IN2_M1 , LOW);
		break;
		case M2:
		DIO_WritePin(IN1_M2 , HIGH);
		DIO_WritePin(IN2_M2 , LOW);
	}
	
}
void MOTOR_CCW(MOTOR_type motor)
{
	switch(motor)
	{
		case M1:
		DIO_WritePin(IN1_M1 , LOW);
	    DIO_WritePin(IN2_M1 , HIGH);
		break;
		case M2:
		DIO_WritePin(IN1_M1 , LOW);
	    DIO_WritePin(IN2_M1 , HIGH);
		break;
	}

}
void MOTOR_Stop(MOTOR_type motor)
{
	switch(motor)
	{
		case M1:
		DIO_WritePin(IN1_M1 , LOW);
	    DIO_WritePin(IN2_M1 , LOW);
		break;
		case M2:
		DIO_WritePin(IN1_M2 , LOW);
	    DIO_WritePin(IN2_M2 , LOW);
		break;
	}
}