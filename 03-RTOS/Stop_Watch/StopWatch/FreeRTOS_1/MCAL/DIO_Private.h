/*
 * DIO_Private.h
 *
 * Created: 7/7/2022 10:02:07 PM
 *  Author: Osama
 */ 


#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_



/* DIO_Registers */
#define  PORTA_REG      (*(volatile unsigned char*)0x3B)
#define  DDRA_REG       (*(volatile unsigned char*)0x3A)
#define  PINA_REG       (*(volatile unsigned char*)0x39)

#define  PORTB_REG      (*(volatile unsigned char*)0x38)
#define  DDRB_REG       (*(volatile unsigned char*)0x37)
#define  PINB_REG       (*(volatile unsigned char*)0x36)


#define  PORTC_REG      (*(volatile unsigned char*)0x35)
#define  DDRC_REG       (*(volatile unsigned char*)0x34)
#define  PINC_REG       (*(volatile unsigned char*)0x33)


#define  PORTD_REG      (*(volatile unsigned char*)0x32)
#define  DDRD_REG       (*(volatile unsigned char*)0x31)
#define  PIND_REG       (*(volatile unsigned char*)0x30)
/************************************************************************/



#endif /* DIO_PRIVATE_H_ */