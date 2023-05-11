/***************************************************/
/* Author : Osama Mahmoud                          */
/* Date   : 2/11/2020                              */
/***************************************************/

#include "SEG_interface.h"



void SEG_Direction(u8 Copy_u8DisplayID)
{
	DIO_setpinDirection(SEG_PINMAP[Copy_u8DisplayID].SEG_A_Port , SEG_PINMAP[Copy_u8DisplayID].SEG_A_Pin , OUTPUT);
	DIO_setpinDirection(SEG_PINMAP[Copy_u8DisplayID].SEG_B_Port , SEG_PINMAP[Copy_u8DisplayID].SEG_B_Pin , OUTPUT);
	DIO_setpinDirection(SEG_PINMAP[Copy_u8DisplayID].SEG_C_Port , SEG_PINMAP[Copy_u8DisplayID].SEG_C_Pin , OUTPUT);
	DIO_setpinDirection(SEG_PINMAP[Copy_u8DisplayID].SEG_D_Port , SEG_PINMAP[Copy_u8DisplayID].SEG_D_Pin , OUTPUT);
	DIO_setpinDirection(SEG_PINMAP[Copy_u8DisplayID].SEG_E_Port , SEG_PINMAP[Copy_u8DisplayID].SEG_E_Pin , OUTPUT);
	DIO_setpinDirection(SEG_PINMAP[Copy_u8DisplayID].SEG_F_Port , SEG_PINMAP[Copy_u8DisplayID].SEG_F_Pin , OUTPUT);
	DIO_setpinDirection(SEG_PINMAP[Copy_u8DisplayID].SEG_G_Port , SEG_PINMAP[Copy_u8DisplayID].SEG_G_Pin , OUTPUT);
	DIO_setpinDirection(SEG_PINMAP[Copy_u8DisplayID].SEG_Dot_Port , SEG_PINMAP[Copy_u8DisplayID].SEG_Dot_Pin , OUTPUT);
	
}

void SEG_voidDisplayNumber(u8 Copy_u8DisplayID , u8 Copy_u8DisplayNumber)
{
	static u8 SEG_DataNumber[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
	
	if(SEG_PINMAP[Copy_u8DisplayID].SEG_MODE == CATHODE)
	{
		DIO_setpinvalue(SEG_PINMAP[Copy_u8DisplayID].SEG_A_Port , SEG_PINMAP[Copy_u8DisplayID].SEG_A_Pin , CHECK_BIT(SEG_DataNumber[Copy_u8DisplayNumber],0));
		DIO_setpinvalue(SEG_PINMAP[Copy_u8DisplayID].SEG_B_Port , SEG_PINMAP[Copy_u8DisplayID].SEG_B_Pin , CHECK_BIT(SEG_DataNumber[Copy_u8DisplayNumber],1));
		DIO_setpinvalue(SEG_PINMAP[Copy_u8DisplayID].SEG_C_Port , SEG_PINMAP[Copy_u8DisplayID].SEG_C_Pin , CHECK_BIT(SEG_DataNumber[Copy_u8DisplayNumber],2));
		DIO_setpinvalue(SEG_PINMAP[Copy_u8DisplayID].SEG_D_Port , SEG_PINMAP[Copy_u8DisplayID].SEG_D_Pin , CHECK_BIT(SEG_DataNumber[Copy_u8DisplayNumber],3));
		DIO_setpinvalue(SEG_PINMAP[Copy_u8DisplayID].SEG_E_Port , SEG_PINMAP[Copy_u8DisplayID].SEG_E_Pin , CHECK_BIT(SEG_DataNumber[Copy_u8DisplayNumber],4));
		DIO_setpinvalue(SEG_PINMAP[Copy_u8DisplayID].SEG_F_Port , SEG_PINMAP[Copy_u8DisplayID].SEG_F_Pin , CHECK_BIT(SEG_DataNumber[Copy_u8DisplayNumber],5));
		DIO_setpinvalue(SEG_PINMAP[Copy_u8DisplayID].SEG_G_Port , SEG_PINMAP[Copy_u8DisplayID].SEG_G_Pin , CHECK_BIT(SEG_DataNumber[Copy_u8DisplayNumber],6));
	}
	else if(SEG_PINMAP[Copy_u8DisplayID].SEG_MODE == ANODE)
	{
		DIO_setpinvalue(SEG_PINMAP[Copy_u8DisplayID].SEG_A_Port , SEG_PINMAP[Copy_u8DisplayID].SEG_A_Pin , ~CHECK_BIT(SEG_DataNumber[Copy_u8DisplayNumber],0));
		DIO_setpinvalue(SEG_PINMAP[Copy_u8DisplayID].SEG_B_Port , SEG_PINMAP[Copy_u8DisplayID].SEG_B_Pin , ~CHECK_BIT(SEG_DataNumber[Copy_u8DisplayNumber],1));
		DIO_setpinvalue(SEG_PINMAP[Copy_u8DisplayID].SEG_C_Port , SEG_PINMAP[Copy_u8DisplayID].SEG_C_Pin , ~CHECK_BIT(SEG_DataNumber[Copy_u8DisplayNumber],2));
		DIO_setpinvalue(SEG_PINMAP[Copy_u8DisplayID].SEG_D_Port , SEG_PINMAP[Copy_u8DisplayID].SEG_D_Pin , ~CHECK_BIT(SEG_DataNumber[Copy_u8DisplayNumber],3));
		DIO_setpinvalue(SEG_PINMAP[Copy_u8DisplayID].SEG_E_Port , SEG_PINMAP[Copy_u8DisplayID].SEG_E_Pin , ~CHECK_BIT(SEG_DataNumber[Copy_u8DisplayNumber],4));
		DIO_setpinvalue(SEG_PINMAP[Copy_u8DisplayID].SEG_F_Port , SEG_PINMAP[Copy_u8DisplayID].SEG_F_Pin , ~CHECK_BIT(SEG_DataNumber[Copy_u8DisplayNumber],5));
		DIO_setpinvalue(SEG_PINMAP[Copy_u8DisplayID].SEG_G_Port , SEG_PINMAP[Copy_u8DisplayID].SEG_G_Pin , ~CHECK_BIT(SEG_DataNumber[Copy_u8DisplayNumber],6));
	}
}





