#include <stdio.h>
#include <stdlib.h>


int main()
{
    unsigned long long n = 0xffee225588aadd77;
    unsigned char *p = &n;

    for(int i=0; i<8; ++i)
    {
        printf("%X\n",*p);
        p = p + 1;
    }
    while(1)
    {

    }
    return 0;
}