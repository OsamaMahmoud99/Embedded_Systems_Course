/*
 * program.h
 *
 *  Created on: Apr 28, 2022
 *      Author: Osama Mahmoud
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#define WITH_ENGINE_TEMP_CONTROLLER        0

typedef enum
{
	ON,
	OFF
}state_t;

state_t Engine_state = OFF;
state_t AC_state = OFF;
state_t Engine_Temp_state = OFF;

float Current_Room_temp;
float Current_Engine_temp;
char Choice;
char Sensor_Reading;
int vehicle_speed = 0;
float Room_temp = 25;
float Engine_temp = 125;


void Get_The_User_Choice(void);
void Check_Sensor_Readings(void);
void Traffic_Light_Data(void);
void Room_Temp_Data(void);
void Engine_Temp_Data(void);
void Vehicle_Speed_30(void);
void Print_States(void);



#endif /* PROGRAM_H_ */
