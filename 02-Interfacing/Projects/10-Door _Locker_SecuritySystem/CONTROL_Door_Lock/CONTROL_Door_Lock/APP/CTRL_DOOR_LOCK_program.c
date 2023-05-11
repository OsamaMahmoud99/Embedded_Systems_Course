/*
 * CTR_DOOR_LOCK_program.c
 *
 * Created: 4/29/2022 4:12:57 PM
 *  Author: Osama Mahmoud
 */ 


/*******************************************************************************/
/*                              Includes                                       */
/*******************************************************************************/
#include "Mem_Map32.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#include "DIO_interface.h"
#include "UART_interface.h"
#include "TIMER_interface.h"
#include "PWM_interface.h"
#include "I2C_interface.h"
#include "external_eeprom.h"
#include "BUZZER_interface.h"
#include "MOTOR_interface.h"
#include "CTRL_DOOR_LOCK_interface.h"

/********************************************************************************/
/*                              Global Variables                                */
/********************************************************************************/

/* Global array to store the password saved in the external EEPROM */
u8 g_storedPassword[PASSWORD_LENGTH];

/* Global array to store the first password inputed from the user */
u8 g_receivedPassword[PASSWORD_LENGTH];

/* Global array to store the second password inputed from the user */
u8 g_confirmPassword[PASSWORD_LENGTH];

/* Global Variable to store the status of the Password after comparing */
u8 g_matchStatus;

/* Global Variable to keep track of the seconds counted by the timer */
volatile u8 g_tick;

/* Global Variable to keep track of how many times the user has inputed the password incorrectly */
u8 g_passwordMistakes;

/* Global Variable to keep track of the command sent from the CONTROL MCU through UART */
u8 g_command;


/********************************************************************************/
/*                              Function Definitions                            */
/********************************************************************************/

/*
 * Description:
 * Function to set the call back function for the Interrupt to be executed
 */
void CONTROL_TimerCallBackProcessing(void)
{
	/* Increment the counter */
	g_tick++; 
} 

/*
 * Description:
 * Function to initialize Timer to operate depending on specific configuration
 * Aim of Timer --> Count the period for specific operations
 */
static void CONTROL_startTimer(void)
{
	/*Timer1_Init(TIMER1_CTC_OCRA_TOP_MODE , TIMER1_SCALER_1024 , OCRA_DISCONNECTED , OCRB_DISCONNECTED);
	
	TCNT1 = 0;
	OCR1A = 7813;
	Timer1_OCA_InterruptEnable();
	Timer1_OCA_SetCallBack(CONTROL_TimerCallBackProcessing);*/
	/* Setup Timer Configuration */
	TIMER_ConfigType TIMER_Config = { TIMER1_ID, TIMER_CTC_Mode, 0, F_CPU_1024, 7813 };

	/* Initialize the Timer */
	Timer_init(&TIMER_Config);

	/* Set Call Back function for the timer */
	Timer_setCallBack(CONTROL_TimerCallBackProcessing, TIMER1_ID);
}

/*
 * Description :
 * Function that save the matched password in external EEPROM
 */
static void CONTROL_savePassword(u8 a_receivedPassword[])
{
	for(u8 i=0; i<PASSWORD_LENGTH; ++i){
		
		/* Save each element of the password in external EEPROM */
		EEPROM_writeByte((0x0311+i) , a_receivedPassword[i]);
		
		/* Delay for the time gap for storing data in EEPROM */
		_delay_ms(STORING_TIME);
	}
}

/*
 * Description:
 * Function to receive specific command from the HMI MCU through UART
 * and Direct the MCU to do predefined set of operations
 */
static u8 CONTROL_receiveCommand(void)
{
	/* Wait until the HMI MCU is ready to send */
	while(UART_ReceiveByte() != READY_TO_SEND);
	
	/* Inform the HMI MCU that you are ready to receive */
	UART_SendByte(READY_TO_RECEIVE);
	
	/* Receive the command from the CONTROL MCU */
	g_command = UART_ReceiveByte();
	
	/* Inform the HMI MCU that the receive has been done successfully */
	UART_SendByte(RECEIVE_DONE);
	
	return g_command;
}

/*
 * Description :
 * Takes the Password which received from UART
 * and Store it in an array for later use
 */
static void CONTROL_receivePassword(u8 a_Password[])
{
	for(u8 i=0; i<PASSWORD_LENGTH; ++i){
		
		/* Receive Password from HMI MCU */
		a_Password[i] = UART_ReceiveByte();
		/* Delay for the time gap for sending receiving time between the MCUs */
		_delay_ms(SEND_RECEIVE_TIME);
	}
}

/*
 * Description :
 * Function to compare two passwords received from HMI MCU
 * and return the match status between them
 */
static u8 CONTROL_comparePasswords(u8 a_password1[], u8 a_password2[])
{
	u8 flag = 0;
	g_matchStatus = PASS_MATCHED;
	
	for(u8 i=0; (i<PASSWORD_LENGTH) && (flag==0); ++i){
		if(a_password1[i] != a_password2[i]){
			g_matchStatus = PASS_MIS_MATCHED;
			flag = 1;
		}
	}	
	return g_matchStatus;
}

/*
 * Description:
 * Function to send specific commands to the HMI MCU through UART
 */
static void CONTROL_sendCommand(u8 g_command)
{
	/* Inform HMI MCU that you are to send */
	UART_SendByte(READY_TO_SEND);
	
	/* Wait until HMI MCU are ready to receive */
	while(UART_ReceiveByte() != READY_TO_RECEIVE);
	
	/* Send the required command to the HMI MCU */
	UART_SendByte(g_command);
	
	/* Wait until the HMI MCU receive the command */
	while(UART_ReceiveByte() != RECEIVE_DONE);
}

/*
 * Description:
 * Function to set a new Password
 * Use cases:
 * 			 --> Set the Password for the first time
 *      	 --> When user need to change the Password
 */
static void CONTROL_newPassword(void)
{
	g_matchStatus = PASS_MIS_MATCHED;
	
	while(g_matchStatus == PASS_MIS_MATCHED)
	{
		/*wait until the HMI MCU send command for first password*/
		while(CONTROL_receiveCommand() != SEND_FIRST_PASSWORD);
		/*Receive the first password from HMI MCU*/
		CONTROL_receivePassword(g_receivedPassword);
		
		/*wait until the HMI MCU send command for second password*/
		while(CONTROL_receiveCommand() != SEND_SECOND_PASSWORD);
		/*Receive the second password from HMI MCU*/
		CONTROL_receivePassword(g_confirmPassword);
		
		/*compare the two received password*/
		g_matchStatus = CONTROL_comparePasswords(g_receivedPassword , g_confirmPassword);
		
		if(g_matchStatus == PASS_MIS_MATCHED)
		{
			/*send command informing that the passwords mis-matched*/
			CONTROL_sendCommand(PASS_MIS_MATCHED);
		}
		else if (g_matchStatus == PASS_MATCHED)
		{
			CONTROL_savePassword(g_receivedPassword);
			/*send command informing that the passwords matched*/
			CONTROL_sendCommand(PASS_MATCHED);
		}
	}
}





/*
 * Description :
 * Load the Password from EEPROM
 * and Store it in an array
 */
static void CONTROL_readPassword(u8 a_storedPassword[])
{
	for(u8 i=0; i<PASSWORD_LENGTH; ++i){
			
		/* Save each element of the password in external EEPROM */
		EEPROM_readByte((0x0311+i) , &a_storedPassword[i]);
			
		/* Delay for the time gap for storing data in EEPROM */
		_delay_ms(STORING_TIME);
	}
}

/*
 * Description:
 * Function that rotates the DC Motor
 */
static void CONTROL_openingDoor(void)
{
	/* Start the Timer */
	CONTROL_startTimer(); 
	
	/*
	 * Do Open Door Task:
	 * 					--> Rotate the DC Motor
	 * 					--> Clock Wise
	 * 					--> 15 seconds
	 */
	UpdateMotor(MOTOR_SPEED , MOTOR_MAIN_DIR);
	/* Count up to 15 */
	while(g_tick != OPEN_DOOR_TIME);
	/* Reset counter to reuse it */ 
	g_tick = 0; 
	
	/*
	 * Do Hold Task:
	 * 			   --> Stop the DC Motor
	 */
	UpdateMotor(MOTOR_SPEED , MOTOR_STOP);
	/* Count up to 15 */
	while(g_tick != HOLD_DOOR_TIME);
	/* Reset counter to reuse it */ 
	g_tick = 0;
	
	/*
	 * Do Close Door Task:
	 * 					 --> Rotate the DC Motor
	 * 					 --> Anti Clock Wise
	 * 					 --> 15 seconds
	 */
	UpdateMotor(MOTOR_SPEED , MOTOR_OTHER_DIR);
	/* Count up to 15 */
	while(g_tick != CLOSE_DOOR_TIME);
	/* Reset counter to reuse it */
	g_tick = 0;
	
	/*stop motor*/
	UpdateMotor(MOTOR_SPEED , MOTOR_STOP);
	
	/* Stop the timer */
	Timer_DeInit(TIMER1_ID);
}

/*
 * Description:
 * Function that take care of wrong password scenarios
 */
static void CONTROL_wrongPassword(void)
{
	/* Increment the wrong counter */
	g_passwordMistakes++; 
	
	if(g_passwordMistakes == MAX_NUM_OF_MISTAKES)
	{
		/* Start the timer to measure time period */
		CONTROL_startTimer();
		
		/* Turn on the buzzer */
		Buzzer_On();
		/* Count up to 15 */
		while(g_tick != WARNING_TIME);
		/* Reset the counters */
		g_tick = 0;
		g_passwordMistakes = 0;
		
		/*stop timer*/
		Timer_DeInit(TIMER1_ID);
	}
	
	/* Turn off the buzzer */
	Buzzer_Off();
}

/**************************************************************************************************************************/

void CONTROL_InitSystem(void)
{
	/* Set the pins of the system as output or input */
	DIO_Init();
	
	/*Enable global interrupt*/
	sei();
	
	/*UART configuration*/
	UART_Init();
	
	/*I2C struct*/
	//I2C_ConfigType I2C_config = {NormalMode_100Kb , Prescaler_1 , I2C_ADDRESS};
	//I2C_init(&I2C_config);
	
	/* Initialize TWI with Configuration */
	I2C_ConfigType TWI_Config = {FastMode_400Kb, Prescaler_1, TWI_ADDRESS};
	I2C_init(&TWI_Config);
	
	/*Init DC Motor*/
	InitMotor();
	
}

void CONTROL_Processing_UpdataSystem(void)
{
	u8 key_option;
	
	CONTROL_newPassword();
	
	while(1)
	{
		while(CONTROL_receiveCommand() != SEND_CHECK_PASSWORD);
		/* Receive the inputed password and store it */
		CONTROL_receivePassword(g_receivedPassword);
		/* Receive the command from the HMI MCU */
		key_option = CONTROL_receiveCommand();
		
		switch(key_option)
		{
			case OPEN_DOOR:
			     /* Read Password from the EEPROM */
			     CONTROL_readPassword(g_storedPassword);
				 /* Compare it with the inputed user */
				 g_matchStatus = CONTROL_comparePasswords(g_receivedPassword, g_storedPassword);
				 
				 if(g_matchStatus == PASS_MATCHED){
					 /* Send Opening Door command to HMI MCU */
					 CONTROL_sendCommand(OPEN_DOOR);
					 /* Start Opening Door sequence */
					 CONTROL_openingDoor();
				 }
				 else if (g_matchStatus == PASS_MIS_MATCHED){
					 /* Send Wrong Password command to HMI MCU */
					 CONTROL_sendCommand(WRONG_PASSWORD);
					 /* Start Wrong Password sequence */
					 CONTROL_wrongPassword();
				 }
				 break;
				 
			case CHANGE_PASSWORD: 
				 /* Read Password from the EEPROM */
				 CONTROL_readPassword(g_storedPassword);
				 /* Compare it with the inputed user */
				 g_matchStatus = CONTROL_comparePasswords(g_receivedPassword, g_storedPassword);
				 
				 if(g_matchStatus == PASS_MATCHED){
					 /* Send Opening Door command to HMI MCU */
					 CONTROL_sendCommand(CHANGING_PASSWORD);
					 /* Start new password sequence */
					 CONTROL_newPassword();
				 }
				 else if (g_matchStatus == PASS_MIS_MATCHED){
					 /* Send Wrong Password command to HMI MCU */
					 CONTROL_sendCommand(WRONG_PASSWORD);
					 /* Start Wrong Password sequence */
					 CONTROL_wrongPassword();
				 }
				 break;  /* End of change password case */
		}	/* End switch case */
	} /* End Super Loop */
}

