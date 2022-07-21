/*
 * LCD_Interface.h
 *
 * Created: 7/9/2022 4:26:06 PM
 *  Author: Osama
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#define  F_CPU    8000000
#include <util/delay.h>
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"

/**********************************     LCD Modes   **************************************************/
#define M_4BIT_SAMEPORT  0
#define M_4BIT_SEPARATED 1
#define M_8BIT           2


/********************************* define control pins     *******************************************/
#define RS  PINB2
#define EN  PINB0
/*********************************   define LCD Mode       *******************************************/
#define LCD_MODE  M_4BIT_SEPARATED

/*******************for 8 bit mode and 4 bit_sameport mode define the LCD port **********************/
#define LCD_PORT  PA
/*******************for 4 bit same port mode define pins mask in port *******************************/
#define M_4BIT_MASK 0X78
/*******************    for 4 bit separated pins  mode define pins    *******************************/
#define D4 PINA4
#define D5 PINA5
#define D6 PINA6
#define D7 PINA7

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
#define LCD_ENTRY_INC_   							(0x06)
#define LCD_ENTRY_INC_SHIFT   						(0x07)
#define LCD_BEGIN_AT_FIRST_ROW						(0x80)
#define LCD_BEGIN_AT_SECOND_ROW						(0xC0)
#define LCD_CLEAR_SCREEN							(0x01)
#define LCD_ENTRY_MODE								(0x06)

/*******************************************************************************************************/

extern void LCD_Init(void);
extern void LCD_WriteChar(u8 character);
extern void LCD_WriteSentence(u8 *PtrSentance);
extern void LCD_WriteNumber(s64 Number);
extern void LCD_WriteNumber_4D(u64 Number);
extern void LCD_WriteBinary(u8 Number);
extern void LCD_WriteBinary2(u8 Number);
extern void LCD_WriteHex(u8 Number);
extern void LCD_WriteHex2(u8 Number);
extern void LCD_GoTo(u8 Line, u8 cell);
extern void LCD_Clear(void);
extern void LCD_GoToClear(u8 Line , u8 cell , u8 Numofcells);
extern void LCD_GoToWriteString(u8 line,u8 cell,u8*str);
extern void LCD_Create_Character(u8 *Pattern,u8 Location); 
extern void LCD_WriteRealNumber(double Number);
extern void LCD_Scroll(u8 a);

#endif /* LCD_INTERFACE_H_ */