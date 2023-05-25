/*
 * LED.h
 *
 * Created: 3/10/2023 7:24:30 AM
 *  Author: osama
 */ 


#ifndef LED_H_
#define LED_H_

typedef enum{
	LED_STATE_OFF = LOW,
	LED_STATE_ON = HIGH
}LED_STATE_t;

typedef enum{
	LED_RED_PIN_ID = PINB0,
	LED_YELLOW_PIN_ID = PINB1,
	LED_GREEN_PIN_ID = PINB2
}LED_PIN_ID_t;

typedef enum{
	LED_RED = 0,
	LED_YELLOW,
	LED_GREEN
}LED_t;

void LED_Update(void);

#endif /* LED_H_ */