#include <stdio.h>
#include <stdlib.h>

//print numbers between two numbers from big to small
int main()
{
    unsigned int num1, num2, Min, Max;

    while(1)
    {
        printf("Enter the two numbers: ");
        scanf("%d%d",&num1,&num2);

        if(num1 > num2)
        {
            Max = num1;
            Min = num2;
        }
        else
        {
            Max = num2;
            Min = num1;
        }


        for(int num=Max-1; num>Min; num--)
        {
            printf("%d ",num);
        }
        printf("\n");

    }


    return 0;
}
