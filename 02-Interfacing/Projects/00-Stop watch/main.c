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

unsigned char SEG[] = {0x3F , 0x06 , 0x5B , 0x4F , 0x66 , 0x6D , 0x7C , 0x07 , 0x7F , 0x6F};
void seg_display_MUX(unsigned char n)
{
	int Tens = n / 10;
	int Ones = n % 10;
	
	SET_BIT(PORTA , 0);
	CLR_BIT(PORTA , 1);
	
	PORTB = SEG[Ones];
	_delay_ms(1);
	SET_BIT(PORTA , 1);
	CLR_BIT(PORTA , 0);
	
	PORTB = SEG[Tens];
	_delay_ms(1);

	
}

void seg_display_BCD_MUX(unsigned char n)
{
	int Tens = n/10;
	int Ones = n%10;
	
	SET_BIT(PORTA , 0);
	CLR_BIT(PORTA , 1);
	
	
	PORTB = PORTB&0xF0 | Ones;
	_delay_ms(5);
	
	SET_BIT(PORTA , 1);
	CLR_BIT(PORTA , 0);
	
	
	PORTB = PORTB&0xF0 | Tens;
	_delay_ms(5);
	
}
int main(void)
{

    //output
	DDRC = 0xFF;
	DDRA = 0xFF;
	DDRB = 0b00001111;
	
	// input
	CLR_BIT(DDRD , 0);
	CLR_BIT(DDRD , 1);
	CLR_BIT(DDRD , 2);
	// Pull up
	SET_BIT(PORTD , 0);
	SET_BIT(PORTD , 1);
	SET_BIT(PORTD , 2);

	int pause_Flag = 0  , Reset_Time =  Time , i , Mode_Flag = 0;
	u8 B0_flag = 0 , B1_flag = 0 , B2_flag = 0;
	int Ones;
	int Tens;
	while (1)
	{
		
		if (pause_Flag == 0 && Mode_Flag == 0)
		{
			if (Time > 0)
			{
				Time--;
			}
		}
		
		if (Time >= 0 && Time <= 99)
		{
			for(int x=0; x<100; ++x)
			{
				Ones = Time%10;
				Tens = Time/10;
				seg_display_BCD_MUX(Time);
				if (!READ_BIT(PIND , 0) && Mode_Flag == 0)
				{
					pause_Flag ^= 1 ;
					while(!READ_BIT(PIND , 0));
				}
				
				if (!READ_BIT(PIND , 1) && Mode_Flag == 0)
				{
					Time = Reset_Time;
				}
				
				if (!READ_BIT(PIND , 2))
				{
				    Mode_Flag ^= 1;
					while(!READ_BIT(PIND , 2));
				}
			
				
				if (!READ_BIT(PIND , 0) && Mode_Flag == 1)
				{
					 if (B0_flag == 0)
					 {	
						if (Ones == 9)
						{
							Ones = -1;	
						}
						Ones++;
						Time = Tens*10 + Ones;
						B0_flag = 1;
					}
				}
				else if (READ_BIT(PIND , 0))
				{
					B0_flag = 0;
				}
				
				if (!READ_BIT(PIND , 1) && Mode_Flag == 1)
				{
					if (B1_flag == 0)
					{	
						if (Tens == 9)
						{
							Tens = -1;
						}
						Tens++;
						Time = Tens*10 + Ones;
						B1_flag = 1;
					}
				}
				else if (READ_BIT(PIND , 1))
				{
					B1_flag = 0;
				}	
			}
		}
	}
}

