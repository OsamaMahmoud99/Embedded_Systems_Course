#include <stdio.h>
#include <stdlib.h>

int main()
{
    int number , n , sum=0 , i;

    while(1)
    {
        printf("Enter the Num of numbers: ");
        scanf("%d",&n);

        sum = 0;
        while(n--)
        {
            scanf("%d",&number);
            sum = sum + number;
        }

        printf("Sum = %d\n",sum);

    }

    return 0;
}