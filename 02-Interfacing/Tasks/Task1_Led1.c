/*
 * AVR.c
 *
 * Created: 7/4/2022 1:58:41 PM
 * Author : Osama
 */ 


#define  F_CPU    1000000
#include <util/delay.h>

#define  PORTA      (*(volatile unsigned char*)0x3B)
#define  DDRA       (*(volatile unsigned char*)0x3A)
#define  PINA       (*(volatile unsigned char*)0x39)

#define  PORTB      (*(volatile unsigned char*)0x38)
#define  DDRB       (*(volatile unsigned char*)0x37)
#define  PINB       (*(volatile unsigned char*)0x36)

//#define cpu_F     8000000

/*volatile unsigned long i;

void delay_s(int time)
{
	#ifndef cpu_F
	#define  cpu_F       1000000
	#warning "cpu not define"
	#endif
	
	for(i=0; i<time*cpu_F; ++i)
	{
		
	}
}
*/

int main(void)
{
	int x = 0 , y=0;

    DDRA = 0xFF;
	PORTA = 0x01;
	
	DDRB = 0xFF;

    while (1) 
    {
		if(y == 0)
		{
			PORTB = 1 << x;
			x++;
			_delay_ms(1000);
			if(x == 8){
				x = 0;
			}
		}
	
		if(x == 0)
		{
			PORTB  = 128 >> y;
			y++;
			_delay_ms(1000);
			if(y == 8){
				y = 0;
			}
		}
		
		
    }
}

