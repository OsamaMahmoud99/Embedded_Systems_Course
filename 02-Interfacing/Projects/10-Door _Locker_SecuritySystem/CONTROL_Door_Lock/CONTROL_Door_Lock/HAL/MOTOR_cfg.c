/**
 * @file HMOTOR_cfg.c
 * @author Osama Mahmoud (you@domain.com)
 * @brief  this file contains the pin configuration of MOTOR
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
/*                                MOTOR configurations                                */
/**************************************************************************************/

MOTOR_PinMap       MOTOR_PINMAP[MOTOR_Number] = 
{
            {PWM_CHANNEL_3 , PIND7 , PINB0 , PINB1}         // Channel1 
};