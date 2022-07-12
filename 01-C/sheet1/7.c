#include <stdio.h>
#include <stdlib.h>

//Write a program that reads a positive integer and computes the factorial.
int main()
{
    unsigned int num , Fact = 1 , i;

    while(1)
    {
        printf("Enter the number: ");
        scanf("%d",&num);

        Fact= 1;
        for(i=num; i>0; --i)
        {
            Fact = Fact * i;
        }

        printf("The fact of number = %d\n",Fact);
    }
    return 0;
}