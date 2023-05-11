#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_


#define  keypad4X4_PROTEUS

#define  NOT_PRESSED               0x0f      
#define  COL_NUM                    4

#define  R0     PINC0
#define  R1     PINC1
#define  R2     PINC2
#define  R3     PINC3
#define  C0     PINC4
#define  C1     PINC5
#define  C2     PINC6
#define  C3     PINC7 



void KEYPAD_voidInit(void);
u8   kEYPAD_u8GetChar(void);
u8   KEYPAD_u8GetPressed(void);





#endif 
