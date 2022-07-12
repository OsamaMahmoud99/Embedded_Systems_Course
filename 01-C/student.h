#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
    char Name[50];
    int age;
    int ID;
    int grade;
}std_t;

void student_printByRef(std_t *ps);
void Add_StudentaTLast(std_t *ps , int *counter);
void student_printByRef(std_t *ps);
void print_school(std_t *ps , int Size);
int  student_searchByName(std_t*ps , int Size , char *name);
void student_swap(std_t *ps1 , std_t *ps2);
void student_selectionsort(std_t *arr, int Size);
void student_sortby_age(std_t *ps);
void insert_studentbyAge(std_t *ps , int *pindex);

/*typedef struct student
{
    char Name[50];
    int age;
    char grade;
}std_t;
*/
/*void student_print(std_t s);


void student_ArrPrint(std_t *arr , int size);
std_t student_scan(void);
void student_scanByRef(std_t* ps);
*/
