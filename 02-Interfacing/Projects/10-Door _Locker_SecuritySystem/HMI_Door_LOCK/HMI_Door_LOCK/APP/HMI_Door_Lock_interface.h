/*
 * HMI_Door_Lock_interface.h
 *
 * Created: 4/30/2022 12:59:27 AM
 *  Author: Osama Mahmoud
 */ 


#ifndef HMI_DOOR_LOCK_INTERFACE_H_
#define HMI_DOOR_LOCK_INTERFACE_H_


/*******************************************************************************/
/*                                Important Macros                             */
/*******************************************************************************/

/* Definitions for Hand Shaking Protocol */
#define OPENING_DOOR          			0xF0
#define WRONG_PASSWORD        			0xF1
#define CHANGING_PASSWORD     			0xF2
#define OPEN_DOOR             			'+'
#define CHANGE_PASSWORD       			'-'
#define READY_TO_SEND         			0xF3
#define READY_TO_RECEIVE      			0xF4
#define RECEIVE_DONE          			0xF5
#define SEND_FIRST_PASSWORD   			0xF6
#define SEND_SECOND_PASSWORD 			0xF7
#define SEND_CHECK_PASSWORD   			0xF8

/* Definitions for Password */
#define PASSWORD_LENGTH         		5
#define MAX_NUM_OF_MISTAKES     		3
#define PASS_MIS_MATCHED              	0
#define PASS_MATCHED				  	1

/* Definitions for Time Periods */
#define SEND_RECEIVE_TIME      			10
#define STAND_PRESENTATION_TIME         1500
#define KEYPAD_CLICK_TIME         		500
#define OPEN_DOOR_TIME      			15
#define HOLD_DOOR_TIME       			3
#define CLOSE_DOOR_TIME      			15
#define WARNING_TIME           			60

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 * Function to init the pins of the system and the modules used
 */
void HMI_InitSystem(void);

/*
 * Description:
 * Function to process and update the system 
 */
void HMI_Processing_UpdataSystem(void);

/*
 * Description:
 * Function to set the call back function for the Interrupt to be executed
 */
void HMI_TimerCallBackProcessing(void);

#endif /* HMI_DOOR_LOCK_INTERFACE_H_ */