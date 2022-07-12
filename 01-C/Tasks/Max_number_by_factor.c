#include <stdio.h>
#include <stdlib.h>

int main()
{
    int number, n, sum=0, i, Max = -1e9, factor;

    while(1)
    {
        printf("Enter the Num of numbers: ");
        scanf("%d",&n);
        printf("Enter the factor: ");
        scanf("%d",&factor);

        Max = -1e9;
        sum = 0;
        while(n--)
        {
            scanf("%d",&number);

            if(number%factor == 0)
            {
                sum = sum + number;
                if(number > Max)
                {
                    Max = number;
                }
            }

        }

        printf("Max = %d\n",Max);
        printf("Sum = %d\n",sum);

    }

    return 0;
}