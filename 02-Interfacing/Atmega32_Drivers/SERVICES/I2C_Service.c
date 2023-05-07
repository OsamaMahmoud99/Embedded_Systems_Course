///*
 //* I2C_Service.c
 //*
 //* Created: 8/7/2022 9:21:11 AM
 //*  Author: Osama
 //*/ 
//
//#include "I2C_Service.h"
//
//void I2C_writeByte(u8 SlaveAddress , u8 InternalRegisterAddress , u8 Data)
//{
	////start cond
	////Wait Ack
	//I2C_Send_StartCond();
	//
	//if(I2C_getStatus() != I2C_START){
		////error
	//}
	////SLA + W
	////Wait Ack
	//I2C_wirteData((SlaveAddress<<1)|WRITEMODE);
	//if(I2C_getStatus() != I2C_MT_SLA_W_ACK){
		////error
	//}
	//
	////Register Address
	////Wait Ack
	//I2C_wirteData(InternalRegisterAddress);
	//if(I2C_getStatus() != I2C_MT_DATA_ACK){
		////error
	//}
	//
	////Byte to be written
	////wait Ack
	//I2C_wirteData(Data);
	//if(I2C_getStatus() != I2C_MT_DATA_ACK){
		////error
	//}
	//
	////stop
	//I2C_Send_StopCond();
//
//}
//
//u8 I2C_ReadByte(u8 SlaveAddress , u8 InternalRegisterAddress)
//{
	//u8 DataReceived = 0;
	//
	////send start cond
	//I2C_Send_StartCond();
	//if(I2C_getStatus() != I2C_START){
		//
	//}
	//
	////send SLA+W
	//I2C_wirteData((SlaveAddress<<1)|WRITEMODE);
	//if(I2C_getStatus() != I2C_MT_SLA_W_ACK){
		////error
	//}
	////send internal reg
	//I2C_wirteData(InternalRegisterAddress);
	//if(I2C_getStatus() != I2C_MT_DATA_ACK){
		////error
	//}
	//
	////send rep start
	//I2C_Send_StartCond();
	//if(I2C_getStatus() != I2C_REP_START){
		////error
	//}
	//
	////send SLA + R
	//I2C_wirteData((SlaveAddress<<1)|READMODE);
	//if(I2C_getStatus() != I2C_MT_SLA_R_ACK){
		////error
	//}
	//
	////Read Data with NACK
	//DataReceived = I2C_ReadDataWithNACK();
	//if(I2C_getStatus() != I2C_MR_DATA_NACK){
		////error
	//}
	//
	////send stop cond
	//I2C_Send_StopCond();
	//
	//return DataReceived;
	//
//}
//
//u8 I2C_SendString(u8 SlaveAddress , u8 *str)
//{
	////start cond
	////Wait Ack
	//I2C_Send_StartCond();
	//
	//if(I2C_getStatus() != I2C_START){
		////error
		//return 0;
	//}
	////SLA + W
	////Wait Ack
	//I2C_wirteData((SlaveAddress<<1)|WRITEMODE);
	//if(I2C_getStatus() != I2C_MT_SLA_W_ACK){
		////error
		//return 0;
	//}
	//
	//for (u8 i=0; str[i]; ++i)
	//{
		//I2C_wirteData(str[i]);
		//if(I2C_getStatus() != I2C_MT_DATA_ACK){
		          //return 0;
	    //}
	//}
	//I2C_Send_StopCond();
//}