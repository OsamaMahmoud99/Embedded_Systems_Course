/*
 * HMI_Door_Lock.c
 *
 * Created: 4/30/2022 12:59:01 AM
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
#include "LCD_interface.h"
#include "KEYPAD_interface.h"
#include "HMI_Door_Lock_interface.h"

/*******************************************************************************/
/*                              Global Variables                               */
/*******************************************************************************/

/* Global array to store the password inputed from the user */
u8 g_inputPassword[PASSWORD_LENGTH];

/* Global Variable to store the status of the Password after comparing */
u8 g_matchStatus = PASS_MIS_MATCHED;

/* Global Variable to keep track of the seconds counted by the timer */
volatile u8 g_tick = 0;

/* Global Variable to keep track of how many times the user has inputed the password incorrectly */
u8 g_passwordMistakes = 0;

/* Global Variable to keep track of the command sent from the CONTROL MCU through UART */
u8 g_command;


/********************************************************************************/
/*                              Function Definitions                            */
/********************************************************************************/

/*
 * Description:
 * Function to set the call back function for the Interrupt to be executed
 */
void HMI_TimerCallBackProcessing(void)
{
	g_tick++; /* Increment the counter */
}

/*
 * Description:
 * Function to initialize Timer to operate depending on specific configuration
 * Aim of Timer --> Count the period for specific operations
 */
static void HMI_startTimer(void)
{

	/* Setup Timer Configuration */
	TIMER_ConfigType TIMER_Config = { TIMER1_ID, TIMER_CTC_Mode, 0, F_CPU_1024, 7813 };

	/* Initialize the Timer */
	Timer_init(&TIMER_Config);

	/* Set Call Back function for the timer */
	Timer_setCallBack(HMI_TimerCallBackProcessing, TIMER1_ID);
}

/*
 * Description:
 * Function that takes Password from Keypad
 * and Store it in array for later use
 * and Display asterisk on the screen
 */
static void HMI_getPassword(u8 a_inputPassword[])
{
	u8 password_key = 0;
	
	for(u8 i=0; i<PASSWORD_LENGTH; ++i)
	{
		/* Get the get the key pressed and store it in the password array */
		password_key = KEYPAD_u8GetPressed() - '0';
		
		if((password_key >= 0) && (password_key <= 9)){
			/* Display asterisk for privacy */
			LCD_WriteChar('*');
			a_inputPassword[i] = password_key;
		}
		/* Delay time for keypad press */
		_delay_ms(KEYPAD_CLICK_TIME);
	}
	/* Don't leave until the user press (=) symbol */
	while(KEYPAD_u8GetPressed() != '=');
}

/*
 * Description:
 * Function to send specific commands to the CONTROL MCU through UART
 */
static void HMI_sendCommand(u8 g_command)
{
	/* Inform CTRL MCU that you are to send */
	UART_SendByte(READY_TO_SEND);
	
	/* Wait until CTRL MCU are ready to receive */
	while(UART_ReceiveByte() != READY_TO_RECEIVE);
	
	/* Send the required command to the CTRL MCU */
	UART_SendByte(g_command);
	
	/* Wait until the CTRL MCU receive the command */
	while(UART_ReceiveByte() != RECEIVE_DONE);
}

/*
 * Description:
 * Function that takes Password characters form array
 * and Send that password to the CONTROL MCU through UART
 */
static void HMI_sendPassword(u8 a_inputPassword[])
{
	for(u8 i=0; i<PASSWORD_LENGTH; ++i)
	{
		/*send password to CTRL MCU*/
		UART_SendByte(a_inputPassword[i]);
		/* Delay for the time gap for sending receiving time between the MCUs */
		_delay_ms(SEND_RECEIVE_TIME);
	}
}

/*
 * Description:
 * Function to receive specific command from the CONTROL MCU through UART
 * and Direct the MCU to do predefined set of operations
 */
static u8 HMI_receiveCommand(void)
{
	/* Wait until the CTRL MCU is ready to send */
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
 * Description:
 * Function to set a new Password
 * Use cases:
 * 			 --> Set the Password for the first time
 *      	 --> When user need to change the Password
 */
static void HMI_newPassword(void)
{
	/* Set its status at first as mis-matched */
	g_matchStatus = PASS_MIS_MATCHED;
	
	while(g_matchStatus == PASS_MIS_MATCHED)
	{
		/* Clear Screen */
		LCD_Clear();
		/* Inform the user that he will input new password */
		LCD_WriteSentence(" New Password ");
		/* Hold for Presentation Time */
		_delay_ms(STAND_PRESENTATION_TIME);
		
		/* Clear Screen */
		LCD_Clear();
		/* Prompt the user to input the password for the first time */
		LCD_WriteSentence("Enter password");
		/* Move Cursor to the second line */
		LCD_GoTo(1,0);
		/* Get the password from the user */
		HMI_getPassword(g_inputPassword); 
		/* Inform the CONTROL MCU that you will send the first password */
		HMI_sendCommand(SEND_FIRST_PASSWORD);
		/* Send the password to the CONTROL MCU */
		HMI_sendPassword(g_inputPassword); 
		
		/* Clear Screen */
		LCD_Clear();
		/* Prompt the user to input the password for the second time */
		LCD_WriteSentence("ReEnter password");
		/* Move Cursor to the second line */
		LCD_GoTo(1,0);
		/* Get the password from the user */
		HMI_getPassword(g_inputPassword);
		/* Inform the CONTROL MCU that you will send the first password */
		HMI_sendCommand(SEND_SECOND_PASSWORD);
		/* Send the password to the CONTROL MCU */
		HMI_sendPassword(g_inputPassword);
		
		/* Wait until the is able to send the confirmation of the second password */
		g_matchStatus = HMI_receiveCommand();
		
		if(g_matchStatus == PASS_MIS_MATCHED){
			/* Clear Screen */
			LCD_Clear();
			/* Display an Error Message */
			LCD_WriteSentence("MISMATCH PASS");
			/* Hold for Presentation Time */
			_delay_ms(STAND_PRESENTATION_TIME); 
		}
	}
}

/*
 * Description:
 * Function that displays the main options for our project
 */
static void HMI_mainOptions(void)
{
	/*clear screen*/
	LCD_Clear();
	/* Display the first option */
	LCD_WriteSentence("(+):Open Door");
	/* Move to the next line */
	LCD_GoTo(1 , 0);
	/* Display the second option */
	LCD_WriteSentence("(-):Change Pass");
}

/*
 * Description:
 * Prompt the user to input a password
 */
static void HMI_promptPassword(void)
{
	/*clear screen*/
	LCD_Clear();
	/* Prompt the user to write the password */
	LCD_WriteSentence("Enter password:");
	/* Takes the password and store it in an array */
	/* Move Cursor to the second line */
	LCD_GoTo(1,0);
	/* Get the password from the user */
	HMI_getPassword(g_inputPassword);
}

/*
 * Description:
 * Function that explain door phase on the screen
 */
static void HMI_openingDoor(void)
{
	/* Start the timer to measure time period */
	HMI_startTimer();
	/* Open the door for ( 15 sec ) */
	/*clear screen*/
	LCD_Clear();
	/* Display explanation message on LCD */
	LCD_WriteSentence("Door is opening");
	/* Count up to 15 */
	while(g_tick != OPEN_DOOR_TIME);
	/* Reset counter to reuse it */
	g_tick = 0;
	
	/* Hold the door for ( 3 sec ) */
	/*clear screen*/
	LCD_Clear();
	/* Display explanation message on LCD */
	LCD_WriteSentence("Door is on hold");
	/* Count up to 3 */
	while(g_tick != HOLD_DOOR_TIME);
	/* Reset counter to reuse it */
	g_tick = 0;
	
	/* close the door for ( 15 sec ) */
	/*clear screen*/
	LCD_Clear();
	/* Display explanation message on LCD */
	LCD_WriteSentence("Door is closing");
	/* Count up to 15 */
	while(g_tick != CLOSE_DOOR_TIME); 
	/* Reset counter to reuse it */
	g_tick = 0;
	
	/*stop the timer1*/
	Timer_DeInit(TIMER1_ID);
	/*clear screen*/
	LCD_Clear();
}

/*
 * Description:
 * Function that take care of wrong password scenarios
 */
static void HMI_wrongPassword(void)
{
	/* Increment the wrong counter */
	g_passwordMistakes++; 
	/*clear screen*/
	LCD_Clear();
	/* Display explanation message on LCD */
	LCD_WriteSentence("Wrong Pass");
	/* Hold for Presentation Time */
	_delay_ms(STAND_PRESENTATION_TIME);
	
	/* If the user entered the password 3 times wrong */
	if(g_passwordMistakes == MAX_NUM_OF_MISTAKES)
	{
		/* Start the timer to measure time period */
		HMI_startTimer(); 
		/*clear screen*/
		LCD_Clear();
		/* Display warning message on LCD */
		LCD_WriteSentence("!!! Warning !!!");
		
		/* Display the message for one minute */
		while(g_tick != WARNING_TIME);
		
		/* Reset the counters */
		g_passwordMistakes = 0;
		g_tick = 0;
		/* Stop the timer */	
		Timer_DeInit(TIMER1_ID); 
	}
	/*clear screen*/
	LCD_Clear();
}

void HMI_InitSystem(void)
{
	/*define the pins of lcd and keypad at dio_config.c*/
	DIO_Init();
	
	/*Enable global interrupt*/
	sei();
	
	/*UART configuration*/
	UART_Init();
	
	/*Keypad init*/
	KEYPAD_voidInit();
	
	/*LCD init*/
	LCD_Init();
	
	/*Welcome message*/
	LCD_GoTo(0 , 4);
	LCD_WriteSentence("Welcome");
	LCD_GoTo(1 , 0);
	LCD_WriteSentence("Use (=) as enter");
	_delay_ms(STAND_PRESENTATION_TIME);
	LCD_Clear();
	
	
}

void HMI_Processing_UpdataSystem(void)
{
	u8 key_option;
	
	/* Set the Password for the first time */
	HMI_newPassword();
	
	while(1)
	{
		/* Display the main options to the screen to make the user decide */
		HMI_mainOptions();
		
		/* Store which key has been pressed for later use */
		key_option = KEYPAD_u8GetPressed();
		
		switch(key_option)
		{
			case OPEN_DOOR:
			     /* Ask the user to input a password */
			     HMI_promptPassword();
				 /* Ask CONTROL MCU to check the Password */
				 HMI_sendCommand(SEND_CHECK_PASSWORD);
				 /* Send the inputed password to the CONTROL MCU */
				 HMI_sendPassword(g_inputPassword);
				 /* Inform CONTROL MCU what the user has chosen */
				 HMI_sendCommand(OPEN_DOOR);
				 
				 /* Receive the order command from CONTROL MCU */
				 g_matchStatus = HMI_receiveCommand();
				 
				 /* In case the two passwords matches */
				 if(g_matchStatus == OPENING_DOOR)
				 {
					 /* Begin unLocking and Locking the Door */
					 HMI_openingDoor();
				 }
				 else if(g_matchStatus == WRONG_PASSWORD)
				 {
					 /* Begin wrong operation protocol */
					 HMI_wrongPassword();
				 }
				 break;
				 
			case CHANGE_PASSWORD:
			     /* Ask the user to input a password */
			     HMI_promptPassword();
				 /* Ask CONTROL MCU to check the Password */
				 HMI_sendCommand(SEND_CHECK_PASSWORD);
			     /* Send the inputed password to the CONTROL MCU */
			     HMI_sendPassword(g_inputPassword);
				 /* Inform CONTROL MCU what the user has chosen */
				 HMI_sendCommand(CHANGE_PASSWORD);
				 /* Receive the order command from CONTROL MCU */
				 g_matchStatus = HMI_receiveCommand();
				 /* In case the two passwords matches */
				 if(g_matchStatus == CHANGING_PASSWORD)
				 {
					 /* Set new password for MCU */
					 HMI_newPassword();
				 }
				 else if(g_matchStatus == WRONG_PASSWORD)
				 {
					 /* Begin wrong operation protocol */
					 HMI_wrongPassword();
				 }
				 break;
		}
	}
}