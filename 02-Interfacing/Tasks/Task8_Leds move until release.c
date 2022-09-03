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




int main(void)
{
	int x = 0 , y=0 , i=0;

	DDRB = 0xFF;

	CLR_BIT(DDRD , 0);
	CLR_BIT(DDRD , 1);
	SET_BIT(PORTD , 0);
	SET_BIT(PORTD , 1);
	
	while (1)
	{
		
		while(!READ_BIT(PIND, 0))
		{
			PORTB = 0;
			i++;
				
			if(i == 8){
				i = 0;
			}
			SET_BIT(PORTB , i);
			_delay_ms(50);
			
		}
		
		while(!READ_BIT(PIND , 1))
		{
			
				PORTB = 0;
				i--;
				
				if(i == -1){     
					i = 7;
				}
				SET_BIT(PORTB , i);
				_delay_ms(50);
		}
	}
}
