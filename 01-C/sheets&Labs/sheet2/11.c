#include <stdio.h>
#include <stdlib.h>

/*Given two integers: L and R, Find the maximal value of A
xor B where A and B satisfy the condition L =< A <= B <=
R Constrains: 1 <= L <= R <= 1000 Input format: the
input contains two lines first line contains L and next
line contains R. Output format: The maximum value of
Axor B.
*/

int main()
{
    int L , R , Res , Max = 0;

    printf("Enter the L and R: ");
    scanf("%d%d",&L,&R);

    for(int A=L; A<=R; A=A+1)
    {
        for(int B=A; B<=R; B=B+1)
        {
            Res = A ^ B;

            if(Res >= Max)
            {
                Max = Res;
            }
        }
    }
    printf("The Max value of A xor B : %d",Max);


    return 0;
}