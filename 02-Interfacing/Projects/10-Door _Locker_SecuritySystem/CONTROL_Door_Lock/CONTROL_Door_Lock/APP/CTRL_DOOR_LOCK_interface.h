/*
 * CTRL_DOOR_LOCK_interface.h
 *
 * Created: 4/29/2022 4:13:26 PM
 *  Author: Osama Mahmoud
 */ 


#ifndef CTRL_DOOR_LOCK_INTERFACE_H_
#define CTRL_DOOR_LOCK_INTERFACE_H_


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
#define OPEN_DOOR_TIME      			15
#define HOLD_DOOR_TIME       			3
#define CLOSE_DOOR_TIME      			15
#define WARNING_TIME           			60
#define STORING_TIME           			80

/* Definitions for TWI */
#define I2C_ADDRESS    0b0000001

/* Definitions for Motor */
#define  MOTOR_SPEED                    128

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 * Function to init the pins of the system and the modules used
 */
void CONTROL_InitSystem(void);

/*
 * Description:
 * Function to process and update the system 
 */
void CONTROL_Processing_UpdataSystem(void);

/*
 * Description:
 * Function to set the call back function for the Interrupt to be executed
 */
void CONTROL_TimerCallBackProcessing(void);

#endif /* CTRL_DOOR_LOCK_INTERFACE_H_ */