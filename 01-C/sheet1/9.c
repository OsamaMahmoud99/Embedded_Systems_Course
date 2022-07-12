#include <stdio.h>
#include <stdlib.h>

//Write a program that reads a positive integer and checks if it is a perfect square.
int main()
{
    unsigned int num , i , Flag = 0;

    while(1)
    {
        printf("Enter the number: ");
        scanf("%d",&num);

        Flag = 0;
        for(i=0; i<num&&Flag==0; ++i)
        {
            if((i*i) == num)
            {
                Flag = 1;
            }

        }
        if(Flag==1)
        {
            printf("a perfect square of %d = %d\n",num,i-1);
        }
        else
        {
            printf("No perfect square\n");
        }
    }
    return 0;
}