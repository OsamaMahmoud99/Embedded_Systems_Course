/*
 * LoggingSystem.c
 *
 * Created: 8/25/2021 6:59:24 PM
 *  Author: Osama Mahmoud
 */ 

#include "LoggingSystem.h"

void DATALogger_Init(void)
{
	UART_Init();
	EEPROM_Init();
}

void DATALogger_Start(void)
{
	u8 Operation = 0;
	u8 Address[3] = {0};
	u8 Data[3] = {0};
	u8 Sum_Address = 0;
	u8 Sum_Data = 0;
	u8 NumToAscci[5];
	
	UART_SendString("Please Enter W to Write Data to EEPROM or R to Read Data From EEPROM: ");
	UART_SendByte(NEWLINE);
	Operation = UART_ReceiveByte();
	UART_SendByte(NEWLINE);
	switch(Operation)
	{
		case 'W':
		case 'w':
		UART_SendString("Please Provide Address [0 - 127] Followed By Data[0-255] : ");
		
		/* Code to Convert rx String to Number */
		for(int i=0; i<3; ++i){
			Address[i] = UART_ReceiveByte();
		}
		UART_SendByte('-');
		for(int i=0; i<3; ++i){
			Data[i] = UART_ReceiveByte();
		}
		UART_SendByte(NEWLINE);
		
		Sum_Address = (Address[0]-'0')*100+(Address[1]-'0')*10+(Address[2]-'0');
		Sum_Data    = (Data[0]-'0')*100+(Data[1]-'0')*10+(Data[2]-'0');
		EEPROM_WriteByte(Sum_Data,Sum_Address);
		UART_SendString("Write Operation Done :: ");
		UART_SendByte(NEWLINE);
		break;
		case 'R':
		case 'r':
		UART_SendString("Please Provide Address [0 - 127]: ");
		for(int i=0; i<3; ++i){
			Address[i] = UART_ReceiveByte();
		}
		UART_SendByte(NEWLINE);
		Sum_Address = (Address[0]-'0')*100+(Address[1]-'0')*10+(Address[2]-'0');
		Sum_Data = EEPROM_ReadByte(Sum_Address);
		
		/* Code to Convert Number to ASCII Before Printing */
		UART_SendString("Address has Data of :  ");
		sprintf(NumToAscci, "%d",Sum_Data);
		UART_SendString(NumToAscci);
		UART_SendByte(NEWLINE);
		break;
		default:
		UART_SendString("Wrong Input Please Try Again ::");
		UART_SendByte(NEWLINE);
		break;
	}
}
