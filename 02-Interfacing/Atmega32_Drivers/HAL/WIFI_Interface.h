///*
 //* WIFI_Interface.h
 //*
 //* Created: 11/24/2022 5:21:56 PM
 //*  Author: Osama
 //*/ 
//
//
//#ifndef WIFI_INTERFACE_H_
//#define WIFI_INTERFACE_H_
//
//#include "UART_Interface.h"
//#include "UART_Service.h"
//
///*define recieving timout for each command that if it exceeded it means no more data*/
///*It varies depending on the router and server and also Clock freq, you'll need to try it*/
//#define ECHO_TIMEOUT		100
//#define MODE_TIMEOUT		150
//#define ROUTER_TIMEOUT		1100000
//#define SERVER_TIMEOUT		300000
//#define PREREQUEST_TIMEOUT	200
//#define REQUEST_TIMEOUT		900000
//
//void HESP_voidInit(void);
//void HESP_voidConnctToRouter(u8* Copy_u8StrSsid, u8* Copy_u8StrPassword);
//void HESP_voidConnectToServer(u8* Copy_u8StrIP, u8* Copy_u8StrPort);
//u8 * HESP_u8ExecuteRequest(u8* Copy_u8StrRequest , u8 Cpy_u8CommandSize , u16 Cpy_u16LineNum);
//
//
//
//
//#endif /* WIFI_INTERFACE_H_ */