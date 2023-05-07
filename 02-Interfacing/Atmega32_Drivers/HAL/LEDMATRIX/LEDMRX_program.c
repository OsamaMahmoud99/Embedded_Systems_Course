/***********************************************************************************/
/*  Author  :  OsamaMahmoud                                                        */
/*  Date    :  2/11/2020                                                            */
/***********************************************************************************/       

#include <util/delay.h>
#include "StdTypes.h"
#include "Utils.h"

#include "DIO_interface.h"

#include "LEDMRX_interface.h"
#include "LEDMRX_config.h"
#include "LEDMRX_private.h"

u8 rows[8]={LEDMRX_ROW0_PIN,LEDMRX_ROW1_PIN,LEDMRX_ROW2_PIN,LEDMRX_ROW3_PIN,LEDMRX_ROW4_PIN,
             LEDMRX_ROW5_PIN,LEDMRX_ROW6_PIN,LEDMRX_ROW7_PIN};

u8 cols[8]={LEDMRX_COL0_PIN,LEDMRX_COL1_PIN,LEDMRX_COL2_PIN,LEDMRX_COL3_PIN,LEDMRX_COL4_PIN,
             LEDMRX_COL5_PIN,LEDMRX_COL6_PIN,LEDMRX_COL7_PIN};

volatile u8  Waiting = 10;
volatile u8  No_Animation = 0;

void LEDMRX_voidInit(void)
{
	DIO_Init();
}

void LEDMRX_voidDispaly(u8 *Copy_u8Data)
{
	
		for(u8 i=0; i<=7; ++i)
		{
            DisableALLCols();
			SetRowValues(Copy_u8Data[i]);
			DIO_WritePin(cols[i] ,LOW);
			_delay_us(1000);
		}
	
}

static void DisableALLCols(void)
{
	for(u8 j=0; j<=7 ; ++j)
	{
		DIO_WritePin(cols[j] , HIGH);
	}
}


static void SetRowValues(u8 Copy_u8Value)
{
	u8 Local_u8BIT;
	
	for(u8 k=0;k<=7;++k)
	{
		Local_u8BIT=CHECK_BIT(Copy_u8Value,k);
		DIO_WritePin(rows[k], Local_u8BIT);
	}
}
void LEDMRX_voidAnimation(u8 *Copy_u8Data) 
{

	u8 index = 0;
		
        for(index =0 ; index<30 ; ++index)
	    {
		while(No_Animation);
		u8 Local_u8TempData[8]={Copy_u8Data[index],Copy_u8Data[index+1],Copy_u8Data[index+2],Copy_u8Data[index+3],Copy_u8Data[index+4],
							    Copy_u8Data[index+5],Copy_u8Data[index+6],Copy_u8Data[index+7]};
		    for(u8 w=0; w<Waiting; ++w)
		    {
			    for(u8 i=0; i<=7; ++i)
				{
			        DisableALLCols();
					SetRowValues(Local_u8TempData[i]);
					DIO_WritePin(cols[i] , LOW);
					_delay_us(1000);
				}
		    }
			
			
	    }
    
}

void LEDMRX_voidResumeAnimation(void)
{
	No_Animation = 0;
}
void LEDMRX_voidStopAnimation(void)
{
	No_Animation = 1;
}
void LEDMRX_voidSpeedUp(void)
{
	Waiting = Waiting - 2;
}
void LEDMRX_voidSpeedDown(void)
{
	Waiting = Waiting + 2;
}



