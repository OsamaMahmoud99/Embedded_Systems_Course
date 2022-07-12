#include <stdio.h>
#include <stdlib.h>

//Write a program that reads two numbers and find the prime between them.
int main()
{
    unsigned int num1, num2, i, j, Flag = 0;

    while(1)
    {
        printf("Enter the number1: ");
        scanf("%d",&num1);
        printf("Enter the number2: ");
        scanf("%d",&num2);

        printf("Prime numbers: ");
        for(i=num1+1; i<num2; ++i)
        {
            Flag = 0;
            for(j=2; j<i&&Flag==0; ++j)
            {
                if(i%j == 0)
                {
                    Flag = 1;
                }
            }
            if((Flag == 0) && (i!= 0) && (i!=1)  )
            {
                printf("%d ",i);
            }
        }
        printf("\n");
    }
    return 0;
}

