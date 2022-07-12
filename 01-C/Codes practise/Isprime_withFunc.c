#include <stdio.h>
#include <stdlib.h>

int Isprime(int n)
{
    int i;
    if((n==0) || (n==1)){
        return 0;
    }

    for(i=2; i<n; i++)
    {
        if(n%i==0)
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    unsigned int n;

    while(1)
    {
        scanf("%d",&n);

        if(Isprime(n) == 1)
        {
            printf("is prime");
        }
        else
        {
            printf("Not prime");
        }
        printf("\n");
    }
    return 0;
}
