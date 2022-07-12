#include <stdio.h>
#include <stdlib.h>

void print_binary(unsigned int n)
{
    int i;
    int flag = 0;
    for(i=31; i>=0; i=i-1)
    {
        if((n>>i)&1)
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

int main()
{
    unsigned int n;

    while(1)
    {
        scanf("%d",&n);

        printf("%d \n",n);
        print_binary(n);
    }
    return 0;
}
