/*
 * Timer_Service.h
 *
 * Created: 7/24/2022 3:01:34 PM
 *  Author: Osama
 */ 


#ifndef TIMER_SERVICE_H_
#define TIMER_SERVICE_H_

#include "TIMER_Interface.h"

void PWM_Init(void);
void PWM_Freq_KHZ(u16 freq);
void PWM_Freq_HZ(u16 freq);
void PWM_Duty(u16 duty);

void Timer1_SetInterruptTime_ms (u16 time,void(*LocalFptr)(void));
void Timer1_SetInterruptTime_us (u16 time,void(*LocalFptr)(void));

void PWM_Measure(u32* Pfreq,u8* Pduty);
void PWM_Measure2(u32* Pfreq,u8* Pduty);


#endif /* TIMER_SERVICE_H_ */
