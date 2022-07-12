#include <stdio.h>
#include <stdlib.h>

//Write a program that take two numbers and calculate the reminder without using % operation.
int main()
{
    unsigned int num1 , num2 , i = 0;

    while(1)
    {
        printf("Enter the number1: ");
        scanf("%d",&num1);
        printf("Enter the number2: ");
        scanf("%d",&num2);

        i = 0;
        while(num1 >= num2)
        {
            num1 = num1 - num2;
            i = i + 1;
        }
        printf("num1/num2=%d , num1%%num2=%d \n",i,num1);
        printf("\n");

    }
    return 0;
}

