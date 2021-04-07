#include "S03.h"

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void mainpage()
{
    int process = 0;
    system("cls");
    date();
    printf("\n");
    printf("\t\t\t\t    ---------------------------\n");
    printf("\t\t\t\t    |STUDENT MANAGEMENT SYSTEM|\n");
    printf("\t\t\t\t    ---------------------------\n");
    printf("\n\n\n");
    printf("\t\t\t\t");
    printf("Prepared By    ");
    printf(":");
    printf("   Group 3");
    printf("\n\n");
    printf("\t\t\t\t");
    printf("Mini Project   ");
    printf(":");
    printf("   Student Management System");
    printf("\n\n");
    printf("\t\t\t\t");
    printf("Guided By      ");
    printf(":");
    printf("   Mr. Nguyen Le Hoang Dung, Mr. Ho Tuan Thanh");
    printf("\n\n");
    printf("\t\t\t\t    Press Enter to continue......");
    printf("\n\n");
    getchar();
    printf("\t\t\t\tLoading");

    for (process = 0; process < 25; process++)
    {
        delay(150);
        printf(".");
    }
}