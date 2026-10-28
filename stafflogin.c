#include <stdio.h>
#include <string.h>
#include "functions.h"
void stafflogin()
{
    char username[30], password[30];
    char staffUsernames[10][30] = {
        "staff01", "staff02", "staff03", "staff04", "staff05",
        "staff06", "staff07", "staff08", "staff09", "staff10"
    };
    int i, valid = 0;

    printf("\n");
    printf("                    STAFF LOGIN                       \n");
    printf("  -----------------------------------------------------\n");
    printf("\n  Username: ");
    scanf("%29s", username);
    printf("  Password: ");
    scanf("%29s", password);

    for (i = 0; i < 10; i++)
    {
        if (strcmp(username, staffUsernames[i]) == 0 &&
            strcmp(password, "canteen123") == 0)
        {
            valid = 1;
            break;
        }
    }

    if (valid)
    {
        printf("\n  Login successful! Welcome, %s.\n", username);
        staffmenu();
    }
    else
    {
        printf("\n  Invalid username or password.\n");
    }
}
