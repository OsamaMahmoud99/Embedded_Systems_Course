/**
 * @file HBUZZER_interface.h
 * @author Osama Mahmoud (you@domain.com)
 * @brief  this file contains the interfacing information for buzzer
 * @version 1.0
 * @date 2022-04-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/* file header guard */
#ifndef _BUZZER_INTERFACE_H_
#define _BUZZER_INTERFACE_H_

/***********************************************************************************/
/*                                Includes                                         */
/***********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "BUZZER_cfg.h"
#include "BUZZER_private.h"



/***********************************************************************************/
/*                                Interfacing function                             */
/***********************************************************************************/

 
 /**
   * @brief this function is used to turn on the buzzer
   * 
 */
void Buzzer_On(void);

 /**
   * @brief this function is used to turn off the buzzer
   * 
 */
void Buzzer_Off(void);      
     

#endif /*_BUZZER_INTERFACE_H_*/