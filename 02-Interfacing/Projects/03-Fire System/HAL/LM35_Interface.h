/*
 * Sensors.h
 *
 * Created: 7/13/2022 1:01:24 PM
 *  Author: Osama
 */ 


#ifndef SENSORS_H_
#define SENSORS_H_

#include "ADC_Interface.h"


#define LM35_CHANNEL     ADC0
#define POT_CHANNEL      ADC2

u16 LM35_GetTemp(void);
u8 POT_GetPercentage(void);
#endif /* SENSORS_H_ */