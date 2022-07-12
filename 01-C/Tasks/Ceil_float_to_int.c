#include <stdio.h>
#include <stdlib.h>


int main()
{
    float num;
    int  int_num;
    double float_num;
    int Res;

    while(1)
    {
        printf("Enter the number: ");
        scanf("%f",&num);

        int_num = num * 10;
        int_num = int_num / 10;
        float_num = num - int_num;

        if(float_num >= 0.5)
        {
            Res = int_num+1;
        }
        else
        {
            Res = int_num;
        }

        printf("Res = %d\n",Res);
    }
    return 0;
}
