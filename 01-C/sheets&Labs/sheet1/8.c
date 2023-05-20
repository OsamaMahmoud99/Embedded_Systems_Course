#include <stdio.h>
#include <stdlib.h>

//Write a program that reads a positive integer and checks if it is a prime.
int main()
{
    unsigned int num , i , Is_prime=0;

    while(1)
    {
        printf("Enter the number: ");
        scanf("%d",&num);

        Is_prime = 0;
        for(i=2; i<num&&Is_prime==0; ++i)
        {
            if(num%i == 0)
            {
                Is_prime = 1;
                //break;
            }
        }

        if(Is_prime==0){
            printf("The number %d is prime\n",num);
        }
        else{
            printf("The number %d is not prime\n",num);
        }

    }
    return 0;
}
