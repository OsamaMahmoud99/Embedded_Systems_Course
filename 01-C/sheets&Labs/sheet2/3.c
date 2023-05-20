#include <stdio.h>
#include <stdlib.h>


//Write a program to reverse a number in decimal
//representation (1205->5021).

int main()
{
    int Num , Rev_Num = 0;
    int Rem;

    printf("Enter the number: ");
    scanf("%d",&Num);

    while(Num>0)
    {
        Rem = Num%10;
        Rev_Num = Rev_Num*10 + Rem ;
        Num = Num / 10;
    }

    printf("Rev num = %d",Rev_Num);
    return 0;
}
