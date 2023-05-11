/**
 * @file HBUZZER_private.h
 * @author Osama Mahmoud (you@domain.com)
 * @brief  this file contains the buzzer struct include (PORT , PIN)
 * @version 1.0
 * @date 2022-04-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*file header guard*/
#ifndef _BUZZER_PRIVATE_H_
#define _BUZZER_PRIVATE_H_


/**************************************************************************************/
/*                                BUZZER Struct                                       */
/**************************************************************************************/

typedef struct 
{
    u8 BUZZER_PIN;
	
}BUZZER_PinMap;

extern BUZZER_PinMap       BUZZER_PINMAP[BUZZER_Number];



#endif /*_BUZZER_PRIVATE_H_*/