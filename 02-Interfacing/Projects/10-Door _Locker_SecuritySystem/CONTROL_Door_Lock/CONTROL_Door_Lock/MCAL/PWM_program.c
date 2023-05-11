/**
 * @file MPWM_program.cpp
 * @author Osama Mahmoud (you@domain.com)
 * @brief  This file contains the main logic of pwm module
 * @version 1.0
 * @date 2022-04-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */


/***********************************************************************************/
/*                                Includes                                         */
/***********************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "PWM_private.h"
#include "PWM_interface.h"

/**************************************************************************************/
/*                                Important macros                                    */
/**************************************************************************************/

#define TIMER1_CH1_CMP_RESET                         (0x3FFF)
#define TIMER1_CH2_CMP_RESET                         (0xCFFF)
#define TIMER1_CH1_PHASE_CORRECT_NON_INV_MODE_2KHZ   (0x8102)
#define TIMER1_CH2_PHASE_CORRECT_NON_INV_MODE_2KHZ   (0x2102)     
#define TIMER2_PHASE_CORRECT_NON_INV_MODE_2KHZ       (0x62)    
#define TIMER1_RESET_CLK_BITS                        (0xFFF8)
#define TIMER2_RESET_CLK_BITS                        (0xF8)


/***********************************************************************************/
/*                                Function Definitions                             */
/***********************************************************************************/

void InitPWM(u8 au8_channel)
{
    
    switch(au8_channel)
    {
        case PWM_CHANNEL_1:
             
             /*  Normal port operation, OC1A/OC1B disconnected */
             MPWM_TCCR1 &= TIMER1_CH1_CMP_RESET;
            
             /* Enable phase correct and non inverting mode with 2KHZ */
             MPWM_TCCR1 |= TIMER1_CH1_PHASE_CORRECT_NON_INV_MODE_2KHZ;
            
             /* Set the duty cycle 0% */
             MPWM_OCR1A = 0;

             break;
        
        case PWM_CHANNEL_2:
             
             /*  Normal port operation, OC1A/OC1B disconnected */
             MPWM_TCCR1 &= TIMER1_CH2_CMP_RESET;
            
             /* Enable phase correct and non inverting mode with 2KHZ */
             MPWM_TCCR1 |= TIMER1_CH2_PHASE_CORRECT_NON_INV_MODE_2KHZ;
            
             /* Set the duty cycle 0% */
             MPWM_OCR1B = 0;

             break;
             
        case PWM_CHANNEL_3:
             
             /* Enable phase correct and non inverting mode with 2KHZ */
             MPWM_TCCR2 |= TIMER2_PHASE_CORRECT_NON_INV_MODE_2KHZ;

             /* Set the duty cycle 0% */
             MPWM_OCR2 = 0;

             break;

        default:
             
             break;

    }

}

void updatepwm(u8 au8_channel , u8 au8_frequency, u8 au8_dutycycle)
{
    switch(au8_channel)
    {
        case PWM_CHANNEL_1:
             
             /* Reset the CLK Bits */
             MPWM_TCCR1 &= TIMER1_RESET_CLK_BITS;
             
             /* setting the new frequency */
             MPWM_TCCR1 |= au8_frequency;
             
             /* setting the new duty cycle */
             MPWM_OCR1A = au8_dutycycle;

             break;

        case PWM_CHANNEL_2:
             
               
             /* Reset the CLK Bits */
             MPWM_TCCR1 &= TIMER1_RESET_CLK_BITS;
             
             /* setting the new frequency */
             MPWM_TCCR1 |= au8_frequency;
             
             /* setting the new duty cycle */
             MPWM_OCR1B = au8_dutycycle;

             break;

        case PWM_CHANNEL_3:
             
               
             /* Reset the CLK Bits */
             MPWM_TCCR2 &= TIMER2_RESET_CLK_BITS;
             
             /* setting the new frequency */
             MPWM_TCCR2 |= au8_frequency;
             
             /* setting the new duty cycle */
             MPWM_OCR2 = au8_dutycycle;

             break;

    }

}