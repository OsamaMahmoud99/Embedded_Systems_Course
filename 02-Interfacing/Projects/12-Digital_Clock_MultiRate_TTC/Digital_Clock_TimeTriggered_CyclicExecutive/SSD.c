/*
 * SSD.c
 *
 * Created: 3/10/2023 7:07:07 AM
 *  Author: osama
 */ 



#include "SW.h"
#include "SSD.h"


static void On(const SSD_t SSD_ID);
static void Off(const SSD_t SSD_ID);
static void Update_Symbol(const u8 SYMBOL);
static void Refesh(void);
static void Update_Mode(void);

SSD_MODE_t SSD_Mode_g = SSD_NORMAL_MODE;
static SSD_t SSD_Id = SSD_HOURS_TENS;

extern u8 Hours;
extern u8 Minutes;
extern u8 Seconds;

void SSD_Update(void){
	Update_Mode();
	Refesh();
}

static void On(const SSD_t SSD_ID){
	switch(SSD_ID){
	case SSD_HOURS_TENS:
		DIO_WritePin(SSD_HOURS_TENS_PIN_ID, SSD_STATE_ON);
		break;
	case SSD_HOURS_UNITS:
		DIO_WritePin(SSD_HOURS_UNITS_PIN_ID, SSD_STATE_ON);
		break;
	case SSD_MIN_TENS:
		DIO_WritePin(SSD_MIN_TENS_PIN_ID, SSD_STATE_ON);
		break;
	case SSD_MIN_UNITS:
		DIO_WritePin(SSD_MIN_UNITS_PIN_ID, SSD_STATE_ON);
		break;
	case SSD_SEC_TENS:
		DIO_WritePin(SSD_SEC_TENS_PIN_ID, SSD_STATE_ON);
		break;
	case SSD_SEC_UNITS:
		DIO_WritePin(SSD_SEC_UNITS_PIN_ID, SSD_STATE_ON);
		break;
	default:
		/* Error: Undefined SSD */
		break;
	}
}

static void Off(const SSD_t SSD_ID){
	switch(SSD_ID){
	case SSD_HOURS_TENS:
		DIO_WritePin(SSD_HOURS_TENS_PIN_ID, SSD_STATE_OFF);
		break;
	case SSD_HOURS_UNITS:
		DIO_WritePin(SSD_HOURS_UNITS_PIN_ID, SSD_STATE_OFF);
		break;
	case SSD_MIN_TENS:
		DIO_WritePin(SSD_MIN_TENS_PIN_ID, SSD_STATE_OFF);
		break;
	case SSD_MIN_UNITS:
		DIO_WritePin(SSD_MIN_UNITS_PIN_ID, SSD_STATE_OFF);
		break;
	case SSD_SEC_TENS:
		DIO_WritePin(SSD_SEC_TENS_PIN_ID, SSD_STATE_OFF);
		break;
	case SSD_SEC_UNITS:
		DIO_WritePin(SSD_SEC_UNITS_PIN_ID, SSD_STATE_OFF);
		break;
	default:
		/* Error: Undefined SSD */
		break;
	}
}

static void Update_Symbol(const u8 SYMBOL){
	DIO_WritePin(SSD_A_PIN_ID, READ_BIT(SYMBOL, 0));
	DIO_WritePin(SSD_B_PIN_ID, READ_BIT(SYMBOL, 1));
	DIO_WritePin(SSD_C_PIN_ID, READ_BIT(SYMBOL, 2));
	DIO_WritePin(SSD_D_PIN_ID, READ_BIT(SYMBOL, 3));
}

static void Refesh(void){

	Off(SSD_HOURS_TENS);
	Off(SSD_HOURS_UNITS);
	Off(SSD_MIN_TENS);
	Off(SSD_MIN_UNITS);
	Off(SSD_SEC_TENS);
	Off(SSD_SEC_UNITS);

	switch(SSD_Id){
	case SSD_HOURS_TENS:
		Update_Symbol(Hours / 10);
		On(SSD_HOURS_TENS);
		SSD_Id = SSD_HOURS_UNITS;
		break;
	case SSD_HOURS_UNITS:
		Update_Symbol(Hours % 10);
		On(SSD_HOURS_UNITS);
		SSD_Id = SSD_MIN_TENS;
		break;
	case SSD_MIN_TENS:
		Update_Symbol(Minutes / 10);
		On(SSD_MIN_TENS);
		SSD_Id = SSD_MIN_UNITS;
		break;
	case SSD_MIN_UNITS:
		Update_Symbol(Minutes % 10);
		On(SSD_MIN_UNITS);
		SSD_Id = SSD_SEC_TENS;
		break;
	case SSD_SEC_TENS:
		Update_Symbol(Seconds / 10);
		On(SSD_SEC_TENS);
		SSD_Id = SSD_SEC_UNITS;
		break;
	case SSD_SEC_UNITS:
		Update_Symbol(Seconds % 10);
		On(SSD_SEC_UNITS);
		SSD_Id = SSD_HOURS_TENS;
		break;

	default:
		/* Error: Undefined SSD */
		break;
	}
}

static void Update_Mode(void){

	switch(SSD_Mode_g){
	case SSD_NORMAL_MODE:
		if(SW_PRESSED == SW_g[SW_SETTING].state){
			SSD_Mode_g = SSD_SETTING_HOURS_MODE;
		}
		break;
	case SSD_SETTING_HOURS_MODE:
		if(SW_PRESSED == SW_g[SW_SETTING].state){
			SSD_Mode_g = SSD_SETTING_MINUTES_MODE;
		}
		/*else if(SW_PRESSED == SW_g[SW_UP].state){

		}*/
		break;
	case SSD_SETTING_MINUTES_MODE:
		if(SW_PRESSED == SW_g[SW_SETTING].state){
			SSD_Mode_g = SSD_NORMAL_MODE;
		}
		break;
	default:
		break;

	}

}

