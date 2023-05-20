#include <stdio.h>
#include <stdlib.h>


void pattern_1(int num_lines)
{
    for(int i=0; i<num_lines; i++)
    {
        for(int j=i; j<num_lines; j++)
        {
            if (i<=j)
            {
                printf("*");
            }
        }
        printf("\n");
    }
}

void pattern_2(int num_lines)
{
    for(int i=0; i<num_lines; i++)
    {
        for(int j=0; j<num_lines; j++)
        {
            if (i>=j)
            {
                printf("*");
            }
        }
        printf("\n");
    }
}
int main()
{
    int Num_Lines;

    while(1)
    {
        printf("Enter number of lines: ");
        scanf("%d",&Num_Lines);

        //pattern_1(Num_Lines);
        pattern_2(Num_Lines);
    }


    return 0;
}