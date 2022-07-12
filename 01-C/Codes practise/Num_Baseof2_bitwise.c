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
        if(counter == 1)
        {
            printf("the number is base of 2\n");
        }
        else
        {
            printf("Not base of 2\n");
        }


    }
    return 0;
}

/****************************************************************************/
#include <stdio.h>
#include <stdlib.h>


int main()
{
    unsigned int num;

    while(1)
    {
        printf("Enter the number: ");
        scanf("%d",&num);

        if((num&(num-1))==0)
        {
            printf("the number is base of 2\n");
        }
        else
        {
            printf("Not base of 2\n");
        }

        printf("\n");
    }
    return 0;
}

