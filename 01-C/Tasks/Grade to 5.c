#include <stdio.h>
#include <stdlib.h>

int main()
{   // Grade to 5
    int Grade;
    printf("Enter the grade: ");
    scanf("%d",&Grade);
    int Grade_after , Rem;

    Rem = Grade%5;
    if(Rem < 3)
    {
        Grade_after = Grade - Rem;
    }
    else
    {
        Grade_after = Grade - Rem + 5;
    }
    printf("Grade after = %d",Grade_after);

    /*if((Grade%10 > 0 && Grade%10 <=2))
    {
        Grade_after = Grade - (Grade%10);
    }
    else if(Grade%10 > 2 && Grade%10 < 5)
    {
        Grade_after = Grade - (Grade%10) + 5;
    }
    else if(Grade%10 > 5 && Grade%10 <= 7)
    {
        Grade_after = Grade - (Grade%10) + 5;
    }
    else if(Grade%10 > 7 && Grade%10 <= 9)
    {
        Grade_after = Grade - (Grade%10) + 10;
    }
    else
    {
        Grade_after = Grade;
    }
     printf("Grade %d",Grade_after);
*/

    return 0;
}