#define  PORTB2      ((volatile unsigned char*)0x38)
void Set_bit(volatile unsigned char *P , unsigned char bit)
{
	*P |= 1 << bit;	
}
int main(void)
{
	int x = 0 , y=0 , i;

    DDRA = 0xFF;
	PORTA = 0x01;
	
	DDRB = 0xFF;

    Set_bit(PORTB2 , 1);
	
    while (1) 
    {
			
    }
}
