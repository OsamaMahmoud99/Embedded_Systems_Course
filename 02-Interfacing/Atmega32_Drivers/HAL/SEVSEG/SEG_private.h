/***************************************************/
/* Author : Osama Mahmoud                          */
/* Date   : 2/11/2020                              */
/***************************************************/
#ifndef SEG_PRIVATE_H
#define SEG_PRIVATE_H



typedef struct{
	
	u8 SEG_MODE;
	u8 SEG_PINA;
	u8 SEG_PINB;
	u8 SEG_PINC;
	u8 SEG_PIND;
	u8 SEG_PINE;
	u8 SEG_PINF;
	u8 SEG_PING;
	u8 SEG_PINDot;
	
}SEG_PinMap;

extern SEG_PinMap    SEG_PINMAP[Copy_u8SEGNumber];











#endif