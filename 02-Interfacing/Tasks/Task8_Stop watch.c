 /*
 * AVR.c
 *
 * Created: 7/4/2022 1:58:41 PM
 * Author : Osama
 */ 


#define  F_CPU    8000000
#include <util/delay.h>

#include "MemMap.h"
#include "StdTypes.h"
#include "Utils.h"



#define  SEG_PORT        PORTC


u16 Time = 30;


void seg_display_BCD(unsigned char n)
{
	int Tens = n/10;
	int Ones = n%10;
	
	SEG_PORT = (Ones << 4) | Tens;
}

int main(void)
{

    //output
	DDRC = 0xFF;
	// input
	CLR_BIT(DDRD , 0);
	CLR_BIT(DDRD , 1);
	CLR_BIT(DDRD , 2);
	// Pull up
	SET_BIT(PORTD , 0);
	SET_BIT(PORTD , 1);
	SET_BIT(PORTD , 2);

	int pause_Flag = 0  , Reset_Time =  Time , i , Mode_Flag = 0;
	int INC_Flag = 0 , DEC_Flag = 0;
	while (1)
	{
	
		if (pause_Flag == 0 && Mode_Flag == 0)
		{
			Time--;
		}
		
		if ((Time !=0  && Mode_Flag == 0)||INC_Flag==1 || DEC_Flag==1)
		{
			seg_display_BCD(Time);
		}
		for (i=0; i<100; ++i)
		{
				_delay_ms(10);
				if (!READ_BIT(PIND , 0) && Mode_Flag == 0)
				{
						pause_Flag ^= 1 ;
						while(!READ_BIT(PIND , 0));
						break;
				}
				
				if (!READ_BIT(PIND , 1) && Mode_Flag == 0)
				{
					    Time = Reset_Time;
				}
				
				if (!READ_BIT(PIND , 2))
				{
					Mode_Flag ^= 1;
					DEC_Flag = 0;
					INC_Flag = 0;
					while(!READ_BIT(PIND , 2));
				}
				
				if (!READ_BIT(PIND , 0) && Mode_Flag == 1)
				{
							Time ++;
							while(!READ_BIT(PIND , 0));
							INC_Flag = 1;
				}
				if (!READ_BIT(PIND , 1) && Mode_Flag == 1)
				{
							Time --;
							while(!READ_BIT(PIND , 1));
							DEC_Flag = 1;
				}

						
		}

		
	}
}

