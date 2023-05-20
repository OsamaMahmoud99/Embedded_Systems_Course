#include <stdio.h>
#include <stdlib.h>

//write a program to take even numbers from user and print the sum of them after each entry if the user enters
//2 odd number the program print "bye" and stopped.
int main()
{
    unsigned int num, odd_Flag = 0 , sum = 0;

    while(odd_Flag<2)
    {
        printf("Enter the number: ");
        scanf("%d",&num);

        if(num%2 == 0)
        {
            sum = sum + num;
            odd_Flag = 0;
        }
        else
        {
            odd_Flag = odd_Flag+1;

        }

        printf("sum=%d\n",sum);

    }
    printf("bye");
    return 0;
}
