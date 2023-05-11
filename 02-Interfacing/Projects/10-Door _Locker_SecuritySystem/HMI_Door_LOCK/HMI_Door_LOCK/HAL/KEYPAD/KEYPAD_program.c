#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "KEYPAD_interface.h"



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


u8 Keypad_Row[] = {R0 , R1 , R2 , R3};
u8 Keypad_Col[] = {C0 , C1 , C2 , C3};

void KEYPAD_voidInit(void)
{
	//DIO_voidSetPortDirection(KYPAD_PORT,ROW_INPUT_COL_OUPUT);      //#define ROW_INPUT_COL_OUTPUT   0xf0   from DIO config.c
	
	DIO_WritePin(Keypad_Row[0] , HIGH);
	DIO_WritePin(Keypad_Row[1] , HIGH);
	DIO_WritePin(Keypad_Row[2] , HIGH);
	DIO_WritePin(Keypad_Row[3] , HIGH);
	DIO_WritePin(Keypad_Col[0] , HIGH);
	DIO_WritePin(Keypad_Col[1] , HIGH);
	DIO_WritePin(Keypad_Col[2] , HIGH);
	DIO_WritePin(Keypad_Col[3] , HIGH);
}

u8 KEYPAD_u8GetChar(void)
{
	u8 col = 0;      //counter for loop
	u8 row = 0;      //get value of row
	u8 key = NOT_PRESSED;
	
	for (col=0; col<COL_NUM; ++col)
	{
		DIO_WritePin(Keypad_Col[0] , HIGH);
		DIO_WritePin(Keypad_Col[1] , HIGH);
		DIO_WritePin(Keypad_Col[2] , HIGH);
		DIO_WritePin(Keypad_Col[3] , HIGH);
		
		DIO_WritePin(Keypad_Col[col] , LOW);
		_delay_ms(10);
		
		for(row=0; row < COL_NUM; ++row)
		{
			if(DIO_ReadPin(Keypad_Row[row]) == LOW)    // Check if key is pressed
			{
				while(DIO_ReadPin(Keypad_Row[row]) == LOW);  // wait for key to be released
				
				switch(col)
				{
					case 0:
					if(row == 0) key = keypadchars[row][col];
					else if(row == 1) key = keypadchars[row][col];
					else if(row == 2) key = keypadchars[row][col];
					else if(row == 3) key = keypadchars[row][col];
					break;
					case 1:
					if(row == 0) key = keypadchars[row][col];
					else if(row == 1) key = keypadchars[row][col];
					else if(row == 2) key = keypadchars[row][col];
					else if(row == 3) key = keypadchars[row][col];
					break;
					case 2:
					if(row == 0) key = keypadchars[row][col];
					else if(row == 1) key = keypadchars[row][col];
					else if(row == 2) key = keypadchars[row][col];
					else if(row == 3) key = keypadchars[row][col];
					break;
					case 3:
					if(row == 0) key = keypadchars[row][col];
					else if(row == 1) key = keypadchars[row][col];
					else if(row == 2) key = keypadchars[row][col];
					else if(row == 3) key = keypadchars[row][col];
					break;
				}
			}
		}
	}
	return key;
}

u8 KEYPAD_u8GetPressed(void)
{
	u8 key=NOT_PRESSED;     
	
	do 
	{
		key=KEYPAD_u8GetChar();
	} while (key==NOT_PRESSED);
	
      return key;
}


		
	
	
	
	 
	 
	 

