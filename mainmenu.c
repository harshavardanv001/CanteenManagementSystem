#include<stdio.h>
#include"functions.h"
int main()
{
    int choice;
do{
    printf("\n");
    printf("  .======================================================.\n");
    printf("  |                                                      |\n");
    printf("  |                C E G   C A N T E E N                 |\n");
    printf("  |       ----------------------------------             |\n");
    printf("  |       SMART FOOD ORDERING & MANAGEMENT               |\n");
    printf("  |                                                      |\n");
    printf("  |   +--------------------------------------------------|\n");
    printf("  |   |                                                  |\n");
    printf("  |   |    GOOD FOOD. ZERO HASSLE.                       |\n");
    printf("  |   |    Your campus food, one step away.              |\n");
    printf("  |   |                                                  |\n");
    printf("  |   +--------------------------------------------------|\n");
    printf("  |                                                      |\n");
    printf("  |    < 01 >   STUDENT PORTAL                           |\n");
    printf("  |              Browse menu  /  Place order             |\n");
    printf("  |                                                      |\n");
    printf("  |    < 02 >   STAFF CONSOLE                            |\n");
    printf("  |              Manage food  /  Process orders          |\n");
    printf("  |                                                      |\n");
    printf("  |    < 03 >   EXIT                                     |\n");
    printf("  |              Leave the counter                       |\n");
    printf("  |                                                      |\n");
    printf("  '======================================================='\n");
    printf("\n       SELECT OPTION  >> ");


    if (scanf("%d", &choice) != 1)
    {
        printf("\n       Invalid input.\n");
        return 0;
    }

    switch (choice)
    {
        case 1:
            studentmenu();
            break;

        case 2:
           stafflogin();
           break;

        case 3:
            printf("\n       >> Thanks for stopping by CEG Canteen!\n");
            break;

        default:
            printf("\n       >> Invalid option. Choose 1, 2, or 3.\n");
    }
}while(choice!=3);
    return 0;
}