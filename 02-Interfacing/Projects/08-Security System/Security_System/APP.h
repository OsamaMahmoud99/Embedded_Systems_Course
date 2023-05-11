/*
 * APP.h
 *
 * Created: 7/15/2021 9:20:13 PM
 *  Author: Osama Mahmoud
 */ 


#ifndef APP_H_
#define APP_H_

#include <util/delay.h>

#include "Switch.h"
#include "LED.h"
#include "SEG_interface.h"

typedef struct {
	u8 LED_Green_Port;
	u8 LED_Green_Pin;
	u8 LED_Yellow_Port;
	u8 LED_Yellow_Pin;
	u8 LED_Red_Port;
	u8 LED_Red_Pin;
	u8 Buzzer_Port;
	u8 Buzzer_Pin;
	}LED_Config;

typedef struct {
	u8 PB_Ones_Port;
	u8 PB_Ones_Pin;
	u8 PB_Tens_Port;
	u8 PB_Tens_Pin;
	u8 PB_Enter_Port;
	u8 PB_Enter_Pin;
	u8 PB_Reset_Port;
	u8 PB_Reset_Pin;
	}PB_Config;
	
	
extern LED_Config LED_PINS_Config[1];	
extern PB_Config PB_PINS_Config[1];

typedef enum {
	NO_PB_PRESSSED,
	ONES_SS,
	TENS_SS,
	ENTER,
	RESET
	}SWITCH_t;
	
typedef enum {
	ONES_ENABLE,
	TENS_ENABLE
	}SS_EN_t;
	

typedef enum {
	PASS,
	WRONG
	}SS_NUM_t;
	
extern int Ones_Count;
extern int Tens_Count;

SWITCH_t PB_CheckPressed(void);
void LED_Init(void);
void LED_On(void);
void LED_Off(void);
void Switch_Init(void);
void SEG_Init(void);
void SEG_Enable_PinDot(u8 Value , SS_EN_t SS_EN);
void SEG_Increment_Ones(void);
void SEG_Increment_Tens(void);
SS_NUM_t SEG_DEF_Password(void);
void Buzzer_On(void);
void Buzzer_Off(void);
void LED_Animation(void);

#endif /* APP_H_ */