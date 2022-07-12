#include <stdio.h>
#include <stdlib.h>


int main()
{
    unsigned int num1,num2,Res;
    char op;

    while(1)
    {
        printf("Enter the equation: ");
        scanf("%d",&num1);
        scanf("%c",&op);
        scanf("%d",&num2);

        switch(op)
        {
        case '+':
            Res = num1 + num2;
            break;
        case '-':
            Res = num1 - num2;
            break;
        case '*':
            Res = num1 * num2;
            break;
        case '/':
            Res = num1 / num2;
            break;
        default:
            printf("wrong operation.");
            break;
        }
        printf("Res = %d\n",Res);
    }
    return 0;
}
