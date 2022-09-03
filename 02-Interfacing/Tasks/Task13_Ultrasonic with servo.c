 /*
 * AVR.c
 *
 * Created: 7/4/2022 1:58:41 PM
 * Author : Osama
 */ 


#define  F_CPU    8000000
#include <util/delay.h>

#include "MemMap.h"
#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "TIMER_Interface.h"
#include "ULTRASONIC_Interface.h"
#include "SERVO_Interface.h"

static volatile u8 flag = 0;
static volatile u16 t1 , t2 , c=0;

static void Func_ICU(void)
{
	if (flag == 0)
	{
		c = 0;
		t1 = ICR1;
		Timer1_InputCaptureEdge(FALLING);
		flag = 1;
	}
	else if (flag == 1)
	{
		t2 = ICR1;
		Timer1_ICU_InterruptDisable();
		Timer1_OVF_InterruptDisable();
		flag = 2;
	}
}
static void Func_OVF(void)
{
	c++;
}

u8 ULTRASONIC_GetDistance(Ultrasonic_t UltraNumber)
{
	u16 Distance ;
	u32 time;
	c = 0;
	DIO_WritePin(UltraNumber , HIGH);
	_delay_us(10);
	DIO_WritePin(UltraNumber , LOW);
	Timer1_InputCaptureEdge(RISING);
	Timer1_ICU_InterruptEnable();
	while(flag<2);
	time = (t2+((u32)c*20000))-t1;

	Distance = time/58;
	flag = 0;
	Timer1_ICU_InterruptDisable();
	return Distance;
}
int main(void)
{
	sei();
	DIO_Init();
	LCD_Init();
	
	Timer1_Init(TIMER1_FASTPWM_OCRA_TOP_MODE , TIMER1_SCALER_8 , OCRA_DISCONNECTED, OCRB_NON_INVERTING);
	Timer1_ICU_SetCallBack(Func_ICU);
	Timer1_OVF_SetCallBack(Func_OVF);
	
	OCR1A=19999;//20000us to get 50hz
	OCR1B=999;// 2000us ton to get angle zero*/
	

	
	u8 Distance;

	while(1)
	{
		Distance = ULTRASONIC_GetDistance(ULTRASONIC1);
		if (Distance > 151)
		{
			SERVO_SetAngle(90);
		}
		LCD_GoTo(0 , 0);
		LCD_WriteNumber(Distance);
	
			
	}
		
	return 0;
}


