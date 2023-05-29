/*
 * SW.c
 *
 *  Created on: May 27, 2023
 *      Author: Osama
 */

#include "SW.h"

SW_t SW_g[SW_MAX_NUMBER] = {  {PINA0 , SW_PRE_PRESSED , SW_RELEASED , SW_INTERNAL_PULLUP},
		                      {PINA1 , SW_PRE_PRESSED , SW_RELEASED , SW_INTERNAL_PULLUP},
							  {PINA2 , SW_PRE_PRESSED , SW_RELEASED , SW_INTERNAL_PULLUP}
};

static void Read(SW_t * const SW)
{
	switch(SW->time){

	case SW_PRE_PRESSED:
		switch(SW->connection){
		case SW_INTERNAL_PULLUP:
			SW->state = SW_RELEASED;
			if(HIGH == DIO_ReadPin(SW->pin)){
				SW->time = SW_PRE_RELEASED;
			}
			break;
		case SW_EXTERNAL_PULLDOWN:
			SW->state = SW_RELEASED;
			if(LOW == DIO_ReadPin(SW->pin)){
				SW->time = SW_PRE_RELEASED;
			}
			break;
		}
		break;
	case SW_PRE_RELEASED:
		switch(SW->connection){
		case SW_INTERNAL_PULLUP:
			if(LOW == DIO_ReadPin(SW->pin)){
				SW->state = SW_PRESSED;
				SW->time = SW_PRE_PRESSED;
			}
			break;
		case SW_EXTERNAL_PULLDOWN:
			if(HIGH == DIO_ReadPin(SW->pin)){
				SW->state = SW_PRESSED;
				SW->time = SW_PRE_RELEASED;
			}
			break;
		}
		break;
	default:
			break;
	}
}

void SW_Update(void)
{
	SW_ID_t id;

	for(id = SW_SETTING; id<SW_MAX_NUMBER; ++id)
	{
		Read(SW_g+id);
	}
}
