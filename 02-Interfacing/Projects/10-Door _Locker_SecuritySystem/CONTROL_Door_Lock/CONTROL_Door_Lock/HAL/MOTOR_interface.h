/**
 * @file HMOTOR_interface.h
 * @author Osama Mahmoud (you@domain.com)
 * @brief  this file contains the interfacing information for MOTOR
 * @version 1.0
 * @date 2022-04-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/* file header guard */
#ifndef _MOTOR_INTERFACE_H_
#define _MOTOR_INTERFACE_H_

/***********************************************************************************/
/*                                Includes                                         */
/***********************************************************************************/
#include "Mem_Map32.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "PWM_interface.h"
#include "MOTOR_cfg.h"
#include "MOTOR_private.h"

/***********************************************************************************/
/*                                Interfacing Macros                               */
/***********************************************************************************/

/* Motor interfacing channels */
#define MOTOR_CHANNEL_1        (0)
#define MOTOR_CHANNEL_2        (1)

/* Motor directions */
#define MOTOR_MAIN_DIR         (1)
#define MOTOR_OTHER_DIR        (2)
#define MOTOR_STOP             (3)

/***********************************************************************************/
/*                                Interfacing Class                                */
/***********************************************************************************/


      
/**
 * @brief Construct a new hmotor Class object to configure the motor pin
 * 
 * @param au8_motorChannel 
*/
void InitMotor(void);
      
/**
  * @brief this function is used to ubdate motor with a specific seed(0 -> 0%, 255 -> 100%) and direction
  * 
  * @param au8_speed 
  * @param au8_direction 
  */
void UpdateMotor(u8 au8_speed , u8 au8_direction);

   

#endif /*_MOTOR_INTERFACE_H_*/