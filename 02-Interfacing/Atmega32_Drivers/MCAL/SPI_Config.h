/*
 * SPI_Config.h
 *
 * Created: 8/1/2022 9:03:26 AM
 *  Author: Osama
 */ 


#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

#define  Data_Order              LSB
#define  Master_Slave_Select     SPI_Master
#define  OPERATING_LEVEL         SPI_IDLE_LOW
#define  SAMPLING_EDGE           SPI_RISING
#define  CLK_RATE                SPI_FOSC_4
#define  SPI_STATE               SPI_ENABLE
#define  SPI_Double_SPEED        SPI_Double_SPEED_OFF
/********** Data Order**************/
#define  LSB       0
#define  MSB       1
/**********Master/Slave Select********/
#define  SPI_Master    0
#define  SPI_Slave     1
/**********Clock Polarity*************/
#define  SPI_IDLE_LOW   0
#define  SPI_IDLE_HIGH  1
/**********Clock Phase***************/
#define  SPI_RISING     0
#define  SPI_FALLING    1
/**********Clock Rate Select********/
#define  SPI_FOSC_4     0b00
#define  SPI_FOSC_16    0b01
#define  SPI_FOSC_64    0b10
#define  SPI_FOSC_128   0b11
/*********SPI STATE****************/
#define  SPI_ENABLE      0
#define  SPI_DISABLE     1
/**********SPI Double Speed*********/
#define  SPI_Double_SPEED_ON    0
#define  SPI_Double_SPEED_OFF   1


#endif /* SPI_CONFIG_H_ */