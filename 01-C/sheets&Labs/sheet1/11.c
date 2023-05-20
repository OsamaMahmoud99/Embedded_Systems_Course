#include <stdio.h>
#include <stdlib.h>

//Write a program to sum the digits in a decimal number 145 -> 1+4+5=10
int main()
{
    unsigned int num , digit , sum = 0;

    while(1)
    {
        printf("Enter the number: ");
        scanf("%d",&num);

        sum = 0;
        while(num > 0)
        {
            digit = num%10;
            sum = sum + digit;
            num = num / 10;
        }

        printf("sum of digits = %d\n",sum);
    }
    return 0;
}
