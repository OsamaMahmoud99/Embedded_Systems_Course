#include <stdio.h>
#include <stdlib.h>

//Write a program to count the number of 1’s in an
//unsigned 32-bit integer.

int main()
{
    unsigned int Num , i , count;

    while(1)
    {
        count = 0;
        printf("Enter the number: ");
        scanf("%d",&Num);

        for(i=0; i<=31; i=i+1)
        {
            if((Num>>i)&1)
            {
                count = count + 1;
            }
        }
        printf("Count of ones is %d \n",count);

    }

    return 0;
}