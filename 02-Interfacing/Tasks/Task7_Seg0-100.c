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

//#define WRITE_BIT(reg , bit , value)     


unsigned char SEG[] = {0x3F , 0x06 , 0x5B , 0x4F , 0x66 , 0x6D , 0x7C , 0x07 , 0x7F , 0x6F};
void seg_display(unsigned char n)
{
	
	PORTC = SEG[n/10];
	PORTD = SEG[n%10];

}

      
int main(void)
{

	DDRC = 0xFF;
	DDRD = 0xFF;

    unsigned char i = 0;
    while (1) 
    {
		for(i=0; i<100; ++i)
		{
			seg_display(i);
			_delay_ms(500);
		}
    }
}

