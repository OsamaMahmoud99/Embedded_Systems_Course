/*
 * RGB_Program.c
 *
 * Created: 7/26/2022 7:22:47 PM
 *  Author: Osama
 */ 

#include "RGB_Interface.h"


static u8 Arr[NUMColors][3] = {{255 , 0 , 0},     // Red
	                           {0 , 255 , 0},     // Green
				               {0 , 0 , 255},     // Blue
				               {255 , 255 , 0},   //Yellow
				               {0 , 255 , 255},   //Cyan
				               {255 , 0 , 255},   //Magenta
				               {0 , 0 , 0},       //Black
				               {255 , 255 , 255}, //white
						       {128 , 128 ,128},  //Gray
						       {128 , 0 , 128}};  //Purple
							


void RGB_SetDuty(Color_t color)
{
	OCR1A = Arr[color][R];
	OCR1B = Arr[color][G];
	OCR0  = Arr[color][B];
}

