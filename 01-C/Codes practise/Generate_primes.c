#include <stdio.h>
#include <stdlib.h>

int Isprime(int n)
{
    int i;
    if((n==0) || (n==1))
    {
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

void generate_prime(int n)
{
    int i = n;
    while(n)
    {
        if(Isprime(i))
        {
            printf("%d ",i);
            n--;
        }
        i++;
    }
    printf("\n");
}

int main()
{
    int n;

    while(1)
    {
        scanf("%d",&n);

        generate_prime(n);
    }

    return 0;
}
