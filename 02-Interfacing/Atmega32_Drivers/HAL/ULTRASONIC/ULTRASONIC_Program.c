/*
 * ULTRASONIC_Program.c
 *
 * Created: 7/25/2022 6:22:50 AM
 *  Author: Osama
 */ 


#include "ULTRASONIC_Interface.h"
#include "LCD_Interface.h"
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
void ULTRASONIC_Init(void)
{
	//Timer1_Init(TIMER1_NORMAL_MODE , TIMER1_SCALER_8 , OCRA_DISCONNECTED , OCRB_DISCONNECTED);
	//Timer1_Init(TIMER1_FASTPWM_OCRA_TOP_MODE , TIMER1_SCALER_8 , OCRA_DISCONNECTED, OCRB_NON_INVERTING);
	Timer1_ICU_SetCallBack(Func_ICU);
	Timer1_OVF_SetCallBack(Func_OVF);
}

//u16 ULTRASONIC_GetDistance(Ultrasonic_t UltraNumber)
//{
	//u16 Distance ;
	//u16 time;
	//c = 0;
	//DIO_WritePin(UltraNumber , HIGH);
	//_delay_us(10);
	//DIO_WritePin(UltraNumber , LOW);
	//Timer1_InputCaptureEdge(RISING);
	//Timer1_ICU_InterruptEnable();
	//while(flag<2);
	//time = t2-t1 +((u32)c*65535);
	////LCD_GoTo(0 , 0);
	////LCD_WriteNumber_3D(t2);
	////LCD_GoTo(0 , 4);
	////LCD_WriteNumber_3D(t1);
//
	//Distance = time/58;
	//flag = 0;
	//Timer1_ICU_InterruptDisable();
	//return Distance;
//}
u8 ULTRASONIC_GetDistance2(Ultrasonic_t UltraNumber)
{
	u8 distance;
	u16 time;
	DIO_WritePin(UltraNumber,HIGH);
	_delay_us(10);
	DIO_WritePin(UltraNumber,LOW);
	while (!DIO_ReadPin(PIND6));
	Timer1_WriteToTCNT1(0);
	while (DIO_ReadPin(PIND6));
	time = Timer1_ReadTCNT1();
	distance=time/58;
	return distance;
}

/*u8 ULTRASONIC_GetDistance3(Ultrasonic_t UltraNumber)
{
	u8 distance;
	u16 time;
	c=0;
	DIO_WritePin(UltraNumber,HIGH);
	_delay_us(10);
	DIO_WritePin(UltraNumber,LOW);
	while (!DIO_ReadPin(PIND6));
	while (DIO_ReadPin(PIND6)){
		c++;
		//_delay_us(0.5);
	}
	distance=c/58;
	return distance;
}
*/
void ULTRASONIC_GetTrigger(Ultrasonic_t UltraNumber)
{
	//Timer1_WriteToTCNT1(0);
	 if (flag == 0)
	 {
		c = 0;
		DIO_WritePin(UltraNumber , HIGH);
		_delay_us(10);
		DIO_WritePin(UltraNumber , LOW);
		Timer1_InputCaptureEdge(RISING);
		Timer1_ICU_InterruptEnable();
	 }

}

bool_t ULTRASONIC_GetDistance_PeridicCheck(u16*PDistance)
{
	bool_t status = FALSE;
	u16 time , Distance;
	if (flag == 2)
	{
		time = t2 - t1+((u32)c*65535);
		Distance = time / 58;
		*PDistance = Distance;
		Timer1_OVF_InterruptEnable();
		flag = 0;
		status = TRUE;
	}
	else
	{
		status = FALSE;
	}
	
	return status;
}
