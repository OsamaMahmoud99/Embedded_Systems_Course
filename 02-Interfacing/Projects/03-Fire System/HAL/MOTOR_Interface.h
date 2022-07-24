/*
 * Motor_Interface.h
 *
 * Created: 7/9/2022 2:27:14 PM
 *  Author: Osama
 */ 


#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_

/********************** Pin config *********************/

#define  IN1_M1   PIND6
#define  IN2_M1   PIND7

#define  IN1_M2   PINC3
#define  IN2_M2   PINC4
/*******************************************************/

typedef enum
{
	M1,
	M2,
	M3	
	}MOTOR_type;

void MOTOR_CW(MOTOR_type motor);
void MOTOR_CCW(MOTOR_type motor);
void MOTOR_Stop(MOTOR_type motor); 

#endif /* MOTOR_INTERFACE_H_ */