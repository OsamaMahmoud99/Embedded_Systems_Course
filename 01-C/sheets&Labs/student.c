#include "student.h"

static int index = 0;
static int New_index = 0;
std_t Newstudent;

void student_scanByRef(std_t* ps)
{
    printf("Enter student name:\n");
    fflush(stdin);
    string_scan(ps->Name);
    printf("Enter student age:\n");
    scanf("%d",&(ps->age));
    printf("Enter student ID:\n");
    scanf("%d",&(ps->ID));
    printf("Enter student grade:\n");
    scanf("%d",&(ps->grade));
    printf("============================\n");
}

void Add_StudentaTLast(std_t *ps , int *counter)
{
    student_scanByRef(ps);
    index ++;
    *counter = index;
}

void student_printByRef(std_t *ps)
{
     printf("name:%s\nage:%d\nID:%d\ngrade:%d\n",ps->Name,ps->age,ps->ID,ps->grade);
     printf("=======================\n");
}

void print_school(std_t *ps , int Size)
{
    for(int i=0; i<Size; ++i)
    {
        student_printByRef(ps+i);
    }
}

int student_searchByName(std_t*ps , int Size , char *name)
{
    for(int i=0; i<Size; ++i)
    {
       if(string_compare(ps[i].Name , name)==1){ //Equal
        return i;
       }
    }
}

void student_swap(std_t *ps1 , std_t *ps2)
{
    std_t temp;
    temp = *ps1;
    *ps1 = *ps2;
    *ps2 = temp;
}

void student_selectionsort(std_t *arr, int Size)
{
    int i, j,Max_index,last_index;
    last_index = Size-1;

    for(i=0; i<Size; ++i)
    {
        Max_index = 0;
        for(j=0; j<Size-i; ++j)
        {
            if((arr[j].age) > (arr[Max_index].age))
            {
                Max_index = j;
            }
        }
        student_swap(&arr[Max_index], &arr[last_index]);
        last_index--;
    }
}
void student_sortby_age(std_t *ps)
{
  student_selectionsort(ps , index);
}

void Shift_student(std_t* ps , std_t *new_student , int new_index)
{
    int i , j=0;
    for(i=new_index; i<index; ++i)
    {
        student_swap(&ps[index-i] , &ps[index-j]);
        j++;
    }

    strcpy(ps[new_index].Name , new_student->Name);
    ps[new_index].age = new_student->age;
    ps[new_index].ID = new_student->ID;
    ps[new_index].grade = new_student->grade;
    index++;
}

void insert_studentbyAge(std_t *ps , int *pindex)
{

    student_scanByRef(&Newstudent);

    int i;
    for(i=0; i<index; ++i)
    {
        if((Newstudent.age) < (ps[i].age))
        {
            New_index = i;
            Shift_student(ps ,&Newstudent , New_index);
            *pindex = index;
            break;
        }
    }
}

/*void student_print(std_t s)
{
    printf("name:%s\nage:%d\ngrage:%c\n",s.Name,s.age,s.grade);
}
*/

/*void student_ArrPrint(std_t *arr , int size)
{
    for(int i=0; i<size; ++i)
    {
        /*printf("name:%s\nage:%d\ngrade:%c\n",arr->Name,arr->age,arr->grade);
        //arr++;

        //student_print(arr[i]);
        student_printByRef(arr+i);

    }
}
*/
/*std_t student_scan(void)
{
    std_t s;
    printf("Enter student name:\n");
    fflush(stdin);
    string_scan(s.Name);
    printf("Enter student age:\n");
    scanf("%d",&s.age);
    printf("Enter student grade:\n");
    scanf(" %c",&s.grade);

    return s;
}
*/


/*std_t* student_scan_Dynamic(void)
{
    std_t* ps = (std_t*)malloc(10*sizeof(std_t));
    printf("Enter student name:\n");
    fflush(stdin);
    string_scan(ps->Name);
    printf("Enter student age:\n");
    scanf("%d",&ps->age);
    printf("Enter student grade:\n");
    scanf(" %c",&ps->grade);

    return ps;
}
*/
int student_MaxAge(std_t*arr , int size)
{
    int Max = arr[0].age , index;
    for(int i=0; i<size; ++i)
    {
        if(arr[i].age>Max)
        {
            Max = arr[i].age;
            index = i;
        }
    }
    return index;
}




