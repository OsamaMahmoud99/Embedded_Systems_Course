///*
 //* I2C_Program.c
 //*
 //* Created: 8/5/2022 10:35:06 AM
 //*  Author: Osama
 //*/ 
//
///*
 //* I2C_program.c
 //*
 //* Created: 4/28/2022 11:31:04 PM
 //*  Author: Osama Mahmoud
 //*/ 
//
//#include "I2C_Interface.h"
//
//void I2C_init(I2C_ConfigType * Config_Ptr)
//{
    ///*
     //* Insert the required Prescaler on TWSR Register
     //* It will occupy the first two bits as the other bits are Read Only
     //*/
	//TWSR = Config_Ptr->prescaler;
//
	///*
	 //* Calculate the division factor for the bit rate generator
	 //* then Insert it on TWBR Register ( It will occupy the whole Register )
	 //*/
	//TWBR = ( ( F_CPU / Config_Ptr->mode ) - 16 ) / ( 2 * ( 4 ^ Config_Ptr->prescaler ) );
	//
    ///*
     //* Insert Two Wire Bus address: my address if any master device want to call me
     //* The address occupy only last 7 Bits So we shift the address one to the left
     //* As General Call Recognition: Off >> TWGCE = 0
     //*/
    //TWAR = (Config_Ptr->slaveAddress) << 1;
	 //
	//SET_BIT(TWCR , TWEN);/* enable I2C */
//}
//
//void I2C_Send_StartCond(void)
//{
	///* save values of TWEN & TWIE and clear other bits */
	//TWCR &= 0x07;
	//
	///* Enable the start bit */
	//SET_BIT(TWCR , TWSTA);
	//
	///*clear the interrupt flag*/
	//SET_BIT(TWCR , TWINT);
    //
	///* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	//while(TWCR &(1<<TWINT) == 0);
 //
//}
//
//void I2C_Send_StopCond(void)
//{
	///* save values of TWEN & TWIE and clear other bits */
	//TWCR &= 0x07;
		//
	///* Enable the stop bit */
	//SET_BIT(TWCR , TWSTO);
		//
	///*clear the interrupt flag*/
	//SET_BIT(TWCR , TWINT);
		//
	///* Wait for TWINT flag set in TWCR Register (stop bit is send successfully) */
	//while(TWCR &(1<<TWINT) == 0);
//}
//
//u8 I2C_getStatus(void)
//{
	//u8 status;
	///* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	//status = TWSR & 0xF8;
	//return status;
//}
//
//void I2C_wirteData(u8 data)
//{
	///* save values of TWEN & TWIE and clear other bits */
	//TWCR &= 0x07;
	//
	//TWDR = data;
	//
	///*clear the interrupt flag I2C start operation*/
	//SET_BIT(TWCR , TWINT);
	//
	///* Wait data to be transmitted */
	//while(TWCR &(1<<TWINT) == 0);
//}
//
//
//u8 I2C_RedDataWithACK(void)
//{
	///* save values of TWEN & TWIE and clear other bits */
	//TWCR &= 0x07;
	//
	//
	//SET_BIT(TWCR , TWINT);
	//SET_BIT(TWCR , TWEA);
	//
	 ///* Wait for TWINT flag set in TWCR Register (data received successfully) */
	 //while(TWCR & (1<<TWINT) == 0);
	//
	 ///* Read Data */
	 //return TWDR;
//}
//
//u8 I2C_ReadDataWithNACK(void)
//{
	///* save values of TWEN & TWIE and clear other bits */
	//TWCR &= 0x07;
		//
		//
	//SET_BIT(TWCR , TWINT);
		//
	///* Wait for TWINT flag set in TWCR Register (data received successfully) */
	//while(TWCR & (1<<TWINT) == 0);
		//
	///* Read Data */
	//return TWDR;
	//
//}
//
//
//
//
