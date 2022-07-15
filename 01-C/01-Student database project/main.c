#include "student.h"
int main()
{
    int Last_index = 0 , i=0;
    int choice;
    std_t school[1000];



    while(1)
    {
        printf("1.Insert student to last\n");
        printf("2.Search by name\n");
        printf("3.Search for the biggest age\n");
        printf("4.Print school\n");
        printf("5.delete student by ID\n");
        printf("6.sorted school by age\n");
        printf("7.Insert at Pos when sorted by age\n");
        printf("8.Print by ID\n");
        printf("9.Edit by ID\n");
        printf("10.To Exit\n");
        printf("========================================\n");

        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
             Add_StudentaTLast(&school[Last_index] , &Last_index);
             break;
        case 2:
             i = student_searchByName(school);
             if( i != -1){
                 student_printByRef(school+i);
             }
             else{
                printf("student name Not found\n");
             }
             break;
        case 3:
             i = student_MaxAge(school);
             student_printByRef(school+i);
             break;
        case 4:
             print_school(school);
             break;
        case 5:
             student_DeleteByID(school);
             break;
        case 6:
             student_sortby_age(school);
             break;
        case 7:
             student_sortby_age(school);
             insert_studentbyAge(school , &Last_index);
             break;
        case 8:
             i = student_searchByID(school , Last_index);
             if(i != -1){
                student_printByRef(school+i);
             }
             else{
                printf("student ID Not found\n");
             }
             break;
        case 9:
            EditStudent_ByID(school);
            break;
        case 10:
			exit(1);
        }
    }