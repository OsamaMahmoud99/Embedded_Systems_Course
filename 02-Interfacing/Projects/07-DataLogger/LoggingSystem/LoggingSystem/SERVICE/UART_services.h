
#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_

#include "UART_interface.h"






void UART_SendString( u8 *Str);
void UART_SendString_Asynch(u8 *Str);
void UART_SendString_Asynch_NocodeInInt(u8 *Str);


void UART_ReceiveString(u8 *Str); // Receive until #
void UART_ReceiveString_NoBlock(u8 *Str);   // Receive until #
void UART_ReceiveString_Asynch(u8 *Str);


void UART_SendString_MYProtocol(u8*str);
u8 UART_ReceiveString_MyProtocol(u8*str);




#endif /* UART_SERVICES_H_ */
