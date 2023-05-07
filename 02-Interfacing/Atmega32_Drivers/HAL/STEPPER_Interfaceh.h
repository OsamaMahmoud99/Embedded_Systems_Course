/*
 * STEPPER_Interfaceh.h
 *
 * Created: 7/12/2022 4:24:03 PM
 *  Author: asss5
 */ 


#ifndef STEPPER_INTERFACEH_H_
#define STEPPER_INTERFACEH_H_

#include "DIO_Interface.h"

#define COIL1A      PIND0  
#define COIL1B      PIND1
#define COIL2A      PIND2
#define COIL2B      PIND3

#define DELAY       500

void STEPPER_Bibolar_CW(void);
void STEPPER_Bibolar_CCW(void);
void STEPPER_Unibolar_CW(void);
void STEPPER_Unibolar_CCW(void);
void STEPPER_Unibolar_HS_CW(void);
void STEPPER_Unibolar_HS_CCW(void);


#endif /* STEPPER_INTERFACEH_H_ */