#include <stdio.h>
#include <stdlib.h>

/*Write c function to count the max number of zeros
between two ones in the binary representation of a
number (296384-> {1001000010111000000} return 4).
*/

int Max_zeros(int n)
{
    int count = 0 , flag = 0 , Max = 0 , i;

    for(i=0; i<32; ++i)
    {
        if((n>>i)&1)
        {
            if(count > Max)
            {
                Max = count;
            }
            count = 0;
            flag = 1;
        }
        else if(flag == 1)
        {
            count++;
        }
    }
    return Max;
}

int main()
{
    int n;

    printf("Enter n: ");
    scanf("%d",&n);

    printf("Max=%d",Max_zeros(n));

    return 0;
}
