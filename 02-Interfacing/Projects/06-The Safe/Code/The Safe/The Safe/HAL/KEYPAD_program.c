#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "KEYPAD_interface.h"
#include "KEYPAD_config.h"


#ifdef keypad4X4_KIT
static u8  keypadchars[4][4] = {       {'1','2','3','a'},
                                       {'4','5','6','b'},
                                       {'7','8','9','c'},
                                       {'*','0','#','d'}
                                     };
#elif defined(keypad4X4_PROTEUS)
static u8   keypadchars[4][4] = {     {'7','8','9','/'},
                                      {'4','5','6','*'},
                                      {'1','2','3','-'},
                                      {'a','0','=','+'}};
#elif defined (Design)
static u8   keypadchars[4][3] = {       {'1','2','3'},
                                        {'4','5','6'},
                                        {'7','8','9'},
                                        {'*','0','#'}};
                                    
#endif

void KEYPAD_voidInit(void)
{
	//DIO_voidSetPortDirection(KYPAD_PORT,ROW_INPUT_COL_OUPUT);      //#define ROW_INPUT_COL_OUTPUT   0xf0
	DIO_WritePort(KYPAD_PORT,ROW_PULLUP_COL_HIGH);         //#define ROW_PULLUP_COL_HIGH    0xff
}

u8 KEYPAD_u8GetChar(void)
{
	u8 col=0;      //counter for loop
	u8 row=0; //get value of row
	u8 key=0;
	
	for (col=0;col<COL_NUM;col++)
	{
		DIO_higher_nibble_Value(KYPAD_PORT, 0xff);
		DIO_setpinvalue(KYPAD_PORT , (col+4) , LOW);
		_delay_ms(10);
		
		row=DIO_get_lower_nibble(KYPAD_PORT);
		
		if(row !=NOT_PRESSED){
			while (DIO_get_lower_nibble(KYPAD_PORT)!=NOT_PRESSED);
			break;
		}
	}
	if (col==COL_NUM)
	{
		return key;
	}
	else 
	{
		switch (row)
		{
			case 0b00001110:   row=0;break;
			case 0b00001101:   row=1;break;
			case 0b00001011:   row=2;break;
			case 0b00000111:   row=3;break;
			
		}
		key = keypadchars[row][col];
	}
	return key;
}
u8 KEYPAD_u8GetPressed(void)
{
	u8 key=0;     
	
	do 
	{
		key=KEYPAD_u8GetChar();
	} while (key==0);
	
      return key;
}
void KEYPAD_voidUpdate(void)
{
	s8 KYPAD_VAL=KEYPAD_u8GetPressed();
				 	                 
}

		
	
	
	
	 
	 
	 

