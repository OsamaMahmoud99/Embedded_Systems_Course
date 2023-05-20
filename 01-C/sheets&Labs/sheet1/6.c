#include <stdio.h>
#include <stdlib.h>

//take the number and power and calculate the power of number
int main()
{
    unsigned int num , power , Res = 1 , i = 0;

    while(1)
    {
        printf("Enter the number: ");
        scanf("%d",&num);
        printf("Enter the power: ");
        scanf("%d",&power);

        Res = 1;
        for(i=0; i<power; ++i)
        {
            Res = Res * num;
        }

        printf("The pow of number = %d\n",Res);
    }
    return 0;
}