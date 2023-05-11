/***************************************************/
/* Author : Osama Mahmoud                          */
/* Date   : 2/11/2020                              */
/***************************************************/
#ifndef SEG_PRIVATE_H
#define SEG_PRIVATE_H



typedef struct{
	
	u8 SEG_MODE;
	u8 SEG_A_Port;
	u8 SEG_A_Pin;
	u8 SEG_B_Port;
	u8 SEG_B_Pin;
	u8 SEG_C_Port;
	u8 SEG_C_Pin;
	u8 SEG_D_Port;
	u8 SEG_D_Pin;
	u8 SEG_E_Port;
	u8 SEG_E_Pin;
	u8 SEG_F_Port;
	u8 SEG_F_Pin;
	u8 SEG_G_Port;
	u8 SEG_G_Pin;
	u8 SEG_Dot_Port;
	u8 SEG_Dot_Pin;
	
}SEG_PinMap;

extern SEG_PinMap    SEG_PINMAP[Copy_u8SEGNumber];











#endif