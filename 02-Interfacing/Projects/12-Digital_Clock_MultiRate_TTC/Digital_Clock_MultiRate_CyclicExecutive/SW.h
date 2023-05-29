/*
 * SW.h
 *
 *  Created on: May 27, 2023
 *      Author: Osama
 */

#ifndef SW_H_
#define SW_H_

#include "DIO_Interface.h"

typedef enum{
	SW_PRESSED = 0,
	SW_RELEASED
}SW_STATE_t;

typedef enum{
	SW_PRE_PRESSED = 0,
	SW_PRE_RELEASED
}SW_TIME_t;

typedef enum{
	SW_EXTERNAL_PULLUP = 0,
	SW_EXTERNAL_PULLDOWN,
	SW_INTERNAL_PULLUP
}SW_CONNECTION_t;

typedef enum{
	SW_SETTING = 0,
	SW_UP,
	SW_DOWN,
	SW_MAX_NUMBER
}SW_ID_t;

typedef struct{
	DIO_Pin_type pin : 6;
	SW_TIME_t time : 1;
	SW_STATE_t state : 1;
	SW_CONNECTION_t connection : 2;
}SW_t;


extern SW_t SW_g[SW_MAX_NUMBER];

void SW_Update(void);


#endif /* SW_H_ */
