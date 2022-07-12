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

int main()
{
    int n1, n2, i;

    while(1)
    {
        scanf("%d%d",&n1,&n2);

        printf("Prime numbers: ");
        for(i=n1; i<=n2; i++)
        {
            if(Isprime(i) == 1)
            {
                printf("%d ",i);
            }
        }
        printf("\n");
    }

return 0;
}
