
#define SERIAL_LENS        5

#define EQUAL              1
#define NOT_EQUAL          0

#define NOT_FOUND          -1

#define A1_BIGGER           2
#define A1_SMALLER          3

int array_compare(unsigned char *arr1,unsigned char *arr2)
{
    int i;

    for(i=0; i < SERIAL_LENS; ++i)
    {
        if(arr1[i] != arr2[i])
        {
            return NOT_EQUAL;
        }
    }
    return EQUAL;
}

int array_compare_binary(unsigned char *arr1,unsigned char *arr2,int size)
{
    int i;

    for(i=0; i < size; ++i)
    {
        if(arr1[i] != arr2[i])
        {
            if(arr1[i] > arr2[i])
            {
                return A1_BIGGER;
            }
            else
            {
                return A1_SMALLER;
            }
        }

    }
    return EQUAL;
}

void Serial_swap(unsigned char *arr1, unsigned char  *arr2, int size)
{
    int i;
    unsigned char temp;

    for(i=0; i<size; ++i)
    {
        temp = arr1[i];
        arr1[i] = arr2[i];
        arr2[i] = temp;
    }
}

void Serial_printAll(unsigned char arr[][SERIAL_LENS], int size)
{
    int i, j;

    for(i=0; i<size; ++i)
    {
        for(j=0; j<SERIAL_LENS; ++j)
        {
            printf("%.2x ",arr[i][j]);
        }
        printf("\n");

    }
    printf("=======================\n");
}
int Serial_Linear_search(unsigned char arr[][SERIAL_LENS], int size, unsigned char *S)
{
    int i;
    for(i=0; i<size; ++i)
    {
        if(array_compare(arr[i], S))
        {
            return i;
        }
    }
    return NOT_FOUND;
}

void Serial_bubblesort(unsigned char arr[][SERIAL_LENS], int size)
{
    int i, j, sorted_flag=1;
    for(i=0; (i<size-1)&&(sorted_flag==1); ++i)
    {
        sorted_flag = 1;
        for(j=0; j<SERIAL_LENS-1-i; ++j)
        {
            if(array_compare_binary(arr[j], arr[j+1], SERIAL_LENS) == (A1_BIGGER))
            {
                Serial_swap(arr[j], arr[j+1], SERIAL_LENS);
                sorted_flag = 0;
            }
        }
    }
}

int Serial_Binary_search(unsigned char arr[][SERIAL_LENS], int size, unsigned char *S)
{
        int First, Last, Mid;
        First = 0;
        Last = size-1;
        int status;

        while(First<=Last)
        {
            Mid = First+(Last-1)/2;
            status = array_compare_binary(arr[Mid], S , SERIAL_LENS);
            if(status == EQUAL)
            {
                return Mid;
            }
            else if(status == A1_BIGGER)
            {
                Last = Mid - 1;
            }
            else
            {
                First = Mid + 1;
            }

        }
        return NOT_FOUND;
}
