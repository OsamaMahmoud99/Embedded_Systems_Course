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

void print_school(std_t *ps)
{
    for(int i=0; i<index; ++i)
    {
        student_printByRef(ps+i);
    }
}

int student_searchByName(std_t*ps)
{
    char student[20];
    printf("Enter the student name you search:\n");
    scanf("%s", student);
    for(int i=0; i<index; ++i)
    {
       if(string_compare(ps[i].Name , student)==1){ //Equal
        return i;
       }
    }
    return -1;
}
int student_searchByID(std_t*ps , int Size)
{
    int ID;
    printf("Enter the ID: ");
    scanf("%d",&ID);
    for(int i=0; i<Size; ++i)
    {
        if(ps[i].ID == ID)
        {
            return i;
        }
    }
    return -1;
}

int student_BinarysearchByID(std_t*ps)
{
    int First = 0 , Last = index - 1;
    int Mid;

    int ID;
    printf("Enter the ID: ");
    scanf("%d",&ID);

    while(First<=Last)
    {
        Mid = (First + Last) / 2;

        if(ps[Mid].ID == ID)
        {
            return Mid;
        }
        else if(ps[Mid].ID > ID)
        {
            Last = Mid - 1;
        }
        else if(ps[Mid].ID < ID)
        {
            First = Mid + 1;
        }
    }
    return -1;
}

void student_swap(std_t *ps1 , std_t *ps2)
{
    std_t temp;
    temp = *ps1;
    *ps1 = *ps2;
    *ps2 = temp;
}

void student_selectionsort(std_t *arr)
{
    int i, j,Max_index,last_index;
    last_index = index-1;

    for(i=0; i<index; ++i)
    {
        Max_index = 0;
        for(j=0; j<index-i; ++j)
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
  student_selectionsort(ps);
}

void Shift_student(std_t* ps , std_t *new_student , int new_index)
{
    int i , j=0;
    for(i=new_index; i<index; ++i)
    {
        student_swap(&ps[index-1-j] , &ps[index-j]);
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

int student_MaxAge(std_t*arr)
{
    int Max = arr[0].age , index;
    for(int i=0; i<index; ++i)
    {
        if(arr[i].age>Max)
        {
            Max = arr[i].age;
            index = i;
        }
    }
    return index;
}

void EditStudent_ByID(std_t *ps)
{

    int i = student_searchByID(ps , index);
    int choice;

    if(i != -1)
    {
        printf("1.name\n");
        printf("2.Age\n");
        printf("3.ID\n");
        printf("4.Grade\n");
        printf("Enter the New Item you want to change: ");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
             fflush(stdin);
             string_scan(ps[i].Name);
             break;
        case 2:
             scanf("%d",&ps[i].age);
             break;
        case 3:
             scanf("%d",&ps[i].ID);
             break;
        case 4:
             scanf("%d",&ps[i].grade);
             break;
        }

    }
}

void student_DeleteByID(std_t *ps)
{
    int i;
    i = student_BinarysearchByID(ps);

    if(i != -1)
    {
        for(int j=i; j<index; ++j)
        {
            strcpy(ps[j].Name , ps[j+1].Name);
            ps[j].age = ps[j+1].age;
            ps[j].grade = ps[j+1].grade;
            ps[j].ID = ps[j+1].ID;
        }
    }
    index--;
}

