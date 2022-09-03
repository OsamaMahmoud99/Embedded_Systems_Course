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


#define  PORTC      (*(volatile unsigned char*)0x35)
#define  DDRC       (*(volatile unsigned char*)0x34)
#define  PINC       (*(volatile unsigned char*)0x33)


#define  PORTD      (*(volatile unsigned char*)0x32)
#define  DDRD       (*(volatile unsigned char*)0x31)
#define  PIND       (*(volatile unsigned char*)0x30)


#define  SET_BIT(reg , bit)       (reg |= (1 << bit))
#define  CLR_BIT(reg , bit)       (reg &= ~(1 << bit))
#define  TOG_BIT(reg , bit)       (reg ^= (1 << bit))
#define  READ_BIT(reg , bit)      ((reg >> bit)&1)

#define WRITE_BIT(reg , bit , value)           
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
			
			if(!READ_BIT(PIND, 0))
			{
				
				
			   PORTB = 0;
    			i++;
						
				if(i == 8){
							i = 0;
				}
				while(!READ_BIT(PIND , 0));
			}
			
			if(!READ_BIT(PIND , 1))
			{	
				PORTB = 0;
				i--;
				if(i == -1){      //i==-1
					i = 7;
				}
				while(!READ_BIT(PIND , 1));
			}
			
			SET_BIT(PORTB , i);
    }
}

