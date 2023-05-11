/**
 * @file MPWM_private.h
 * @author Osama Mahmoud (you@domain.com)
 * @brief This file contains the address of PWM registers
 * @version 1.0
 * @date 2022-04-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _MPWM_PRIVATE_H
#define _MPWM_PRIVATE_H


/***********************************************************************************/
/*                                PWM Registers                                    */
/***********************************************************************************/

/* Timer1 Registers */
#define MPWM_TCCR1         (*(volatile u16*)(0x4E))
#define MPWM_TCNT1         (*(volatile u16*)(0x4C))
#define MPWM_OCR1A         (*(volatile u16*)(0x4A))
#define MPWM_OCR1B         (*(volatile u16*)(0x48))

/* Timer2 Registers */
#define MPWM_TCCR2         (*(volatile u8*)(0x45))
#define MPWM_TCNT2         (*(volatile u8*)(0x44))
#define MPWM_OCR2          (*(volatile u8*)(0x43))





#endif /* _MPWM_PRIVATE_H */