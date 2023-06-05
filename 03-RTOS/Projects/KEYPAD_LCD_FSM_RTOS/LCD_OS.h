/*
 * LCD_OS.h
 *
 * Created: 8/29/2022 1:17:32 PM
 *  Author: Osama
 */ 


#ifndef LCD_OS_H_
#define LCD_OS_H_

#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"

/**********************************     LCD Modes   **************************************************/
#define M_4BIT_SAMEPORT  0
#define M_4BIT_SEPARATED 1
#define M_8BIT           2


/********************************* define control pins     *******************************************/

/* for kit */
#define RS  PINB_2
#define EN  PINB_0
/*********************************   define LCD Mode       *******************************************/
#define LCD_MODE  M_8BIT

/*******************for 8 bit mode and 4 bit_sameport mode define the LCD port **********************/
#define LCD_PORT  PA

/*******************    for 4 bit separated pins  mode define pins    *******************************/

/*** for kit ***/
#define D4 PINA_4
#define D5 PINA_5
#define D6 PINA_6
#define D7 PINA_7

/******************************************************************************************************/
#define LCD_FUNCTION_8BIT_2LINES   					(0x38)
#define LCD_FUNCTION_4BIT_2LINES   					(0x28)
#define LCD_MOVE_DISP_RIGHT       					(0x1C)
#define LCD_MOVE_DISP_LEFT   						(0x18)
#define LCD_MOVE_CURSOR_RIGHT   					(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  					(0x10)
#define LCD_DISP_OFF   								(0x08)
#define LCD_DISP_ON_CURSOR   						(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK   					(0x0F)
#define LCD_DISP_ON_BLINK   						(0x0D)
#define LCD_DISP_ON   								(0x0C)
#define LCD_ENTRY_DEC   							(0x04)
#define LCD_ENTRY_DEC_SHIFT   						(0x05)
#define LCD_ENTRY_MODE   							(0x06)
#define LCD_ENTRY_INC_SHIFT   						(0x07)
#define LCD_BEGIN_AT_FIRST_ROW						(0x80)
#define LCD_BEGIN_AT_SECOND_ROW						(0xC0)
#define LCD_CLR_SCREEN							    (0x01)
#define LCD_ENTRY_MODE								(0x06)

/*******************************************************************************************************/

void LCD_OS_Init(void);
void LCD_OS_Task(void* pvoid);
u8 LCD_OS_WriteChar(u8 character);


#endif /* LCD_OS_H_ */
