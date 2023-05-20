#include <stdio.h>
#include <stdlib.h>

//Write a C program to take a number and a character
//from user if the number is even print the same
//character, if the number is odd print the other case of
//the character (a->A, B->b).

int main()
{
    int Num;
    char character;

    printf("Enter the Number: ");
    scanf("%d",&Num);
    printf("Enter the character: ");
    scanf(" %c",&character);

    if((Num&1) == 0)
    {
        printf("%c",character);
    }
    else
    {
        if(character >= 'a' && character <= 'z')
        {
            printf("%c",(character-'a')+'A'); // small to capital
        }
        else
        {
            printf("%c",(character-'A')+'a'); // capital to small
        }
    }

    while(1)
    {

    }
    return 0;
}