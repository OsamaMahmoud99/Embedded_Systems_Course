/*
 * AVR.c
 *
 * Created: 7/4/2022 1:58:41 PM
 * Author : Osama
 */ 


#define  F_CPU    8000000
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
	int x = 0 , y=0 , i;

    DDRA = 0xFF;
	PORTA = 0x01;
	
	DDRB = 0xFF;

    while (1) 
    {
			for (i=0; i<5; ++i)
			{
				PORTB = 0xFF;
				_delay_ms(500);
				PORTB = 0x00;
				_delay_ms(500);
			}
			
			for(i=0; i<5; ++i)
			{
				PORTB = 0x0F;
				_delay_ms(500);
				PORTB = 0xF0;
				_delay_ms(500);
			}
			
			for(i=0; i<5; ++i)
			{
				PORTB = 3 << x;
				x = x + 4;
				PORTB |= 3 << x;
				x = x - 2;
				_delay_ms(1000);
				
				if(x == 4){
					x = 0;
				}
			}
			for(i=0; i<5; ++i)
			{
				PORTB = 0b01010101;
				_delay_ms(500);
				PORTB = 0b10101010;
				_delay_ms(500);
			}
		
    }
}

