
#include "StdTypes.h"

/*void string_print(char *str)
{
    int i;

    for(i=0; str[i]!=0; ++i)
    {
        printf("%c",str[i]);
    }
    printf("\n");
}*/

int string_len(char *str)
{
    int i;
    for(i=0; str[i]; ++i);
    return i;
}

//u8 string_compare(u8 *str1,u8 *str2)
//{
    //int i;
//
    //for(i=0; str1[i]||str2[i]; ++i)
    //{
        //if(str1[i] != str2[i])
        //{
            //return 0;
        //}
    //}
    //return 1;
//}


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

void string_scan(char *str)
{
    int i=0;
    scanf("%c",str+i);
    for(; str[i]!='\n';)
    {
        i++;
        scanf("%c",str+i);
    }
    str[i] = 0;
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

char string_firstRepeatedchar(char *str)
{
    char count[256]= {0};
    int i;
    for(i=0; str[i]; i++)
    {
        count[str[i]]++;

        if(count[str[i]] == 2)
        {
            return str[i];
        }
    }
    return -1;
}



/*********************************************************/
/*******************  sheet4 *****************************/
/*********************************************************/
void string_reverse(char *str)
{
    char temp;
    int l= string_len(str);
    int i=0,j=l-1;

    while(i < j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;

        i++;
        j--;
    }
}

int string_ismirror(char *str)
{
    int i, j=string_len(str)-1, flag = 0;

    while((i < j) && (flag == 0))
    {
        if(str[i] != str[j])
        {
            flag = 1;     //not mirror
        }
        i++;
        j--;
    }
    return flag;

}
void string_reverse_size(char *str, int size)
{
    char temp;
    int i=0,j=size-1;

    while(i < j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;

        i++;
        j--;
    }
}
//" I work as an embedded software engineer for 3 years"
//" sraey 3 rof reenigne erawtfos deddebme na sa krow I"
void string_reversesentence(char *str)
{
    string_reverse(str);
    int i, word_size=0, len;

    for(i=0; str[i]; ++i)
    {
        if(str[i] == ' ')
        {
            string_reverse_size(&str[i-word_size], word_size);
            word_size = 0;
        }
        else
        {
            word_size++;
        }
    }
    string_reverse_size(&str[i-word_size], word_size);

}
char* string_triangletype(char *str)
{
    int num1=0, num2=0, num3=0, digit, i;
    char *type=0;

    for(i=0; str[i]!=' '; ++i)
    {
        digit = str[i] - '0';
        num1 = num1*10 + digit;
    }
    for(i=i+1; str[i]!=' '; ++i)
    {
        digit = str[i] - '0';
        num2 = num2*10 + digit;

    }
    for(i=i+1; str[i]; ++i)
    {
        digit = str[i] - '0';
        num3 = num3*10 + digit;
    }

    if(((num1+num2)<num3) && ((num1+num3)<num2) && ((num2+num3)<num1))
    {
        type = "Not triangle";
    }
    else if((num1 == num2)&&(num1 == num3)&&(num2 == num3))
    {
        type = "Equilateral triangle";
    }
    else if((num1 == num2) && (num1 != num3))
    {
        type = "Isosceles triangle";
    }
    else if((num1 != num2) && (num1 != num3) && (num2 != num3))
    {
        type = "Scalene triangle";
    }


    return type;
}

char* string_triangletype2(char *str)
{
    int num1=0, num2=0, num3=0, digit, i, flag = 0;
    char *type=0;

    for(i=0; str[i]; ++i)
    {
        if(str[i] == ' ')
        {
            flag++;
        }
        else
        {
            if(flag == 0)
            {
                digit = str[i] - '0';
                num1 = num1*10 + digit;
            }
            else if(flag == 1)
            {
                digit = str[i] - '0';
                num2 = num2*10 + digit;
            }
            else if(flag == 2)
            {
                digit = str[i] - '0';
                num3 = num3*10 + digit;
            }
        }

    }

    if(((num1+num2)>num3) && ((num1+num3)>num2) && ((num2+num3)>num1))
    {
        if((num1 == num2)&&(num1 == num3)&&(num2 == num3))
        {
            type = "Equilateral triangle";
        }
        else if((num1 == num2) && (num1 != num3))
        {
            type = "Isosceles triangle";
        }
        else if((num1 != num2) && (num1 != num3) && (num2 != num3))
        {
            type = "Scalene triangle";
        }
    }
    else
    {
        type = "Not triangle";
    }

    return type;
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

char* string_findReplace(char *str, char *find, char *replace)
{
    int i, j, k, f=0, index=-1;
    int main_len = string_len(str);
    int find_Len = string_len(find);
    int replace_Len = string_len(replace);

    int New_Len = main_len-find_Len+replace_Len;
    int main_pos, New_pos;
    char *new_str = (char*)malloc(New_Len*sizeof(char));

    for(i=0; str[i]; ++i)
    {
        if(str[i] == find[0])
        {

            if(string_compare2(&str[i], find, find_Len))
            {
                index = i;
                //printf("%d\n",index);
            }
        }
    }
    if(index == -1)
    {
        return str;
    }
    else
    {
        for(k=0; k <index; k++)
        {
            new_str[k] = str[k];
        }
        main_pos = k;
        //printf("main_pos=%d\n",main_pos);
        New_pos = main_pos + find_Len;
        //printf("%d\n",New_pos);
        for(; k <replace_Len+index; k++)
        {
            new_str[k] = replace[f++];
        }
        //printf("%d\n",k);
        for(; k <New_Len; k++)
        {
            new_str[k] = str[New_pos++];
        }
    }
    new_str[k]=0;
    return new_str;
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
