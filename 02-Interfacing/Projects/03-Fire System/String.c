int string_len(char *str)
{
    int i;
    for(i=0; str[i]; ++i);
    return i;
}

int string_compare(char *str1,char *str2)
{
    int i;

    for(i=0; str1[i]||str2[i]; ++i)
    {
        if(str1[i] != str2[i])
        {
            return 0;
        }
    }
    return 1;
}

int string_compare_thebiggest(char *str1,char *str2)
{
    int i;

    for(i=0; str1[i]||str2[i]; ++i)
    {
        if(str1[i] > str2[i])
        {
            return 1;
        }
        else if(str1[i] < str2[i])
        {
            return -1;
        }
    }
    return 0;
}

int string_compareNotcaseSens(char *str1,char *str2)
{
    int i;
    for(i=0; str1[i]||str2[i]; ++i)
    {
        if((str1[i] != str2[i]) && ((str1[i]-'a'+'A')!=str2[i]&&(str1[i]-'A'+'a')!=str2[i]))
        {
            return 0;
        }
    }
    return 1;
}

int string_longestword(char *str)
{
    int i, Max=0, count=0;
    for(i=0; str[i] ; i++)
    {
        if(str[i] != ' ')
        {
            count++;
        }
        else
        {
            count = 0;
        }
        if(count >= Max)
        {
            Max = count;
        }
    }
    return Max;
}

void string_longestword2(char *str, char *word)
{
    int i, Max=0, count=0, index, j=0;
    for(i=0; str[i] ; i++)
    {
        if(str[i] != ' ')
        {
            count++;
            if(count >= Max)
            {
                Max = count;
                index = i - Max+1;
            }
        }
        else
        {
            count = 0;
        }

    }
    for(i=index; i<index+Max; ++i)
    {
        word[j] = str[i];
        j++;
    }
    word[j]=0;
}

void intTostring(int num, char *str)  //2513
{
    int digit, i=0, flag = 0;
    if(num == 0)
    {
        str[0]='0';
        str[1]=0;
        return;
    }
    if(num < 0)
    {
        flag = 1;
        num = num * -1;
    }
    while(num > 0)
    {
        digit = num%10;
        num = num/10;
        str[i] = digit+'0';
        i++;
    }
    if(flag == 1)
    {
        str[i] = '-';
        i++;
    }
    str[i] = 0;
    string_reverse(str);
}

int stringToint(char *str) //2 5 1 3
{
    int i, num=0, digit;

    for(i=0; str[i]; i++)
    {
        digit = str[i]-'0';
        num = num*10 + digit;
    }
    return num;
}

void string_swap(char *str1, char *str2)
{
    int i, temp;

    for(i=0; str1[i]&&str2[i]; ++i)
    {
        temp = str1[i];
        str1[i] = str2[i];
        str2[i] = temp;
    }
}

int intTostring2(int num, char *str)  //2513
{
    int digit, flag = 0;
    int i=0;
    if(num == 0)
    {
        str[0]='0';
        str[1]=0;
        return;
    }
    if(num < 0)
    {
        flag = 1;
        num = num * -1;
    }
    while(num > 0)
    {
        digit = num%10;
        num = num/10;
        str[i] = digit+'0';
        i++;
    }
    if(flag == 1)
    {
        str[i] = '-';
        i++;
    }
    str[i] = 0;
    string_reverse(str);

    return i;
}

char* floatTostring(double num)
{
    static char str[10] = {0};
    int first = num, i;                //num before (.)
    int second = (num-first)*1000;    // num after (.)
    i = intTostring2(first, str);
    str[i] = '.';
    //i = intTostring2(second , str+3);
    str[i+1]=((second%1000)/100)+'0';
    str[i+2]=((second%100)/10)+'0';
    str[i+3]=((second%10)/1)+'0';
    str[i+4]= 0;
    //str[6] = 0;
    return str;
}

int string_compare2(char *str1,char *str2,int size)
{
    int i;

    for(i=0; i<size; ++i)
    {
        if(str1[i] != str2[i])
        {
            return 0;
        }
    }
    return 1;
}


void string_printWords(char *str , char *str1 , char *str2 , int *n1 , int* n2)
{
    int i, j=0 , flag=0 , x1=0 , x2=0;

    for(i=0; str[i]; i++)
    {

        if(str[i]!=',')
        {
            if(0==flag)
            {
                str1[i] = str[i];
            }
            if(1==flag)
            {
                x1 = (x1)*10+str[i]-'0';
            }
            if(2==flag)
            {
                str2[j++]=str[i];
            }
            if(3==flag)
            {
                x2 = (x2)*10+str[i]-'0';
            }
        }
        else
        {
            if(0==flag)
                str1[i]=0;
            if(2==flag)
                str2[j]=0;

            ++flag;
        }
    }

    *n1 = x1;
    *n2 = x2;
}
