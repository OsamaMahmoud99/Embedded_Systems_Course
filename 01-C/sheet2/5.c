#include <stdio.h>
#include <stdlib.h>

//write a program to print the binary representation of a
//number, try not to print zeros on the left (5->print 101).

int main()
{
    unsigned int Num;
    int i;
    char flag = 0;

    while(1)
    {
        printf("Enter the number: ");
        scanf("%d",&Num);

        flag = 0;
        for(i=31; i>=0; i=i-1)
        {
            if((Num>>i)&1)
            {
                printf("1");
                flag = 1;
            }
            else
            {
                if(flag == 1)
                {
                    printf("0");
                }

            }
        }
        printf("\n");

    }

    return 0;
}
