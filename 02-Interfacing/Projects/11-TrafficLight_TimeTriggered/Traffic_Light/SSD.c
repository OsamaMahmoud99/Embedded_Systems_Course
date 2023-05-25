/*
 * SSD.c
 *
 * Created: 3/10/2023 7:07:07 AM
 *  Author: osama
 */ 

#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "SSD.h"

typedef enum{
	SSD_TENS = 0,
	SSD_UNITS
}SSD_t;

/******************************************************************************/
static void SSD_On(const SSD_t SSD_ID);
static void SSD_Off(const SSD_t SSD_ID);
static void SSD_Update_Symbol(const u8 SYMBOL);
static void SSD_Refesh(void);
void SSD_Set_Symbol(const u8 SYMBOL);

static u8 SSD_Symbol = 0;

static void SSD_On(const SSD_t SSD_ID){
	switch(SSD_ID){
		case SSD_TENS:
		DIO_WritePin(SSD_TENS_PIN_ID, SSD_STATE_ON);
		break;
		case SSD_UNITS:
		DIO_WritePin(SSD_UNITS_PIN_ID, SSD_STATE_ON);
		break;
		default:
		/* Error: Undefined SSD */
		break;
	}
}

static void SSD_Off(const SSD_t SSD_ID){
	switch(SSD_ID){
		case SSD_TENS:
		DIO_WritePin(SSD_TENS_PIN_ID, SSD_STATE_OFF);
		break;
		case SSD_UNITS:
		DIO_WritePin(SSD_UNITS_PIN_ID, SSD_STATE_OFF);
		break;
		default:
		/* Error: Undefined SSD */
		break;
	}
}

static void SSD_Update_Symbol(const u8 SYMBOL){
	DIO_WritePin(SSD_A_PIN_ID, READ_BIT(SYMBOL, 0));
	DIO_WritePin(SSD_B_PIN_ID, READ_BIT(SYMBOL, 1));
	DIO_WritePin(SSD_C_PIN_ID, READ_BIT(SYMBOL, 2));
	DIO_WritePin(SSD_D_PIN_ID, READ_BIT(SYMBOL, 3));
}

static void SSD_Refesh(void){
	static SSD_t SSD_Id = SSD_TENS;
	SSD_Off(SSD_TENS);
	SSD_Off(SSD_UNITS);
	switch(SSD_Id){
		case SSD_TENS:
		SSD_Update_Symbol(SSD_Symbol / 10);
		SSD_On(SSD_TENS);
		SSD_Id = SSD_UNITS;
		break;
		case SSD_UNITS:
		SSD_Update_Symbol(SSD_Symbol % 10);
		SSD_On(SSD_UNITS);
		SSD_Id = SSD_TENS;
		break;
		default:
		/* Error: Undefined SSD */
		break;
	}
}

void SSD_Update(void){
	SSD_Refesh();
}

void SSD_Set_Symbol(const u8 SYMBOL){
	SSD_Symbol = SYMBOL;
}
