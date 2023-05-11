/**
 * @file HMOTOR_private.h
 * @author Osama Mahmoud (you@domain.com)
 * @brief  this file contains the Motor struct include PWM pin  and Directio pin
 * @version 1.0
 * @date 2022-04-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*file header guard*/
#ifndef _MOTOR_PRIVATE_H_
#define _MOTOR_PRIVATE_H_


/**************************************************************************************/
/*                                MOTOR Struct                                        */
/**************************************************************************************/

typedef struct 
{   
    u8 MOTOR_PWM_Channel;
    u8 MOTOR_PWM_PIN;
    u8 MOTOR_DIR_IN1;
    u8 MOTOR_DIR_IN2;

}MOTOR_PinMap;

extern MOTOR_PinMap       MOTOR_PINMAP[MOTOR_Number];


#endif /* _MOTOR_PRIVATE_H_ */