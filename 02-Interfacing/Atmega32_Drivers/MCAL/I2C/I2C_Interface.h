/*
 * I2C_interface.h
 *
 * Created: 4/28/2022 11:27:55 PM
 *  Author: Osama Mahmoud
 */ 


#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define I2C_START         0x08 /* start has been sent */
#define I2C_REP_START     0x10 /* repeated start */
#define I2C_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define I2C_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define I2C_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define I2C_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define I2C_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	NormalMode_100Kb = 100000,
	FastMode_400Kb = 400000,
	FastModePlus_1Mb = 1000000,
	HighSpeedMode_3Mb = 3400000
}SCL_Frquency;

typedef enum
{
	Prescaler_1 ,
    Prescaler_4 , 
	Prescaler_16 ,
	Prescaler_64
	
}I2C_Prescaler;

typedef struct
{
	SCL_Frquency mode;
	I2C_Prescaler prescaler;
	u8 slaveAddress;
}I2C_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void I2C_init(I2C_ConfigType * Config_Ptr);
void I2C_writeByte(u8 SlaveAddress , u8 InternalRegisterAddress , u8 Data);
u8 I2C_ReadByte(u8 SlaveAddress , u8 InternalRegisterAddress);


#endif /* I2C_INTERFACE_H_ */