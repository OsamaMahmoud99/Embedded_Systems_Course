/*
 * LCD_Program.c
 *
 * Created: 7/9/2022 4:26:27 PM
 *  Author: Osama
 */ 

#include "LCD_Interface.h"

/************************************* 8 BIT Mode functions********************************************/
#if (LCD_MODE==M_8BIT)

static void LCD_WriteCommand(u8 Command)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePort(LCD_PORT,(Command));
	DIO_WritePin(EN,HIGH);
	_delay_ms(2);
	DIO_WritePin(EN,LOW);
	_delay_ms(2);
}

static void LCD_WriteData(u8 Data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePort(LCD_PORT,(Data));
	DIO_WritePin(EN,HIGH);
	_delay_ms(2);
	DIO_WritePin(EN,LOW);
	_delay_ms(2);
}

void LCD_Init(void)
{
	_delay_ms(50);          // said in Data sheet to delay after power on for 1st time
	
	LCD_WriteCommand(0x38); //N=1 , F=0
	_delay_ms(1);           //delay 1ms a must delay as said in Data sheet
	LCD_WriteCommand(0x0E); //D=1(LCD itself on or off) C=0, B=0
	_delay_ms(1);    //delay 1ms
	LCD_WriteCommand(0x01); //clear LCD
	_delay_ms(20);
	LCD_WriteCommand(0x06); //Entry Mode
	LCD_WriteCommand(0x80);
}

/************************************* 4 BIT Mode separated Pins functions********************************************/
#elif (LCD_MODE==M_4BIT_SEPARATED)
static void LCD_WriteCommand(u8 Command)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePin(D7 , READ_BIT(Command , 7));
	DIO_WritePin(D6 , READ_BIT(Command , 6));
	DIO_WritePin(D5 , READ_BIT(Command , 5));
	DIO_WritePin(D4 , READ_BIT(Command , 4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(2);
	DIO_WritePin(EN,LOW);
	_delay_ms(2);
	DIO_WritePin(D7 , READ_BIT(Command , 3));
	DIO_WritePin(D6 , READ_BIT(Command , 2));
	DIO_WritePin(D5 , READ_BIT(Command , 1));
	DIO_WritePin(D4 , READ_BIT(Command , 0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(2);
	DIO_WritePin(EN,LOW);
	_delay_ms(2);
}

static void LCD_WriteData(u8 Data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(D7 , READ_BIT(Data , 7));
	DIO_WritePin(D6 , READ_BIT(Data , 6));
	DIO_WritePin(D5 , READ_BIT(Data , 5));
	DIO_WritePin(D4 , READ_BIT(Data , 4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(2);
	DIO_WritePin(EN,LOW);
	_delay_ms(2);
	DIO_WritePin(D7 , READ_BIT(Data , 3));
	DIO_WritePin(D6 , READ_BIT(Data , 2));
	DIO_WritePin(D5 , READ_BIT(Data , 1));
	DIO_WritePin(D4 , READ_BIT(Data , 0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(2);
	DIO_WritePin(EN,LOW);
	_delay_ms(2);
}

void LCD_Init(void)
{
	_delay_ms(50);          // said in Data sheet to delay after power on for 1st time
	LCD_WriteCommand(0x02);//4 bit mode only
	_delay_ms(1);
	LCD_WriteCommand(0x28); //N=1 , F=0
	_delay_ms(1);           //delay 1ms a must delay as said in Data sheet
	LCD_WriteCommand(0x0c); //D=1(LCD itself on or off) C=0, B=0
	_delay_ms(1);    //delay 1ms
	LCD_WriteCommand(0x01); //clear LCD
	_delay_ms(20);
	LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x80);
}

#endif

/*************************** service functions*****************************************************/
void LCD_WriteChar(u8 character)
{
	LCD_WriteData(character);
}

void LCD_WriteSentence(u8 *PtrSentance)
{
	u8 i=0;
	for(i=0;PtrSentance[i];i++)
	{
		LCD_WriteData(PtrSentance[i]);
	}
}

void LCD_WriteNumber(s64 Number)
{
	u8 arr[20];
	u8 i = 0 , j;
	if (Number == 0)
	{
		LCD_WriteData('0');
	}
	if (Number < 0)
	{
		Number = Number * -1;
		LCD_WriteData('-');
	}

	while(Number)
	{
		arr[i++] = Number%10 + '0';
		Number /= 10;
	}		
	for (j = i; j>0; --j)
	{
		LCD_WriteData(arr[j - 1]);
	}
}

void LCD_WriteNumber_4D(u64 Number)
{
	LCD_WriteChar(((Number%10000)/1000)+'0');
	LCD_WriteChar(((Number%1000)/100)+'0');
	LCD_WriteChar(((Number%100)/10)+'0');	
	LCD_WriteChar(((Number%10)/1)+'0');
}

void LCD_WriteBinary(u8 Number)
{
	s8 i;
	u8 flag = 0;
	for (i=7; i>=0; --i)
	{
		if ((Number>>i)&1)
		{
			LCD_WriteData('1');
			flag = 1;
		}
		else
		{
			if (flag == 1)
			{
				LCD_WriteData('0');
			}
		}
	}
}
void LCD_WriteBinary2(u8 Number)
{
	u8 Rem , i=0 , j;
	u8 Binary[8]={0};
	while(Number)
	{
		Rem = Number % 2;
		Number = Number/2;
		Binary[i++] = Rem+'0';
	}
	
	for (j=i; j>0; --j)
	{
		LCD_WriteData(Binary[j - 1]);
	}
}

u8 Hex[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
void LCD_WriteHex(u8 Number)
{
	u8 Rem , i=0 , j;
	u8 Arr[2];	
	while(Number)
	{
		Rem = Number % 16;
		Number = Number/16;
		Arr[i++] = Hex[Rem];
	}
	
	for (j=i; j>0; --j)
	{
		LCD_WriteData(Arr[j - 1]);
	}
}

void LCD_WriteHex2(u8 Number) //0xfe
{
	u8 Hnibble = Number >> 4;  //0x0f
	u8 Lnibble = Number & 0x0F; //0x0e
	if (Hnibble <= 9)
	{
		LCD_WriteData(Hnibble + '0');
	}
	else
	{
		LCD_WriteData(Hnibble -10 + 'A');
	}
	/*if (Lnibble <= 9)
	{
		LCD_WriteData(Lnibble + '0');
	}
	else
	{
		LCD_WriteData(Lnibble -10 + 'A');
	}*/
	LCD_WriteData(Hex[Lnibble]);
}

void LCD_GoTo(u8 Line, u8 cell)
{
	if(0 == Line)
	{
		if ( cell <=15)
		{
			LCD_WriteCommand(0x80 + cell);
		}
	}
	else if (1 == Line)
	{
		if ( cell <=15)
		{
			LCD_WriteCommand(0xC0+ cell);
		}
	}
}

void LCD_Clear(void)
{
	LCD_WriteCommand(0x01);
}

void LCD_GoToClear(u8 Line , u8 cell , u8 Numofcells)
{
	LCD_GoTo(Line , cell);
	
	for (u8 i=0; i<Numofcells; ++i)
	{
		LCD_WriteData(' ');
	}
}

void LCD_GoToWriteString(u8 line,u8 cell,u8*str)
{
	LCD_GoTo(line,cell);
	LCD_WriteSentence(str);
}

void Create_Character(u8 *Pattern,u8 Location) 
{
	u8 iLoop=0;

	LCD_WriteCommand(0x40+(Location*8)); //Send the Address of CGRAM
	for(iLoop=0;iLoop<8;iLoop++)
	LCD_WriteData(Pattern[iLoop]); //Pass the bytes of pattern on LCD
	LCD_WriteCommand(0x80);        // to return to DDRAM
}

void LCD_WriteRealNumber(double Number)
{
	char Str[16];
	
	char *TmpSign = (Number < 0) ? "-" : "";
	float TmpVal  = (Number < 0) ? -Number : Number;
	
	int TmpInt1 = TmpVal;
	float TmpFrac = TmpVal - TmpInt1;
	int TmpInt2 = TmpFrac * 1000;
	
	sprintf(Str, "%s%d.%04d", TmpSign , TmpInt1 , TmpInt2);
	
	LCD_WriteSentence(Str);
}

void LCD_Scroll(u8 a) //for scrolling
{
	u8 i;
	for(i = 0; i < a; i++)
	{
		LCD_WriteCommand(LCD_MOVE_DISP_RIGHT); // shifting the entire display right.
		_delay_ms(1000);
	}
}