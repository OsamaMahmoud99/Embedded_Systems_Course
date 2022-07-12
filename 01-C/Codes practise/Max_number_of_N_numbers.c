#include <stdio.h>
#include <stdlib.h>

int main()
{
    int number , n , sum=0 , i , Max = -1e9;

    while(1)
    {
        printf("Enter the Num of numbers: ");
        scanf("%d",&n);
        Max = -1e9;
        while(n--)
        {
            scanf("%d",&number);
            if(number > Max)
            {
                Max = number;
            }
        }

        printf("Max = %d\n",Max);

    }

    return 0;
}