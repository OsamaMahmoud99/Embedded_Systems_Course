#include <stdio.h>
#include <stdlib.h>

//take two numbers and multiply them without * operation
int main()
{
    unsigned int num1, num2 , Res = 0;

    while(1)
    {
        printf("Enter the two numbers: ");
        scanf("%d%d",&num1,&num2);

        Res = 0;
        while(num2--)
        {
            Res = Res + num1;
        }
        printf("Mult of two numbers = %d\n",Res);
    }
    return 0;
}