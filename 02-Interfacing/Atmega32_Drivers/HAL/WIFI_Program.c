///*
 //* WIFI_Program.c
 //*
 //* Created: 11/24/2022 5:22:13 PM
 //*  Author: Osama
 //*/ 
//
//#include "WIFI_Interface.h"
//
//char Closing[]	 = "\r\n"	;
//
//u8 Local_u8Response[100];
	//
//static u8 u8ValidateCmd(u32 Copy_u32timeout)
//{
	//u8 Local_u8ValidFlag = 0;
	//u8 Counter = 0;
	//u8 Temp_char = 0;
//
	//for(u8 i = 0; i < 100; i++)
	//{
		//Local_u8Response[i] = 0;
	//}
//
	///*Make sure that the MC is not receiving any more data from the ESP*/
	//while (Temp_char != 255)
	//{
		//Temp_char = USART_Receive_timeout(Copy_u32timeout);
		//Local_u8Response[Counter] = Temp_char;
		//Counter++;
	//}
//
	///*	Deleting last element as it is always 255 for stop receiving data	*/
	//Local_u8Response[Counter-1] = 0;
//
//
	//for(u8 i = 0; i < 100; i ++)
	//{
		//if(Local_u8Response[i] == 'O' && Local_u8Response[i+1] == 'K')
		//{
			//Local_u8ValidFlag = 1;
			//break;
		//}
//
	//}
	//return Local_u8ValidFlag;
//}
//void HESP_voidInit(void)
//{
	//u8 Local_u8ValidFlag = 0;
//
	//while(Local_u8ValidFlag == 0)
	//{
		///*Stop Echo*/
		//UART_SendString("ATE0\r\n");
		///*	Check command is done right
			//ATE0 returns OK if all is okay*/
		//Local_u8ValidFlag = u8ValidateCmd(ECHO_TIMEOUT);
	//}
	//
	//Local_u8ValidFlag = 0;
	//
	//while(Local_u8ValidFlag == 0)
	//{
		///*Set ESP station mode*/
		//UART_SendString("AT+CWMODE=1\r\n");
		///*	Check command is done right
			//AT+CWMODE=1 returns OK if all is okay*/
		//Local_u8ValidFlag = u8ValidateCmd(MODE_TIMEOUT);
	//}
//}
//void HESP_voidConnctToRouter(u8* Copy_u8StrSsid, u8* Copy_u8StrPassword)
//{
	//u8 Local_u8ValidFlag = 0;
	//char Router_Command[50];
	//
	//sprintf(Router_Command,"%s%s%s%s%s","AT+CWJAP_CUR=\"",Copy_u8StrSsid,"\",\"",Copy_u8StrPassword,"\"\r\n");
	//
	//while(Local_u8ValidFlag == 0)
	//{
		///*Connect to WiFi of name Copy_u8StrSsid and password Copy_u8StrPassword*/
		//UART_SendString(Router_Command);
		///*	Check command is done right
			//AT+CWJAP_CUR="SSID","Pass" returns OK if all is okay*/
		//Local_u8ValidFlag = u8ValidateCmd(ROUTER_TIMEOUT);
	//}
//}
//void HESP_voidConnectToServer( u8* Copy_u8StrIP, u8* Copy_u8StrPort)
//{
	//u8 Local_u8ValidFlag = 0;
	//char Server_Command[42];
//
	//
	//sprintf(Server_Command,"%s%s%s%s%s","AT+CIPSTART=\"TCP\",\"", Copy_u8StrIP,"\",",Copy_u8StrPort,"\r\n");
	//while(Local_u8ValidFlag == 0)
	//{
		///*	Connect to Server of IP Copy_u8StrIP with Copy_u8StrMode potocol
			//Either TCP or UDP and on Port Copy_u8StrPort*/
		//UART_SendString(Server_Command);
		///*	Check command is done right
			//AT+CIPSTART="MODE","IP",PORT returns OK if all is okay*/
		//Local_u8ValidFlag = u8ValidateCmd(SERVER_TIMEOUT);
	//}
//}
//u8 * HESP_u8ExecuteRequest(u8* Copy_u8StrRequest , u8 Cpy_u8CommandSize , u16 Cpy_u16LineNum)
//{
	//
//}

