/*
 * SSD.h
 *
 * Created: 3/10/2023 7:07:25 AM
 *  Author: osama
 */ 


#ifndef SSD_H_
#define SSD_H_


typedef enum{
	SSD_A_PIN_ID = PINA0,
	SSD_B_PIN_ID = PINA1,
	SSD_C_PIN_ID = PINA2,
	SSD_D_PIN_ID = PINA3,
	SSD_TENS_PIN_ID = PINA4,
	SSD_UNITS_PIN_ID = PINA5
}SSD_PIN_ID_t;

typedef enum{
	SSD_STATE_ON = LOW,
	SSD_STATE_OFF = HIGH
}SSD_STATE_t;

void SSD_Update(void);

#endif /* SSD_H_ */