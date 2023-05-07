/*
 * Timer_Service.c
 *
 * Created: 7/24/2022 3:02:10 PM
 *  Author: Osama
 */ 

#include "Timer_Service.h"


static volatile u8 flag = 0;
static volatile u16 t1 , t2 ,t3 ,c=0;

void PWM_Init(void)
{
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE , TIMER1_SCALER_8 , OCRA_NON_INVERTING , OCRB_DISCONNECTED);
}

void PWM_Freq_KHZ(u16 freq)
{
	u16 ttotal;
	
	if(freq == 0);
	else
	{
		ttotal = 1000 / freq;       // (10^6*(1/freq*10^3)) us
		if (ttotal >= 1)
		{
			ICR1 = ttotal - 1;
		}
		else{
			ICR1 = 0;
		}	
	}
}

void PWM_Freq_HZ(u16 freq)
{
	u16 ttotal;
	
	if(freq == 0);
	else
	{
		ttotal = (u32)1000000 / freq;       // (10^6*(1/freq)) us
		if (ttotal >= 1)
		{
			ICR1 = ttotal - 1;
		}
		else
		{
			ICR1 = 0;
		}	
	}
}

void PWM_Duty(u16 duty)
{
	if (duty <= 100)
	{
		u16 ton = ((u32)duty * (ICR1+1))/100;
		if (ton > 1)
		{
			OCR1A = ton - 1;
		}
		else
		{
			OCR1A = 0;
		}
	}
}

static void Func_ICU(void)
{
	if (flag == 0)
	{
		t1 = ICR1;
		Timer1_InputCaptureEdge(FALLING);
		flag = 1;
	}
	else if (flag == 1)
	{
		t2 = ICR1;
		Timer1_InputCaptureEdge(RISING);
		flag = 2;
	}
	else if (flag == 2)
	{
		t3 = ICR1;
		Timer1_ICU_InterruptDisable();
		flag = 3;
	}
}

static void Func_OVF(void)
{
	c++;
}

void PWM_Measure(u32* Pfreq,u8* Pduty)
{ 
	u16 ton , toff;
	c=0;
	Timer1_ICU_SetCallBack(Func_ICU);
	Timer1_OVF_SetCallBack(Func_OVF);
	Timer1_InputCaptureEdge(RISING);
	Timer1_ICU_InterruptEnable();
	Timer1_OVF_InterruptEnable();
	flag = 0;
	while(flag<3);
	ton = t2 - t1 + ((u32)c*65535);
	toff = t3 - t2 + ((u32)c*65535);
	
	*Pfreq = ((u32)1000000 / ((u32)ton + toff));
	*Pduty = ((u32)ton*100)/((u32)ton + toff);
}


void Timer1_SetInterruptTime_ms (u16 time,void(*LocalFptr)(void))
{
	if (time >= 1 && time <= 65)
	{
		Timer1_Init(TIMER1_CTC_OCRA_TOP_MODE , TIMER1_SCALER_8 , OCRA_DISCONNECTED , OCRB_DISCONNECTED);
		OCR1A = (time*1000)-1;   // time range 0 - 65ms
	}
	else
	{
		Timer1_Init(TIMER1_CTC_OCRA_TOP_MODE , TIMER1_SCALER_1024 , OCRA_DISCONNECTED , OCRB_DISCONNECTED);
		OCR1A = (((u32)time*1000)/128)-1;  
	}

	Timer1_OCA_SetCallBack(LocalFptr);
	Timer1_OCA_InterruptEnable();
}
void Timer1_SetInterruptTime_us (u16 time,void(*LocalFptr)(void))
{
	Timer1_Init(TIMER1_CTC_OCRA_TOP_MODE , TIMER1_SCALER_8 , OCRA_DISCONNECTED , OCRB_DISCONNECTED);
	OCR1A = (time)-1;
	Timer1_OCA_SetCallBack(LocalFptr);
	Timer1_OCA_InterruptEnable();
}