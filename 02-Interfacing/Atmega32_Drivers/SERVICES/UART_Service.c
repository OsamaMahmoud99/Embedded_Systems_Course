/*
 * UART_Service.c
 *
 * Created: 7/28/2022 4:19:21 PM
 *  Author: Osama
 */ 

#include "UART_Service.h"
#include "LCD_Interface.h"
void UART_SendString(u8 *pstr)
{
	while(*pstr != 0)
	{
		UART_SendByte(*pstr);
		pstr++;
	}
}

void UART_ReceiveString(u8 *pstr)
{
	u8 i = 0;
	pstr[i] = UART_ReceiveByte();
	
	while(pstr[i] != 0x0d)
	{
		i++;
		pstr[i] = UART_ReceiveByte();
	}
	pstr[i] = '\0';
}

void UART_SendNumber(u32 num)
{
	UART_SendByte((u8)num);
	UART_SendByte((u8)(num>>8));
	UART_SendByte((u8)(num>>16));
	UART_SendByte((u8)(num>>24));
}
void UART_SendNumber2(u32 num)
{
	u8 *p = &num;
	UART_SendByte(*p);
	UART_SendByte(*(p+1));
	UART_SendByte(*(p+2));
	UART_SendByte(*(p+3));
}

u32 UART_RecieveNumber(void)
{
	u32 num = UART_ReceiveByte();
	
	num |= ((u32)UART_ReceiveByte()<<8);
	num |= ((u32)UART_ReceiveByte()<<16);
	num |= ((u32)UART_ReceiveByte()<<24);
	
	return num;
}

u32 UART_RecieveNumber2(void)
{
	u32 num , Sum;
	u8 *p = &num;
	p[0] = UART_ReceiveByte();
	p[1] = UART_ReceiveByte();
	p[2] = UART_ReceiveByte();
	p[3] = UART_ReceiveByte();
	
	return num;
}

void UART_SendStringCheckSum(u8 *str)
{
	u8 len=0 , i;
	u16 sum=0;
	for(len=0; str[len]; ++len);
	UART_SendByte(len);
	
	for (i=0; i<len; ++i)
	{
		UART_SendByte(str[i]);
		sum = sum + str[i];
	}
	UART_SendByte((u8)sum);
	UART_SendByte((u8)(sum>>8));
}

u8 UART_ReceiveStringCheckSum(u8 *str)
{
	u8 len , i;
	u16 rec_sum=0 , send_sum = 0;
	u8 *psum = &send_sum;
	len = UART_ReceiveByte();
	
	for (i=0; i<len; ++i)
	{
		str[i] = UART_ReceiveByte();
		rec_sum = rec_sum + str[i];
	}
	
	psum[0] = UART_ReceiveByte();
	psum[1] = UART_ReceiveByte();
	str[i] = 0;
	if (rec_sum == send_sum)
	{
		return 1;
	}
	return 0;
}

/*********************************** Send Async ***************************************/
static void Send_Int_Function(void);
static void Receive_Int_Function(void);
static u8  *Asynch_Send_Str;
static u8  *Asynch_receive_str;

void UART_SendString_Asynch(u8 *Str)
{
	Asynch_Send_Str=Str;
	UART_SendByte(Str[0]);

	UART_TX_SetCallBack(Send_Int_Function);
	UART_TX_InterruptEnable();
}

static void Send_Int_Function(void)
{
	static u8 i=1;
	if(Asynch_Send_Str[i] !='\0')
	{
		UART_SendByteNoBlock(Asynch_Send_Str[i]);
		i++;
	}
	else
	{
		i=1;
		UART_TX_InterruptDisable();
	}
}

/*********************************** Receive Async ***************************************/

void UART_ReceiveString_Asynch(u8 *Str)
{
	UART_RX_SetCallBack(Receive_Int_Function);
	UART_RX_InterruptEnable();
	Asynch_receive_str=Str;
}

static void Receive_Int_Function(void)
{
	static u8 i=0;

 
	Asynch_receive_str[i] = UART_ReceiveByteNoBlock();
	if (Asynch_receive_str[i] != 0x0d)
	{
		 i++;
    }
	else
	{

		Asynch_receive_str[i] = 0;
		i = 0;
	}
}

/************************************* queue Asynchronous functions *****************************/
static void Func_TX(void);
static void Func_RX(void);

static u8 *TX_str[20]={0};
static u8 *RX_str[20]={0};

static u8 TX_j = 0;
static u8 RX_j = 0;
void UART_SendStringAsynch(u8 *pstr)
{
	if (TX_j == 0)
	{
		UART_SendByte(pstr[0]);
	}
	TX_str[TX_j] = pstr;
	TX_j++;

	UART_TX_SetCallBack(Func_TX);
	UART_TX_InterruptEnable();
	
}

static void Func_TX(void)
{
	static u8 i = 1 , k=0;
	u8 j = TX_j-1;
	if (TX_str[k][i] != 0)
	{
		UART_SendByteNoBlock(TX_str[k][i]);
		i++;
	}
	else
	{
		i = 1;
		k++;
			LCD_GoTo(1 , 0);
			LCD_WriteNumber(k);
	    /*if (j > 0 )
	    {
			j--;
			UART_SendByte(TX_str[1][0]);	
	    }*/
		
	}
}


void UART_ReceiveStringAsynch(u8 *pstr)
{
	UART_RX_SetCallBack(Func_RX);
	UART_RX_InterruptEnable();
	RX_str[RX_j] = pstr;
	RX_j++;
}

static void Func_RX(void)
{
	static u8 i = 0 , k=0;
	if (RX_str[k][i] != 0x0d)
	{
		RX_str[k][i] = UART_ReceiveByteNoBlock();	
		i++;
	}
	else
	{
		RX_str[k][i]=0;
		k++;
		i=0;
	}
}

/*************************** Basic comm module ******************************/

static void Func_TX2(void);
static volatile u8 flag = 0;
void UART_BCM_Init(void)
{
	UART_TX_SetCallBack(Func_TX2);
	UART_TX_InterruptEnable();
	
}
void UART_BCM_Runnable(u8 *pstr)
{
	static u8 i = 1;
    static u8 first_run = 0;
	if (first_run == 0)
	{
		UART_SendByte(pstr[0]);
		first_run = 1;
	}
	
	if (flag == 1)
	{
		if (pstr[i] != 0)
		{
			UART_SendByteNoBlock(pstr[i]);
			i++;
			flag = 0;
		}
		else
		{
			i = 1;
			first_run = 0;
		}
	}
}

static void Func_TX2(void)
{
	flag = 1;
}