/*
 * program.c
 *
 *  Created on: Apr 28, 2022
 *      Author: Osama Mahmoud
 */


#include <stdio.h>
#include "program.h"


int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	Get_The_User_Choice();

	return 0;
}



void Get_The_User_Choice(void)
{
	printf("choose one of the following:\n");

	printf("a.Turn on the vehicle engine\n");
	printf("b.Turn off the vehicle engine\n");
	printf("c.Quit the system\n");

	printf("Enter your choice:\n");
	scanf(" %c",&Choice);

	switch(Choice)
	{
	case 'c':
		printf("\n Quit System\n");
		return;
		break;
	case 'b':
		while(Choice == 'b'){
			Get_The_User_Choice();
		}
		break;
	case 'a':
		Engine_state = ON;
		printf("\nthe vehicle engine is on\n");
		while(Engine_state == ON){
			Check_Sensor_Readings();

			if(Choice == 'a'){
				Print_States();
			}
		}

		break;
	default:
		printf("wrong choice\n");
		Get_The_User_Choice();
		break;
	}
}
void Check_Sensor_Readings(void)
{
	printf("\n********************\n");
	printf("a.Turn off engine\n");
	printf("b.Set traffic light color\n");
	printf("c.Set room temperature\n");
	printf("d.Set engine temperature\n");

	printf("Sensor reading:\n");
	scanf(" %c",&Sensor_Reading);

	switch(Sensor_Reading)
	{
	case 'a':
		Engine_state = OFF;
		Choice = 'b';
		printf("\n");
		Get_The_User_Choice();
		break;

	case 'b':
		Traffic_Light_Data();
		if(vehicle_speed == 30){
			Vehicle_Speed_30();
			return;
		}
		break;

	case 'c':
		if(vehicle_speed == 30){
			Vehicle_Speed_30();
			return;
		}
		Room_Temp_Data();
		break;

#if WITH_ENGINE_TEMP_CONTROLLER == 1
	case 'd':
		if(vehicle_speed == 30){
			Vehicle_Speed_30();
			return;
		}
		Engine_Temp_Data();
		break;
#endif
	default:
		Check_Sensor_Readings();
		break;
	}
}
void Traffic_Light_Data(void)
{
	char traffic_light_data;
	printf("\nEnter the traffic light data\n");
	scanf(" %c",&traffic_light_data);

	switch(traffic_light_data)
	{
	case 'G':
		vehicle_speed = 100;
		break;

	case 'O':
		vehicle_speed = 30;
		break;

	case 'R':
		vehicle_speed = 0;
		break;

	default:
		break;
	}

}
void Room_Temp_Data(void)
{
	printf("\nEnter the current room temperature:\n");
	scanf("%f",&Current_Room_temp);

	if(Current_Room_temp < 10 || Current_Room_temp > 30){
		AC_state = ON;
		Room_temp = 20;
	}
	else{
		AC_state = OFF;
	}
}
void Engine_Temp_Data(void)
{
	printf("\nEnter the current Engine temperature:\n");
	scanf("%f",&Current_Engine_temp);

	if(Current_Engine_temp < 100 || Current_Engine_temp > 150){
		Engine_Temp_state = ON;
		Engine_temp = 125;
	}
	else{
		Engine_Temp_state = OFF;
	}
}
void Vehicle_Speed_30(void)
{
	Room_Temp_Data();

	if(AC_state == OFF){
		AC_state = ON;
	}
	Room_temp = ((Current_Room_temp)*(5/4))+1;

	printf("\n");

	Engine_Temp_Data();

	if(Engine_Temp_state == OFF){
		Engine_Temp_state = ON;
	}
	Engine_temp = ((Current_Engine_temp)*(5/4))+1;

}
void Print_States(void)
{
	printf("\nCurrent vehicle states\n");
	printf("**********************\n");

	printf("Engine state: ");
	Engine_state == ON ? printf("ON\n") : printf("OFF\n");

	printf("AC state: ");
	AC_state == ON ? printf("ON\n") : printf("OFF\n");

	printf("vehicle speed: %d KM/Hr\n",vehicle_speed);
	printf("Room temp: %.3f C\n",Room_temp);

#if WITH_ENGINE_TEMP_CONTROLLER == 1
	printf("Engine controller state: ");
	Engine_Temp_state == ON ? printf("ON\n") : printf("OFF\n");

	printf("Engine Temperature: %.3f C\n",Engine_temp);
#endif
}
