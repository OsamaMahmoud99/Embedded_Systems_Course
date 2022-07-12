#include <stdio.h>
#include <stdlib.h>

int main()
{   //get the max num from three numbers
    int x , y , z , Max = -1e9;
    printf("Enter two numbers: ");
    scanf("%d%d%d",&x,&y,&z);

    if(x>Max)
    {
        Max = x;
    }
    if(y>Max)
    {
        Max = y;
    }
    if(z>Max)
    {
        Max = z;
    }

    printf("the Max number is %d",Max);
    
    return 0;
}