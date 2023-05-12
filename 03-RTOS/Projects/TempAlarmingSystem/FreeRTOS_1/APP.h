/*
 * APP.h
 *
 * Created: 9/26/2022 2:46:45 PM
 *  Author: Osama
 */ 


#ifndef APP_H_
#define APP_H_

#include "StdTypes.h"
#include "DIO_Interface.h"
#include "UART_Interface.h"
#include "UART_Service.h"
#include "ADC_Interface.h"
#include "LCD_Interface.h"
#include "LM35_Interface.h"

/* Tasks /Functions Prototypes*/
void System_Init(void);
void T_Control(void* pvParam);
void T_SysCheck(void* pvParam);
void T_Terminal(void* pvParam);
void T_Sensing(void* pvParam);
void T_Display(void* pvParam);
void T_Indication(void* pvParam);

/* used to trigger the T_Control task */
#define E_PUMPON		(1<<0)		/* Is set by the T_SysCheck task */
#define E_HEATERON		(1<<1)		/* Is set by the T_SysCheck task */
#define E_COOLERON		(1<<2)		/* Is set by the T_SysCheck task */
#define E_CONTROLMASK 	(0b111)

/* used to trigger the T_Display task */
#define E_MainScreen	(1<<0)
#define E_ConfigScreen	(1<<1)
#define E_HUpdated		(1<<2)
#define E_TUpdated		(1<<3)
#define E_TTUpdated		(1<<4)	/* Changed */
#define E_HTUpdated		(1<<5)
#define E_MotorState	(1<<6) 	/* Changed */
#define E_Next			(1<<7)	/* Changed */
#define E_DISPLAYMASK 	(0b11111111) /* Changed */

#define DISABLED 	0x2
#define ENABLED	 	0xF


/* MOTORs*/
#define WATER_PUMP 		PIND_2
#define HEATER	   		PIND_3
#define COOLER	   		PIND_4


/*************** Display ********************/
#define LCD_MAIN_SCREEN_L1		"T =    C    H =    %"
#define LCD_MAIN_SCREEN_L2		"TT=    C    TH=    %"
#define LCD_TEMP_COL			4
#define LCD_HUMI_COL			16

#define LCD_MAIN_SCREEN_L3		"P:      H:     C:   "
#define LCD_PUMP_COL			2
#define LCD_HEATER_COL			10
#define LCD_COOLER_COL			17

#define LCD_MAIN_SCREEN_L4		"  Configuration: C  "

#define LCD_CONFIG_SCREEN_L1	"TempThreshold:     C"
#define LCD_CONFIG_SCREEN_L2	"HumiThreshold:     %"
#define LCD_CONFIG_COL			14

#define LCD_CONFIG_SCREEN_L4	"OK:O Next:N Cancel:C"


#if	1
EventGroupHandle_t egControl = NULL;
EventGroupHandle_t egDisplay = NULL;
EventBits_t ebControlBits;
EventBits_t ebDisplayBits;
SemaphoreHandle_t bsCheck;
#endif

/* 1 */
typedef enum
{
	OFF,ON
}Motor;

/* 1 */
struct
{
	Motor Water_Pump;
	Motor Heater;
	Motor Cooler;
}Motors_State;

typedef enum{
	MainState, 
	ConfigState
} SystemState_t ;

/* 3 */
struct
{
	SystemState_t SystemState;
	struct
	{
		u8 TempData;
		u8 HumiData;
	} SensorData;

	struct
	{
		u8 TempT;
		u8 HumiT;
	} SensorThreshold;

} SFS;



#endif /* APP_H_ */