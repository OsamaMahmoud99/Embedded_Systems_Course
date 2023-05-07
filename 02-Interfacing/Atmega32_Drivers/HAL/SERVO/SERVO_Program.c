/*
 * SERVO_Program.c
 *
 * Created: 7/24/2022 10:31:47 AM
 *  Author: Osama
 */ 

#include "SERVO_Interface.h"

void SERVO_Init()
{
	/*set timer 1 prescaler to 8to get 1us tick time
	use fast mode with top value at OCRA reg to set the freq of servo
	disconnect OC1A PIN ,and generate the PWM on OC1B PIN with non inverting mode to use OCR1B reg as the ton value*/
	Timer1_Init(TIMER1_FASTPWM_OCRA_TOP_MODE , TIMER1_SCALER_8 , OCRA_DISCONNECTED, OCRB_NON_INVERTING);
	OCR1A=19999;//20000us to get 50hz
	OCR1B=999;// 2000us ton to get angle zero
}

void SERVO_SetAngle(u8 Angle)
{
	OCR1B = 999 + ((u32)1000*Angle)/180;
}
