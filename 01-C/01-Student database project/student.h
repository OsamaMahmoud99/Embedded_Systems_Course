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
void print_school(std_t *ps);
int  student_searchByName(std_t*ps);
int student_BinarysearchByID(std_t*ps);
void student_swap(std_t *ps1 , std_t *ps2);
void student_selectionsort(std_t *arr);
void student_sortby_age(std_t *ps);
void insert_studentbyAge(std_t *ps , int *pindex);
int student_MaxAge(std_t*arr);
void EditStudent_ByID(std_t *ps);