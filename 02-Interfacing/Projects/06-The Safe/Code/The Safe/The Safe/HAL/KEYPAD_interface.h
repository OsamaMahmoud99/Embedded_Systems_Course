#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_


#define  COL_NUM                    4
#define  ROW_INPUT_COL_OUPUT       0xf0
#define  ROW_PULLUP_COL_HIGH       0xff
#define  NOT_PRESSED               0x0f   
   
void KEYPAD_voidInit(void);
u8   kEYPAD_u8GetChar(void);
u8   KEYPAD_u8GetPressed(void);
void KEYPAD_voidUpdate(void);




#endif 
