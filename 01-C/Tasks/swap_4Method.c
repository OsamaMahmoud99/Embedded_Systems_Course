#include <stdio.h>
#include <stdlib.h>


int main()
{
    int x = 5 , y = 7;

    int temp;

    temp = x;
    x = y;
    y = temp;

    printf("x=%d y=%d",x , y);

    while(1)
    {

    }
    return 0;
}
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>


int main()
{
    int x = 5 , y = 7;

    x = x * y;
	y = x / y;
	x = x / y;

    printf("x=%d y=%d",x , y);

    while(1)
    {

    }
    return 0;
}
/**********************************************************************************/
#include <stdio.h>
#include <stdlib.h>


int main()
{
    int x = 5 , y = 7;

    x = x + y;
    y = x - y;
    x = x - y;

    printf("x=%d y=%d",x , y);

    while(1)
    {

    }
    return 0;
}
/**********************************************************************************/
#include <stdio.h>
#include <stdlib.h>


int main()
{
    int x = 5 , y = 7;

    x = x ^ y;
    y = x ^ y;
    x = x ^ y;

    printf("x=%d y=%d",x , y);

    while(1)
    {

    }
    return 0;
}