/*
 * TIME.c
 *
 * Created: 3/10/2023 6:45:49 AM
 *  Author: osama
 */ 

#include "StdTypes.h"
#include "TIME.h"

#define SEC_MAX_VAL 59

extern void SSD_Set_Symbol(const u8 SYMBOL);

void TIME_Update(void){
	static u8 Seconds = 0;
	if(Seconds < SEC_MAX_VAL){
		Seconds++;
		}else{
		Seconds = 0;
	}
	SSD_Set_Symbol(Seconds);
}
