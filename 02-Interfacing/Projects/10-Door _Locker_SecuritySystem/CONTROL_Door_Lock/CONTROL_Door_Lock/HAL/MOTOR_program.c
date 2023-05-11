/**
 * @file HMOTOR_program.c
 * @author Osama Mahmoud (you@domain.com)
 * @brief  this file contains the main logic to control the MOTOR
 * @version 1.0
 * @date 2022-04-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/***********************************************************************************/
/*                                Includes                                         */
/***********************************************************************************/
#include "MOTOR_interface.h"


/**************************************************************************************/
/*                                Important Macros                                    */
/**************************************************************************************/

#define NO_DUTY_CYCLE            (0)


/***********************************************************************************/
/*                                Function Definitions                             */
/***********************************************************************************/


void InitMotor(void)
{
	InitPWM(MOTOR_PINMAP[0].MOTOR_PWM_Channel);
	updatepwm(MOTOR_PINMAP[0].MOTOR_PWM_Channel , PWM_2KHZ , NO_DUTY_CYCLE);
}

void UpdateMotor(u8 au8_speed , u8 au8_direction)
{
    
             switch(au8_direction)
             {
                 case MOTOR_MAIN_DIR:
                      /* Motor 1 main direction */
                      DIO_WritePin(MOTOR_PINMAP[0].MOTOR_DIR_IN1 ,  HIGH);
                      DIO_WritePin(MOTOR_PINMAP[0].MOTOR_DIR_IN2 , LOW);
                      break;

                case MOTOR_OTHER_DIR:
                     /* Motor 1 other direction */
                     DIO_WritePin(MOTOR_PINMAP[0].MOTOR_DIR_IN1 ,  LOW);
                     DIO_WritePin(MOTOR_PINMAP[0].MOTOR_DIR_IN2 , HIGH);
                     break;

                case MOTOR_STOP:
                     /* Motor 1 Stop */
                     DIO_WritePin(MOTOR_PINMAP[0].MOTOR_DIR_IN1 ,  LOW);
                     DIO_WritePin(MOTOR_PINMAP[0].MOTOR_DIR_IN2 , LOW);
                     break;

                default:
                     
                     break;
             }
             /* setting pwm for motor1 with freq=2KHZ and speed=au8_speed */ 
             updatepwm(MOTOR_PINMAP[0].MOTOR_PWM_Channel , PWM_2KHZ , au8_speed);
}