/*
 * STEPPER_Programc.c
 *
 * Created: 7/12/2022 4:23:37 PM
 *  Author: Osama
 */ 

#include "STEPPER_Interfaceh.h"
#define F_CPU              8000000
#include <util/delay.h>

void STEPPER_Bibolar_CW(void)
{

	DIO_WritePin(COIL1A , LOW);
	DIO_WritePin(COIL1B , LOW);
	DIO_WritePin(COIL2A , HIGH);
	DIO_WritePin(COIL2B , LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A , LOW);
	DIO_WritePin(COIL1B , HIGH);
	DIO_WritePin(COIL2A , LOW);
	DIO_WritePin(COIL2B , LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A , LOW);
	DIO_WritePin(COIL1B , LOW);
	DIO_WritePin(COIL2A , LOW);
	DIO_WritePin(COIL2B , HIGH);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A , HIGH);
	DIO_WritePin(COIL1B , LOW);
	DIO_WritePin(COIL2A , LOW);
	DIO_WritePin(COIL2B , LOW);
	_delay_ms(DELAY);
}

void STEPPER_Bibolar_CCW(void)
{
		
	DIO_WritePin(COIL1A , LOW);
	DIO_WritePin(COIL1B , LOW);
	DIO_WritePin(COIL2A , LOW);
	DIO_WritePin(COIL2B , HIGH);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A , LOW);
	DIO_WritePin(COIL1B , HIGH);
	DIO_WritePin(COIL2A , LOW);
	DIO_WritePin(COIL2B , LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A , LOW);
	DIO_WritePin(COIL1B , LOW);
	DIO_WritePin(COIL2A , HIGH);
	DIO_WritePin(COIL2B , LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A , HIGH);
	DIO_WritePin(COIL1B , LOW);
	DIO_WritePin(COIL2A , LOW);
	DIO_WritePin(COIL2B , LOW);
	_delay_ms(DELAY);
			
}

void STEPPER_Unibolar_CW(void)
{
	DIO_WritePin(COIL1A , LOW);
	DIO_WritePin(COIL1B , HIGH);
	DIO_WritePin(COIL2A , LOW);
	DIO_WritePin(COIL2B , LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A , LOW);
	DIO_WritePin(COIL1B , LOW);
	DIO_WritePin(COIL2A , HIGH);
	DIO_WritePin(COIL2B , LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A , LOW);
	DIO_WritePin(COIL1B , LOW);
	DIO_WritePin(COIL2A , LOW);
	DIO_WritePin(COIL2B , HIGH);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A , HIGH);
	DIO_WritePin(COIL1B , LOW);
	DIO_WritePin(COIL2A , LOW);
	DIO_WritePin(COIL2B , LOW);
	_delay_ms(DELAY);
}
void STEPPER_Unibolar_CCW(void)
{
		
	DIO_WritePin(COIL1A , HIGH);
	DIO_WritePin(COIL1B , LOW);
	DIO_WritePin(COIL2A , LOW);
	DIO_WritePin(COIL2B , LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A , LOW);
	DIO_WritePin(COIL1B , LOW);
	DIO_WritePin(COIL2A , LOW);
	DIO_WritePin(COIL2B , HIGH);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A , LOW);
	DIO_WritePin(COIL1B , LOW);
	DIO_WritePin(COIL2A , HIGH);
	DIO_WritePin(COIL2B , LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A , LOW);
	DIO_WritePin(COIL1B , HIGH);
	DIO_WritePin(COIL2A , LOW);
	DIO_WritePin(COIL2B , LOW);
	_delay_ms(DELAY);

}

void STEPPER_Unibolar_HS_CW(void)
{
	DIO_WritePin(COIL1A , LOW);
	DIO_WritePin(COIL1B , HIGH);
	DIO_WritePin(COIL2A , LOW);
	DIO_WritePin(COIL2B , LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A , LOW);
	DIO_WritePin(COIL1B , HIGH);
	DIO_WritePin(COIL2A , HIGH);
	DIO_WritePin(COIL2B , LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A , LOW);
	DIO_WritePin(COIL1B , LOW);
	DIO_WritePin(COIL2A , HIGH);
	DIO_WritePin(COIL2B , LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A , LOW);
	DIO_WritePin(COIL1B , LOW);
	DIO_WritePin(COIL2A , HIGH);
	DIO_WritePin(COIL2B , HIGH);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A , LOW);
	DIO_WritePin(COIL1B , LOW);
	DIO_WritePin(COIL2A , LOW);
	DIO_WritePin(COIL2B , HIGH);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A , HIGH);
	DIO_WritePin(COIL1B , LOW);
	DIO_WritePin(COIL2A , LOW);
	DIO_WritePin(COIL2B , HIGH);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A , HIGH);
	DIO_WritePin(COIL1B , LOW);
	DIO_WritePin(COIL2A , LOW);
	DIO_WritePin(COIL2B , LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A , HIGH);
	DIO_WritePin(COIL1B , HIGH);
	DIO_WritePin(COIL2A , LOW);
	DIO_WritePin(COIL2B , LOW);
	_delay_ms(DELAY);
}
void STEPPER_Unibolar_HS_CCW(void)
{
	
}