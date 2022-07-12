
void array_print(int *arr, int size)
{
    int i;

    for(i=0; i<size; ++i)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

int array_search(int *arr, int size, int num)
{
    int i;

    for(i=0; i<size; ++i)
    {
        if(arr[i] == num)
        {
            return i;
        }
    }
    return -1;
}

int array_binarysearch(int *arr, int size, int num)
{
    int first = 0, last = size-1, Mid;

    while(last >= first)
    {
        Mid = (first+last)/2;
        if(arr[Mid] == num)
        {
            return Mid;
        }
        else if(arr[Mid] > num)
        {
            last = Mid - 1;
        }
        else
        {
            first = Mid + 1;
        }
    }
    return -1;

}
int array_binarysearch_R(int *arr, int num, int first,int last)
{
    int  Mid;
    if(last >= first)
    {
        Mid = first+(last-1)/2;

        if(arr[Mid] == num)
        {
            return Mid;
        }
        if(arr[Mid] > num)
        {
            return array_binarysearch_R(arr, num, first,Mid-1);
        }

        if(arr[Mid] < num)
        {
            return array_binarysearch_R(arr,num, Mid+1, last);
        }
    }

    return -1;

}
int array_removeprimes(int *arr, int size)
{
    int i, count = 0;

    for(i=0; i<size; i++)
    {
        if(Is_prime(arr[i]))
        {
            arr[i] = 0;
            count = count + 1;
        }
    }

    return count;
}

int array_scan(int *arr, int maxsize)
{
    int size;
    printf("enter the num of elements not more than %d:\n",maxsize);
    scanf("%d",&size);

    if(size>maxsize)
    {
        size = maxsize;
    }
    for(int i=0; i<size; ++i)
    {
        scanf("%d",arr+i); //&arr[i]
    }

    return size;
}

int* Dynamic_array_scan(int *psize)
{
    int i, size;
    printf("enter the num of elements: ");
    scanf("%d",&size);
    int *arr =(int*)malloc(size*sizeof(int));
    if(arr == 0)
    {
        printf("no space\n");
        return;
    }
    else
    {
        for(int i=0; i<size; ++i)
        {
            scanf("%d",arr+i); //&arr[i]
        }
    }
    *psize = size;
    return arr;
}

int array_longseries(int *arr, int size)
{
    int count = 1, max = 0;
    for(int i=0; i<size-1; i++)
    {
        if((arr[i+1]-arr[i]) == 1)
        {
            count = count + 1;
            if(count >= max)
            {
                max = count;
            }
        }
        else
        {
            count = 1;
        }

    }
    return max;
}
int array_copy(int *source,int sourcesize, int *copy, int maxsize)
{
    int size;
    if(sourcesize > maxsize)
    {
        size = maxsize;
    }
    else
    {
        size = sourcesize;
    }
    for(int i=0; i<size; i++)
    {
        copy[i] = source[i];
    }

    return size;
}

int array_mostRepeated(int *arr, int size, int *pnum)
{
    int i,j,count=1, max = 0, c=0;

    for(i=0; i<size; ++i)
    {
        count = 1;
        for(j=i+1; j<size; ++j)
        {
            if(arr[i] == arr[j])
            {
                count++;
            }
            c++;
            if(count >= max)
            {
                max = count;
                *pnum = arr[i];
            }
        }
    }
    printf("%d\n",c);
    return max;
}
// Task
int array_mostRepeatedSorted(int *arr, int size, int *pnum)
{
    int i, arr2[50]= {0}, max=0;

    for(i=0; i<size-1; ++i)
    {
        if(arr[i] == arr[i+1])
        {
            arr2[arr[i]]++;
        }
    }

    for(i=0; i<50; ++i)
    {
        if(arr2[i]>= max)
        {
            max = arr2[i];
            *pnum = i;
        }
    }
    return max+1;
}

void array_bubblesort(int *arr, int size)
{
    int i, j, sorted_flag=1;
    for(i=0; i<size; ++i)
    {
        sorted_flag = 1;
        for(j=i+1; j<size; ++j)
        {
            if(arr[i] > arr[j])
            {
                Swap(&arr[i], &arr[j]);
                sorted_flag = 0;
            }
        }
        if(sorted_flag==1)
        {
            break;
        }
    }
}

void array_selectionsort(int *arr, int size)
{
    int i, j,Max_index,last_index, temp;
    last_index = size-1;

    for(i=0; i<size; ++i)
    {
        Max_index = 0;
        for(j=0; j<size-i; ++j)
        {
            if(arr[j] > arr[Max_index])
            {
                Max_index = j;
            }
        }
        Swap(&arr[Max_index], &arr[last_index]);
        last_index--;
    }
}

void array_countingsort(int *arr, int size)
{
    int i, j = 0,count[10]= {0};
    for(i=0; i<size; ++i)
    {
        count[arr[i]]++;
    }

    i=0;
    while(i<size)
    {
        while(count[j]--)
        {
            arr[i] = j;
            i++;
        }
        j++;
    }
}

void Dynamicarray_countingsort(int *arr, int size)
{
    int i, j = 0,max=arr[0], min=arr[0], count_size;

    for(i=0; i<size; ++i)
    {
        if(arr[i]>max)
            max = arr[i];
        if(arr[i]<min)
            min = arr[i];
    }
    count_size = max-min+1;
    int *count =(int*)calloc(count_size, sizeof(int));
    if(count==0)
    {
        return;
    }
    for(i=0; i<size; ++i)
    {
        count[arr[i]-min]++;
    }

    i=0;
    for(j=0; j<count_size; ++j)
    {
        while(count[j]--)
        {
            arr[i] = j+min;
            i++;
        }
    }
    free(count);
}

/* This function takes last element as pivot,
   places the pivot element at its correct
   position in sorted  array, and places
   all smaller (smaller than pivot) to left
   of pivot and all greater elements to
   right of pivot */
int partition(int arr[], int l, int h)
{
    int x = arr[h];
    int i = (l - 1);

    for (int j = l; j <= h - 1; j++)
    {
        if (arr[j] <= x)
        {
            i++;
            //swap(&arr[i], &arr[j]);
        }
    }
    //swap(&arr[i + 1], &arr[h]);
    return (i + 1);
}

/* A[] --> Array to be sorted,
l --> Starting index,
h --> Ending index */
void quickSort(int A[], int l, int h)
{
    if (l < h)
    {
        /* Partitioning index */
        int p = partition(A, l, h);
        quickSort(A, l, p - 1);
        quickSort(A, p + 1, h);
    }
}

void array_ofstring_print(char**arr, int size)
{
    //printf("%c\n",*(*(arr+1)+1)); //arr[1][1]
    int i, j;

    for(i=0; i<size; ++i)
    {
        /*for(j=0; arr[i][j]; ++j)
        {
            printf("%c",arr[i][j]);
        }
        printf("\n");
        */
        string_print(arr[i]);
    }
    printf("***************\n");
}

void array_ofArray_print(char(*arr)[10], int size)
{
    //printf("%c\n",*(*(arr+1)+1)); //arr[1][1]
    int i, j;

    for(i=0; i<size; ++i)
    {
        /*for(j=0; arr[i][j]; ++j)
        {
            printf("%c",arr[i][j]);
        }
        printf("\n");
        */
        string_print(arr[i]);
    }
    printf("***************\n");
}

int array_ofstring_search(char**arr, int size, char*str)
{
    int i, j;

    for(i=0; i<size; ++i)
    {
        if(string_compare(arr[i], str))
        {
            return i;
        }
    }
    return -1;
}

int array_ofArray_search_char(char arr[][10], int size, char c, int*index)
{
    int i, j;

    for(i=0; i<size; ++i)
    {
        for(j=0; j<10; j++)
        {
            if(arr[i][j] == c)
            {
                *index = j;
                return i;
            }
        }
    }
    return -1;
}

void swap_pointers_char(char**pp1, char**pp2)
{
    char *temp = *pp1;
    *pp1 = *pp2;
    *pp2 = temp;
}

void array_ofstring_bubblesort(char**arr, int size)
{
    int i, j, sorted_flag=1;
    for(i=0; i<size; ++i)
    {
        sorted_flag = 1;
        for(j=i+1; j<size; ++j)
        {
            if(string_compare_thebiggest(arr[i], arr[j])==1)
            {
                swap_pointers_char(&arr[i], &arr[j]);
                sorted_flag = 0;
            }
        }
        if(sorted_flag==1)
        {
            break;
        }
    }
}

int array_ofstring_Binarysearch(char**arr, int size, char*str)
{
    int i, j;
    int First = 0 , Last = size-1, Mid;

    while(First<=Last)
    {
        Mid = (First+Last)/2;

        if(string_compare_thebiggest(arr[Mid] , str) == 0){
            return Mid;
        }

        if(string_compare_thebiggest(arr[Mid] , str) == 1){
            Last = Mid - 1;
        }
        if(string_compare_thebiggest(arr[Mid] , str) == -1){
            First = Mid + 1;
        }
    }
    return -1;
}

void matrix_print(int arr[][5], int row, int col)
{
    for(int i=0; i<row; ++i)
    {

        for(int j=0; j<col; ++j)
        {
            printf("%2d  ",arr[i][j]);
        }
        printf("\n");
    }
}

void matrix_print_zigzag(int arr[][20], int row, int col)
{
    for(int i=0; i<row; ++i)
    {
        if((i&1)==0)
        {
            for(int j=0; j<col; ++j)
            {
                printf("%2d  ",arr[i][j]);
            }
        }
        else
        {
            for(int j=col-1; j>=0; --j)
            {
                printf("%2d  ",arr[i][j]);
            }
        }

        printf("    ");
    }
}

int check_magic_square(int arr[][20],int row, int col)
{
    if(row != col)
    {
        return 0;
    }
    int i, j, sum_L=0, sum_R=0;
    for(i=0; i<row; ++i)
    {
        for(j=0; j<col; ++j)
        {
            if(i == j)
            {
                sum_L = sum_L + arr[i][j];
            }
            if(j == col-1-i)
            {
                sum_R = sum_R + arr[i][j];
            }
        }
    }
    if(sum_L == sum_R)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


/********************************************************/
/*************** sheet 3*********************************/

int array_lastoccurrence(int *arr, int size, int num)
{
    int i;

    for(i=size-1; i>=0; --i)
    {
        if(arr[i] == num)
        {
            return i;
        }
    }
    return -1;
}

int array_Max_Min(int *arr, int size, int *max, int *min, int *maxindex)
{
    int i, minindex;

    *max=0;
    *min=1e9;

    for(int i=0; i<size; i++)
    {
        if(arr[i] >= *max)
        {
            *max = arr[i];
            *maxindex = i;
        }

        if(arr[i] < *min)
        {
            *min = arr[i];
            minindex = i;
        }
    }
    return minindex;
}

int array_return_numbers(int *arr,int num1, int num2)
{
    int i, j=0, size=0;
    for(i=num1+1; i<num2; ++i)
    {
        arr[j++] = i;
        size++;
    }

    return size;
}

void array_reverse(int *arr, int size)
{
    int i=0, j=size-1, temp;

    while(i < j)
    {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;

        i++;
        j--;
    }
}

void array_swapTwo(int *arr1, int size1, int *arr2, int size2)
{
    int i, temp;
    if(size1 == size2)
    {
        for(i=0; i<size1; ++i)
        {
            temp = arr1[i];
            arr1[i] = arr2[i];
            arr2[i] = temp;
        }
    }
    else if(size1 > size2)
    {
        for(i=0; i<size2; ++i)
        {
            temp = arr1[i];
            arr1[i] = arr2[i];
            arr2[i] = temp;
        }
    }

}

int array_longestofanyNum(int *arr, int size,int *pnum)
{
    int i, count = 0, max = 0;
    for(i=0; i<size-1; ++i)
    {
        if((arr[i]^arr[i+1]) == 0)
        {
            count++;
        }
        else
        {
            count = 0;
        }

        if(count >= max)
        {
            max = count;
            *pnum = arr[i];
        }
    }
    return max+1;
}

int array_merge(int *arr1, int size1, int *arr2, int size2, int *arr3)
{
    int i, j=0;
    int size = size1 + size2;

    for(i=0; i<size; i+=2)
    {
        arr3[i] = arr1[j];
        arr3[i+1] = arr2[j];

        j++;
    }

    return size;
}

int array_mergeDiffSize(int *arr1, int size1, int *arr2, int size2, int *arr3)
{
    int i, j=0;
    int size = size1 + size2;

    int Min = 0;
    Min = size1<size2?size1:size2;
    for(i=0; i<2*Min; i++)
    {
        if((i&1) == 0)
        {
            arr3[i] = arr1[j];
        }
        else
        {
            arr3[i] = arr2[j];
            j++;
        }

    }

    if(Min == size2)
    {
        for(; i<size; ++i)
        {
            arr3[i] = arr1[j];
            j++;
        }
    }
    else if(Min == size1)
    {
        for(; i<size; ++i)
        {
            arr3[i] = arr2[j];
            j++;
        }
    }

    return size;
}



int array_removesRepeated(int *arr, int size, int *narr)
{
    int i, nsize = 0;
    for(i=0; i<size-1; ++i)
    {
        if((arr[i]^arr[i+1]) != 0)
        {
            narr[nsize] = arr[i];
            nsize++;
        }
    }
    return nsize;

}

void array_swapAfter2Zeros(int *arr)
{
    int i,first, second, flag = 0;
    for(i=0; flag < 2; i++)
    {
        if((arr[i] == 0)&&(flag == 0))
        {
            first = i;
            flag = 1;

        }
        else if((arr[i] == 0)&&(flag == 1))
        {
            second = i;
            flag = 2;
        }
    }

    Swap(&arr[first+1], &arr[second+1]);
    Swap(&arr[first+2], &arr[second+2]);
    Swap(&arr[first+3], &arr[second+3]);
}

int array_biggestDiff(int *arr, int size)
{
    int i, Min_index=0,Max_index=size-1, Min=1e9, Max = -1e9;
    for(i=0; i<size; ++i)
    {
        if(arr[i] < Min)
        {
            Min = arr[i];
            Min_index = i;
        }
    }
    for(i=0; i<size; ++i)
    {
        if((arr[i] > Max) || (Min_index > Max_index))
        {
            Max = arr[i];
            Max_index = i;
        }
    }
    return arr[Max_index]-arr[Min_index];
}

int array_mostRepeatedSorted_mono(int *arr, int size, int *pnum)
{
    int count[10]= {0}, i, element, Max=-1e9;
    for(i=0; i<size; ++i)
    {
        count[arr[i]]++;
    }

    for(i=0; i<10; ++i)
    {
        if(count[i] > Max)
        {
            Max = count[i];
            element = i;
        }
    }
    *pnum = element;
    return Max;
}

int Dynamicarray_mostRepeated(int *arr, int size, int *pnum)
{
    int  i, countsize, Max=-1e9, Min=1e9, Max_Num=-1e9 ;
    for(i=0; i<size; ++i)
    {
        if(arr[i] > Max)
        {
            Max = arr[i];
        }
        if(arr[i] < Min)
        {
            Min = arr[i];
        }
    }
    countsize = Max-Min+1;
    int *countarr = (int*)calloc(countsize,sizeof(int));

    for(i=0; i<size; ++i)
    {
        countarr[arr[i]-Min]++;
    }

    for(i=0; i<countsize; ++i)
    {
        if(countarr[i] > Max_Num)
        {
            Max_Num = countarr[i];
            *pnum = i + Min;
        }
    }
    free(countarr);
    return Max_Num;
}

void swap_pointers(int **pp1, int **pp2)
{
    int *temp = *pp1;
    *pp1 = *pp2;
    *pp2 = temp;
}
void swap_by2pointers(int **pp1, int **pp2)
{
    int temp = **pp1;
    **pp1 = **pp2;
    **pp2 = temp;
}

int fabonacci(int n)
{
    int i,a=0,b=1,c;
    if(n==0 || n==1)
    {
        return n;
    }
    for(i=1; i<n; ++i)
    {
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

int fabonacci_R(int n)
{
    if(n==0 || n==1)
    {
        return n;
    }

    return fabonacci_R(n-1)+fabonacci_R(n-2);
}


int mostRepeated_NotArray(int n)
{
    int last_value = -1, value;
    for(int i=0 ; i<n; ++i)
    {
        scanf("%d",&value);
        if(value > 9)
        {
            return -1;
        }

        if(value == last_value)
        {

        }
        last_value = value;

    }
}
