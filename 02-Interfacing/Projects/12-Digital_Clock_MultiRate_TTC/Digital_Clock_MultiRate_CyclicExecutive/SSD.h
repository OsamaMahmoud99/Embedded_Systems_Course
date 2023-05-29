/*
 * SSD.h
 *
 * Created: 3/10/2023 7:07:25 AM
 *  Author: osama
 */ 


#ifndef SSD_H_
#define SSD_H_

#include "MemMap.h"
#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"

typedef enum{
	SSD_A_PIN_ID = PINC0,
	SSD_B_PIN_ID = PINC1,
	SSD_C_PIN_ID = PINC2,
	SSD_D_PIN_ID = PINC3,
	SSD_HOURS_TENS_PIN_ID = PIND0,
	SSD_HOURS_UNITS_PIN_ID = PIND1,
	SSD_MIN_TENS_PIN_ID = PIND2,
	SSD_MIN_UNITS_PIN_ID = PIND3,
	SSD_SEC_TENS_PIN_ID = PIND4,
	SSD_SEC_UNITS_PIN_ID = PIND6

}SSD_PIN_ID_t;

typedef enum{
	SSD_HOURS_TENS= 0,
	SSD_HOURS_UNITS,
	SSD_MIN_TENS,
	SSD_MIN_UNITS,
	SSD_SEC_TENS,
	SSD_SEC_UNITS

}SSD_t;

typedef enum{
	SSD_STATE_ON = 0,
	SSD_STATE_OFF = 1
}SSD_STATE_t;

typedef enum{
        SSD_NORMAL_MODE = 0,
        SSD_SETTING_HOURS_MODE,
        SSD_SETTING_MINUTES_MODE
}SSD_MODE_t;

void SSD_Update(void);

#endif /* SSD_H_ */
