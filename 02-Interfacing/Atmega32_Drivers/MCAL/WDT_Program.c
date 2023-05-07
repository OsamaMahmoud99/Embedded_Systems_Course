/*
 * WDT_Program.c
 *
 * Created: 8/6/2022 1:17:52 PM
 *  Author: Osama
 */ 

#include "WDT_Interface.h"


void WDT_Set(timeout_type time)
{
	u8 wdt_value=0x08; //WDE SET & WDTOE CLEARED
	wdt_value |= time;
	WDTCR |= (1<<WDTOE)|(1<<WDE);
	WDTCR = wdt_value;
}
void WDT_Stop(void)
{
	WDTCR = (1<<WDTOE)|(1<<WDE);
	
	WDTCR = 0;
}
