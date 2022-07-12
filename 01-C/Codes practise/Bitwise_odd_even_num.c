#include <stdio.h>
#include <stdlib.h>


int main()
{
    unsigned int num;

    while(1)
    {
        printf("Enter the number: ");
        scanf("%d",&num);

        if(num&1)
        {
            printf("the number %d is odd\n",num);
        }
        else
        {
            printf("the number %d is even\n",num);
        }
    }
    return 0;
}
