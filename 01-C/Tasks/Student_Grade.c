#include <stdio.h>
#include <stdlib.h>

int main()
{   // Grade
    int Grade;
    printf("Enter the grade: ");
    scanf("%d",&Grade);

    if(Grade < 50)
    {
        printf("Fail");
    }
    else if((Grade >= 50) && (Grade < 65))
    {
        printf("accept");
    }
    else if((Grade >=65) && (Grade < 75))
    {
        printf("Good");
    }
    else if((Grade >=75) && (Grade < 85))
    {
        printf("Very Good");
    }
    else if(Grade >= 85)
    {
        printf("Excellent");
    }
    else
    {
        printf("Wrong grade");
    }


    return 0;
}
