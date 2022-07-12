#include <stdio.h>
#include <stdlib.h>


int main()
{
    unsigned int num , counter = 0 , i;

    while(1)
    {
        printf("Enter the number: ");
        scanf("%d",&num);
        counter = 0;
        for(i=0; i<32; ++i)
        {
            if((num>>i)&1)
            {
                counter = counter + 1;
            }
        }
        printf("Counter = %d\n",counter);

    }
    return 0;
}
