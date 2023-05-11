#ifndef LCD_H_
#define LCD_H_

//#define F_CPU 8000000UL
#include "DIO_interface.h"
#include "DIO_config.h"
#include <util/delay.h>

/**********************************     LCD Modes   **************************************************/
#define M_4BIT_SAMEPORT  0
#define M_4BIT_SEPARATED 1
#define M_8BIT           2


/********************************* define control pins     *******************************************/
#define RS  PINB0
#define RW  PINB1
#define EN  PINB2
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


extern void LCD_Init(void);
extern void LCD_WriteChar(u8 Character);
extern void LCD_WriteSentence(u8 *PtrSentance);
extern void LCD_GoTo(u8 Line, u8 x);
extern void LCD_WriteNumber(u64 Number);
extern void LCD_WriteNumber4(u16 Number);
extern void LCD_WriteNumber3(u16 Number);
extern void LCD_Create_Character(u8 *Pattern,u8 Location);
extern void LCD_Clear(void);
void lcd_out(uint8_t x,uint8_t y,unsigned char*str);
char *convert_data(unsigned int var);






#endif
