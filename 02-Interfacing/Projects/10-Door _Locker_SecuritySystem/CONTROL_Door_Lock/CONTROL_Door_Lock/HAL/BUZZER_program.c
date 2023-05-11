/**
 * @file HBUZZER_program.c
 * @author Osama Mahmoud (you@domain.com)
 * @brief  this file contains the main logic to control the buzzer
 * @version 1.0
 * @date 2022-04-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/***********************************************************************************/
/*                                Includes                                         */
/***********************************************************************************/
#include "BUZZER_interface.h"


/***********************************************************************************/
/*                                Function Definitions                             */
/***********************************************************************************/
 
void Buzzer_On(void)
{
     /* set pin value to HIGH */
    DIO_WritePin(BUZZER_PINMAP[0].BUZZER_PIN ,HIGH);

    return;
}
      
  
void Buzzer_Off(void)
{
    /* set pin value to LOW */
    DIO_WritePin(BUZZER_PINMAP[0].BUZZER_PIN ,LOW);

    return;
}