
int Fact(int n)
{
    int i, r = 1;

    for(i=1; i<=n; i++)
    {
        r = r * i;
    }

    return r;
}

int Fact_Recursive(int n)
{
    int i, r = 1;

    if(n==1 || n==0){
        return 1;
    }
    return n*Fact(n-1);
}

int Power(int n, int power)
{
    int r = 1;
    while(power > 0)
    {
        r = r * n;
        power = power - 1;
    }

    return r;
}

float round(float n)
{
    int x = n;

    float f = n - x;

    if(f<0.5)
        return x;
    else
        return (x+1);

}

void Mul_with_add(int num1, int num2)
{
    int Res = 0;

    while(num2--)
    {
        Res = Res + num1;
    }

    printf("%d",Res);
}

char Check_perfect_square(int n)
{
    int i;
    char flag = 0;

    for(i=0; i<n&&flag==0; i++)
    {
        if((i*i) == n)
        {
            flag = 1;
        }
    }

    return flag;
}

char Check_baseof2(int num)
{
    char flag = 0;

    if((num&(num-1)) == 0)
        flag = 1;  // base of 2

    return flag;

}
int Is_prime(int n)
{
    int i, flag = 1;

    if(n==0 || n==2)
    {
        flag = 0;
    }
    for(i=2; i<n&&flag==1; i++)
    {
        if((n%i)==0)
        {
            flag = 0;  //not prime
        }
    }
    return flag;  //prime
}

void Generate_prime(int n)
{
    int i = n;

    while(n)
    {
        if(Is_prime(i))
        {
            printf("%d",i);
            n = n - 1;
        }
        i = i + 1;
    }
    printf("\n");
}

void Swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void Print_binary(unsigned int n)
{
    int i, flag = 0;

    for(i=31; i>=0; i--)
    {
        if((n>>i)&1)
        {
            printf("1");
            flag = 1;
        }
        else
        {
            if(flag == 1)
            {
                printf("0");
            }
        }
    }
}

void Reverse_binary(char Num)
{
    char m = 0, j = 7, i;

    for(i=0; i<8; i++)
    {
        if((Num>>i)&1)
        {
            m = m | (1 << j);
        }
        j = j - 1;
    }

    printf("%d",m);
}

int Count_ones(unsigned int num)
{
    int i, count = 0;

    for(i=0; i<=31; i++)
    {
        if((num)&(1<<i))
        {
            count = count + 1;
        }
    }

    return count;
}

int Max_zeros(int n)
{
    int count = 0, flag = 0, Max = 0, i;

    for(i=0; i<32; ++i)
    {
        if((n>>i)&1)
        {
            if(count > Max)
            {
                Max = count;
            }
            count = 0;
            flag = 1;
        }
        else if(flag == 1)
        {
            count++;
        }
    }
    return Max;
}


int power_of3(int num)
{
    /* The maximum power of 3 value that
       integer can hold is 1162261467 ( 3^19 ) .*/
    return 1162261467 % num == 0;
}
