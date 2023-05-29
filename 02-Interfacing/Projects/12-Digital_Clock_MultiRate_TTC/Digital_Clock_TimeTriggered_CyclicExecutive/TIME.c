/*
 * TIME.c
 *
 * Created: 3/10/2023 6:45:49 AM
 *  Author: osama
 */ 

#include "StdTypes.h"

#include "SSD.h"
#include "SW.h"
#include "TIME.h"


#define MINUTE_MAX_VAL  59
#define HOUR_MAX_VAL    23
#define SEC_MAX_VAL     59

//extern void SSD_Set_Symbol(const u8 SYMBOL);
static void Auto_Update(void);
static void Manual_Update(void);

u8 Hours = 0;
u8 Minutes = 0;
u8 Seconds = 0;

extern SSD_MODE_t SSD_Mode_g ;

void TIME_Update(void){

	Auto_Update();
	Manual_Update();
}

static void Auto_Update(void){

	static u8 Period = 50;       /* 50 * 20 = 1000ms */

	Period--;
	if(Period  == 0){
		if(Seconds == SEC_MAX_VAL){
			Seconds = 0;
			if(Minutes == MINUTE_MAX_VAL){
				Minutes = 0;
				if(Hours == HOUR_MAX_VAL){
					Hours = 0;
				}
				else{
					Hours++;
				}
			}
			else{
				Minutes++;
			}
		}
		else{
			Seconds++;
		}
		Period = 50;
	}

}

static void Manual_Update(void){

	switch(SSD_Mode_g){
	case SSD_NORMAL_MODE:
		/* Time Update Automatic */
		break;
	case SSD_SETTING_HOURS_MODE:
		if(SW_PRESSED == SW_g[SW_UP].state){
			if(Hours < HOUR_MAX_VAL){
				Hours++;
			}
		}
		else if(SW_PRESSED == SW_g[SW_DOWN].state){
			if(Hours > 0){
				Hours--;
			}
		}
		break;
	case SSD_SETTING_MINUTES_MODE:
		if(SW_PRESSED == SW_g[SW_UP].state){
			if(Minutes < MINUTE_MAX_VAL){
				Minutes++;
			}
		}
		else if(SW_PRESSED == SW_g[SW_DOWN].state){
			if(Minutes > 0){
				Minutes--;
			}

		}
		break;
	default:
		break;
	}
}
