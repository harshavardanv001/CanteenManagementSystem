#include <stdio.h>
#include "functions.h"

void studentmenu()
{
    int choice;

    do
    {
        printf("\n");
        printf("                    STUDENT CONSOLE\n");
        printf("  ------------------------------------------------------\n");
        printf("\n");
        printf("  1.  View Food Menu\n");
        printf("  2.  Search Food Item\n");
        printf("  3.  Filter Food by Category\n");
        printf("  4.  Add Food to Cart\n");
        printf("  5.  View Cart\n");
        printf("  6.  Update Item Quantity / Remove Item\n");
        printf("  7.  Place Order\n");
        printf("  8.  View Bill / Receipt\n");
        printf("  9.  Track Order by Token\n");
        printf("  10. View Order History\n");
        printf("  11. Exit \n");
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
               filterFoodByCategory();
                break;

            case 4:
                 addToCart();
                break;

            case 5:
                 viewCart();
                break;

            case 6:
               updateCart();
                break;

            case 7:
    printf("\nWARNING: Once the order is placed, it cannot be cancelled!\n");
    printf("Do you want to continue? (1 = Yes, 0 = No): ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        placeOrder();
    }
    else
    {
        printf("\nOrder placement cancelled.\n");
    }
    break;

            case 8:
                viewBill();
                break;

            case 9:
                trackOrder();
                break;
            case 10:
                 viewOrderHistory();
                break;

            case 11:
                printf("\n  Returning to Main Menu...\n");
                return;

            default:
                printf("\n  Invalid option. Choose 1 to 11.\n");
        }

    } while (1);
}
