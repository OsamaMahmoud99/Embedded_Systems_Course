#include <stdio.h>
#include <stdlib.h>

//Write a program that reads the radius of a circle and calculates the area and circumference.

int main()
{
    float Radius;
    float Area , Circumference;

    printf("Enter radius of circle : ");
    scanf("%f",&Radius);

    Area = 3.14 * Radius * Radius;
    Circumference = 2 * 3.14 * Radius;

    printf("Area = %0.3f\nCircum = %0.3f",Area , Circumference);

    while(1)
    {

    }
    return 0;
}