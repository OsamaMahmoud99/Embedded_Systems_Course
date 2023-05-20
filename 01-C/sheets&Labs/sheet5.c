/*1) You have an array of 100 element contain all number from 0 t0 100 except
one number, write c function to find the missed number (try in O(n)).
*/

int Missed_Number(int *arr , int size)
{
    int real_sum = ((size*(size+1))/2);
    int sum = 0;
    for(int i=0; i<size; ++i)
    {
        sum += arr[i];
    }

    return real_sum-sum;
}

/*2) You have an array of 101 element contain all number from 1 t0 100, so one
number is repeated, write c function to find the repeated number (try in
O(n)).
*/

int Repeated_Number(int *arr , int size)
{
    int real_sum = ((size*(size+1))/2);
    int sum = 0;
    for(int i=0; i<size; ++i)
    {
        sum += arr[i];
    }

    return sum-real_sum;
}

/*3) You have an array of integers all numbers in the array repeated 2 times
except one number repeated one time only find this number (try o(n)).
array like {1,2,4,66,2,1,500,66,7,7,500}->4.
*/

int Repeated_OneTime(int *arr , int size)
{
    int result = 0;
    for(int i=0; i<size; ++i)
    {
        result = result ^ arr[i];
    }
    return result;
}

/*4) repeat Q3 but array is sorted (try less than O(n)).
 array {1,1,2,2,4,4,70,70,73,80,80,81,81} ->73.
 */

 int Repeated_OneTimeSorted(int *arr , int size)
 {
     int First = 0 , Last = size-1;
     int Mid;

     while(First<=Last)
     {
         Mid = (First + Last)/2;
         if(arr[Mid] == arr[Mid+1])
         {
             if(Mid%2 == 0)
             {
                 First = Mid + 1;
             }
             else
             {
                 Last = Mid - 1;
             }
         }
         else if(arr[Mid] == arr[Mid-1])
         {
             if(Mid%2 == 0)
             {
                 Last = Mid - 1;
             }
             else
             {
                 First = Mid + 1;
             }
         }
         else{
            return arr[Mid];
         }
     }

 }

/*5) You have an array of integers contain Mono numbers only (from 0 to 9)
 , write c function to find the most repeated number (try in O(n)).
 */

int MostRepeated_Mono(int *arr , int size)
{
    int count_arr[10]={0} , i , Max=0 , index;
    for(i=0; i<size; ++i)
    {
        count_arr[arr[i]]++;
    }

    for(i=0; i<10; ++i)
    {
        if(Max > count_arr[i])
        {
            Max = count_arr[i];
            index = i;
        }
    }
    return index;
}

 /*6) Write c function to find the first repeated char in string (try in O(n)).
 "ahmed selem" ->e.
 */

char FirstRepeated(char *str)
{
    int count_arr[256]={0} , i;
    for(i=0; str[i]; ++i)
    {
        count_arr[str[i]]++;
        if(count_arr[str[i]] == 2)
        {
            return str[i];
        }
    }
}

/*7) Write c function to copy string to string without copy repeated characters
 try (O(n)). "ahmed selem kamel"->"ahmed slk".
 */

void Copy_NoRepeated(char *str , char *Newstr)
{
    int count_arr[256]={0} , i , j=0;
    for(i=0; str[i]; ++i)
    {
        if(count_arr[str[i]] == 0)
        {
            Newstr[j] = str[i];
            j++;
            count_arr[str[i]] = 1;
        }
    }
}

/*8) . Write C function to take an array and if it finds a number "given" makes the
 previous elements in a new array and returns it (try to optimize).
 */


/*9) Write a c function to swap the two bytes of a short int (n=0xFE20 ->0X20FE)
 use 2 methods.
 */

 short SwapTwoBytes(short int n)
 {
     short left = (n&0x00FF) << 8;
     short right = (n&0xFF00) >> 8;
     return right|left;
 }


