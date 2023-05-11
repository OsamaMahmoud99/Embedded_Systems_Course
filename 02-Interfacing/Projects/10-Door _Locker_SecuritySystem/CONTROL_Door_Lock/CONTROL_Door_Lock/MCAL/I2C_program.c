#define F_CPU             8000000UL
#include "Mem_Map32.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "I2C_interface.h"

void I2C_init(const I2C_ConfigType * Config_Ptr)
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
	
    TWCR = (1<<TWEN); /* enable I2C */
}

void I2C_start(void)
{
    /* 
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    
    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

void I2C_stop(void)
{
    /* 
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void I2C_writeByte(u8 data)
{
    /* Put data On TWI data Register */
    TWDR = data;
    /* 
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

u8 I2C_readByteWithACK(void)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

u8 I2C_readByteWithNACK(void)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

u8 I2C_getStatus(void)
{
    u8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}
