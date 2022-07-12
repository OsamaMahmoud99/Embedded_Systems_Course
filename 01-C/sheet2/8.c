#include <stdio.h>
#include <stdlib.h>

/*Write a full C program to take 4 choose from user:
1-Set bit.
2-Clear bit
3-Toggle bit.
4-Read bit.
then take number, and bit number.
print the number after set, clear, or toggle if 1,2 or 3 is
selected.
print the bit value if 4 is selected.
*/

void Set_Bit(int *Number, int bit_number)
{
    *Number |= 1 << bit_number;
}

void Clear_Bit(int *Number, int bit_number)
{
    *Number &= ~(1 << bit_number);
}

void Toggle_Bit(int *Number, int bit_number)
{
    *Number ^= (1 << bit_number);
}

char Read_Bit(int Number, int bit_number)
{
    return ((Number>>bit_number)&1);
}

int main()
{
    char ch;
    int Number, bit_number;
    char bit_value;

    printf("1-Set bit.\n");
    printf("2-Clear bit.\n");
    printf("3-Toggle bit.\n");
    printf("4-Read bit.\n");
    printf("/**************************/\n");

    while(1)
    {
        printf("Enter your choice: ");
        scanf(" %c",&ch);

        printf("Enter the number: ");
        scanf("%d",&Number);

        printf("Enter the bit number: ");
        scanf("%d",&bit_number);

        switch(ch)
        {
        case '1':
            Set_Bit(&Number, bit_number);
            printf("Number = %d",Number);
            break;

        case '2':
            Clear_Bit(&Number, bit_number);
            printf("Number = %d",Number);
            break;

        case '3':
            Toggle_Bit(&Number, bit_number);
            printf("Number = %d",Number);
            break;

        case '4':
            bit_value = Read_Bit(Number, bit_number);
            printf("the bit value: %d",bit_value);
            break;
        }
        printf("\n");


    }


    return 0;
}
