/***************************************************/
/* Author : Osama Mahmoud                          */
/* Date   : 2/11/2020                              */
/***************************************************/

#include "SEG_interface.h"

SEG_PinMap    SEG_PINMAP[Copy_u8SEGNumber] =
{
	
	{CATHODE,PD,PIND0%8,PD,PIND1%8,PD,PIND2%8,PD,PIND3%8,PD,PIND4%8,PD,PIND5%8,PD,PIND6%8,PB,PINB0%8},
	{CATHODE,PA,PINA4%8,PA,PINA5%8,PA,PINA6%8,PA,PINA7%8,PB,PINB2%8,PB,PINB3%8,PB,PINB4%8,PB,PINB1%8}
};