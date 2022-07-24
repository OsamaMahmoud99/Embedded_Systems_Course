/*
 * KEYPAD_Interface.h
 *
 * Created: 7/10/2022 4:32:58 PM
 *  Author: Osama
 */ 


#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

#include "DIO_Interface.h"

/*************************** pin config ********************************/

#define FIRST_OUTPUT    PIND0
#define FIRST_INPUT     PINC0

#define COL       4
#define ROW       4

#define NOTPRESSED   0xFF

/****** keypad4X4_KIT
        keypad4X4_PROTEUS
        Design
                            ******/
#define  keypad4X4_PROTEUS

#ifdef keypad4X4_KIT
static u8  keypadchars[ROW][COL] = 
{       
{'7','8','9','A'},
{'4','5','6','B'},
{'1','2','3','E'},
{'c','0','=','F'}
};
#elif defined(keypad4X4_PROTEUS)
static u8   keypadchars[ROW][COL] = 
{{'7','8','9','/'},
 {'4','5','6','*'},
 {'1','2','3','-'},
 {'c','0','=','+'}
};
#elif defined (Design)
static u8   keypadchars[4][3] = 
{       
 {'1','2','3'},
 {'4','5','6'},
 {'7','8','9'},
 {'*','0','#'}
};

#endif

/***************************************************/
u8 KEYPAD_GetChar(void);


#endif /* KEYPAD_INTERFACE_H_ */