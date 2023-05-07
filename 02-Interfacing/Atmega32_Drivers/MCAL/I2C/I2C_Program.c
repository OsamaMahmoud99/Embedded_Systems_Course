/*
 * I2C_program.c
 *
 * Created: 4/28/2022 11:31:04 PM
 *  Author: Osama Mahmoud
 */ 

#define F_CPU                8000000UL
#include "MemMap.h"
#include "StdTypes.h"
#include "Utils.h"
#include "I2C_interface.h"


#define WRITEMODE       (0x00)
#define READMODE        (0x01)

void I2C_init(I2C_ConfigType * Config_Ptr)
{
    /*
     * Insert the required Prescaler on TWSR Register
     * It will occupy the first two bits as the other bits are Read Only
     */
	TWSR = Config_Ptr->prescaler;

	/*
	 * Calculate the division factor for the bit rate generator
	 * then Insert it on TWBR Register ( It will occupy the whole Register )
	 */
	TWBR = ( ( F_CPU / Config_Ptr->mode ) - 16 ) / ( 2 * ( 4 ^ Config_Ptr->prescaler ) );
	
    /*
     * Insert Two Wire Bus address: my address if any master device want to call me
     * The address occupy only last 7 Bits So we shift the address one to the left
     * As General Call Recognition: Off >> TWGCE = 0
     */
    TWAR = (Config_Ptr->slaveAddress) << 1;
	 
	SET_BIT(TWCR , TWEN);/* enable I2C */
}

static void I2C_Send_StartCond(void)
{
	/* save values of TWEN & TWIE and clear other bits */
	TWCR &= 0x07;
	
	/* Enable the start bit */
	SET_BIT(TWCR , TWSTA);
	
	/*clear the interrupt flag*/
	SET_BIT(TWCR , TWINT);
    
	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while(TWCR &(1<<TWINT) == 0);
 
}

static void I2C_Send_StopCond(void)
{
	/* save values of TWEN & TWIE and clear other bits */
	TWCR &= 0x07;
		
	/* Enable the stop bit */
	SET_BIT(TWCR , TWSTO);
		
	/*clear the interrupt flag*/
	SET_BIT(TWCR , TWINT);
		
	/* Wait for TWINT flag set in TWCR Register (stop bit is send successfully) */
	while(TWCR &(1<<TWINT) == 0);
}

static u8 I2C_getStatus(void)
{
	u8 status;
	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	status = TWSR & 0xF8;
	return status;
}

static void I2C_wirteData(u8 data)
{
	/* save values of TWEN & TWIE and clear other bits */
	TWCR &= 0x07;
	
	TWDR = data;
	
	/*clear the interrupt flag I2C start operation*/
	SET_BIT(TWCR , TWINT);
	
	/* Wait data to be transmitted */
	while(TWCR &(1<<TWINT) == 0);
}

void I2C_writeByte(u8 SlaveAddress , u8 InternalRegisterAddress , u8 Data)
{
	//start cond
	//Wait Ack
	I2C_Send_StartCond();
	
	if(I2C_getStatus() != I2C_START){
		//error
	}
	//SLA + W
	//Wait Ack
	I2C_wirteData((SlaveAddress<<1)|WRITEMODE);
	if(I2C_getStatus() != I2C_MT_SLA_W_ACK){
			//error
	}
	
	//Register Address
	//Wait Ack
	I2C_wirteData(InternalRegisterAddress);
	if(I2C_getStatus() != I2C_MT_DATA_ACK){
		//error
	}
	
	//Byte to be written
	//wait Ack
	I2C_wirteData(Data);
	if(I2C_getStatus() != I2C_MT_DATA_ACK){
		//error
	}
	
	//stop
	I2C_Send_StopCond();

}

static u8 I2C_RedDataWithACK(void)
{
	/* save values of TWEN & TWIE and clear other bits */
	TWCR &= 0x07;
	
	
	SET_BIT(TWCR , TWINT);
	SET_BIT(TWCR , TWEA);
	
	 /* Wait for TWINT flag set in TWCR Register (data received successfully) */
	 while(TWCR & (1<<TWINT) == 0);
	
	 /* Read Data */
	 return TWDR;
}

static u8 I2C_ReadDataWithNACK(void)
{
	/* save values of TWEN & TWIE and clear other bits */
	TWCR &= 0x07;
		
		
	SET_BIT(TWCR , TWINT);
		
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(TWCR & (1<<TWINT) == 0);
		
	/* Read Data */
	return TWDR;
	
}

u8 I2C_ReadByte(u8 SlaveAddress , u8 InternalRegisterAddress)
{
	u8 DataReceived = 0;
	
	//send start cond
	I2C_Send_StartCond();
	if(I2C_getStatus() != I2C_START){
		
	}
	
	//send SLA+W
	I2C_wirteData((SlaveAddress<<1)|WRITEMODE);
	if(I2C_getStatus() != I2C_MT_SLA_W_ACK){
		//error
	}
	//send internal reg
	I2C_wirteData(InternalRegisterAddress);
	if(I2C_getStatus() != I2C_MT_DATA_ACK){
		//error
	}
	
	//send rep start
	I2C_Send_StartCond();
	if(I2C_getStatus() != I2C_REP_START){
		//error
	}
	
	//send SLA + R
	I2C_wirteData((SlaveAddress<<1)|READMODE);
	if(I2C_getStatus() != I2C_MT_SLA_R_ACK){
		//error
	}
	
	//Read Data with NACK
	DataReceived = I2C_ReadDataWithNACK();
	if(I2C_getStatus() != I2C_MR_DATA_NACK){
		//error
	}
	
	//send stop cond
	I2C_Send_StopCond();
	
	return DataReceived;
		
}

