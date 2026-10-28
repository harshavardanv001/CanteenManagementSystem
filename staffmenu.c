#include <stdio.h>
#include "functions.h"

void staffmenu()
{
    int choice;

    do
    {
        printf("\n");
        printf("                    STAFF CONSOLE\n");
        printf("  ------------------------------------------------------\n");
        printf("\n");
        printf("  1.  View Food Menu\n");
        printf("  2.  Search Food Item\n");
        printf("  3.  Manage Food Items (Add / Update / Remove)\n");
        printf("  4.  Undo Last Supported Action\n");
        printf("  5.  View All Orders and Pending Orders\n");
        printf("  6.  Process Next Order\n");
        printf("  7.  Search Order by Token\n");
        printf("  8.  Update Order Status\n");
        printf("  9.  View Completed \n");
        printf("  10. View Sales Report\n");
        printf("  11. View Popular Food Items\n");
        printf("  12. View Stock Report\n");
        
        printf("  13. Logout\n");
        printf("\n");
        printf("  Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\n  Invalid input. Please enter a number.\n");

            while (getchar() != '\n');

            choice = 0;
            continue;
        }

        switch (choice)
        {
            case 1:
                 viewFoodMenu();
                break;
                  
            case 2:
                searchFoodItem();
                break;
            case 3:
               manageFoodItems();
                break;
      
            case 4:
                 undoFoodUpdate();
                break;
            case 5:
                 viewStaffOrders();
                break;

            case 6:
                processNextOrder();
                break;

            case 7:
                searchStaffOrder();
                break;

            case 8:
                 updateOrderStatus();
                break;

            case 9:
                viewCompletedOrders();
                break;

            case 10:
               SalesReport();
                break;

            case 11:
                popularFoodReport();
                break;

            case 12:
            
                stockReport();
                break;

            

            case 13:
                printf("\n  Logging out of Staff Console...\n");
                break;

            default:
                printf("\n  Invalid option. Choose 1 to 13.\n");
        }

    } while (choice != 13);
}