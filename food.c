
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "structures.h"
/*
   FOOD LINKED LIST OPERATIONS
*/
struct Food *head = NULL;
struct Food *temp = NULL;
struct Food *newNode = NULL;
void addFoodNode(int id, char name[], char category[], float price, int stock)
{
    newNode = (struct Food *)malloc(sizeof(struct Food));

    if (newNode == NULL)
    {
        printf("\n  Memory allocation failed.\n");
        return;
    }

    newNode->id = id;
    strcpy(newNode->name, name);
    strcpy(newNode->category, category);
    newNode->price = price;
    newNode->stock = stock;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}
/*
   FOR CART
*/

struct CartItem cart[20];
int cartCount = 0;

/*
     HASH TABLE OPERATIONS
*/
struct Order *orderHead = NULL;
struct Order *orderTail = NULL;

struct Order *hashTable[HASH_SIZE] = {NULL};

int nextToken = 1001;
int hashFunction(int token)
{
    return token % HASH_SIZE;
}

void insertOrderHash(struct Order *order)
{
    int index = hashFunction(order->token);

    order->hashNext = hashTable[index];
    hashTable[index] = order;
}

struct Order *searchOrderHash(int token)
{
    int index = hashFunction(token);
    struct Order *current = hashTable[index];

    while (current != NULL)
    {
        if (current->token == token)
            return current;

        current = current->hashNext;
    }

    return NULL;
}
/*
  QUEUE OPERATIONS
*/
struct Order *orderQueue[MAX_PENDING_ORDERS];
int queueFront = 0;
int queueRear = -1;
int queueCount = 0;

int enqueueOrder(struct Order *order)
{
    if (queueCount == MAX_PENDING_ORDERS)
        return 0;

    queueRear = (queueRear + 1) % MAX_PENDING_ORDERS;
    orderQueue[queueRear] = order;
    queueCount++;

    return 1;
}

struct Order *dequeueOrder(void)
{
    struct Order *order;

    if (queueCount == 0)
        return NULL;

    order = orderQueue[queueFront];
    queueFront = (queueFront + 1) % MAX_PENDING_ORDERS;
    queueCount--;

    return order;
}

void removeOrderFromQueue(int token)
{
    int count = queueCount;
    int i;
    struct Order *order;

    for (i = 0; i < count; i++)
    {
        order = dequeueOrder();

        if (order != NULL && order->token != token)
            enqueueOrder(order);
    }
}

/*
STACK OPERATIONS
*/

struct UpdateUndo *updateUndoTop = NULL;
void pushUndo(struct UpdateUndo *action)
{
    action->next = updateUndoTop;
    updateUndoTop = action;
}

struct UpdateUndo *popUndo(void)
{
    struct UpdateUndo *action;

    if (updateUndoTop == NULL)
        return NULL;

    action = updateUndoTop;
    updateUndoTop = updateUndoTop->next;
    action->next = NULL;

    return action;
}

void initializeFoodMenu()
{
    if (head != NULL)
        return;

    addFoodNode(1, "Idli", "Breakfast", 30.00, 40);
    addFoodNode(2, "Dosa", "Breakfast", 45.00, 30);
    addFoodNode(3, "Pongal", "Breakfast", 40.00, 25);
    addFoodNode(4, "Meals", "Lunch", 80.00, 35);
    addFoodNode(5, "FriedRice", "Lunch", 90.00, 20);
    addFoodNode(6, "Noodles", "Lunch", 85.00, 15);
    addFoodNode(7, "Samosa", "Snacks", 15.00, 50);
    addFoodNode(8, "Tea", "Drinks", 12.00, 60);
}
/*
   ROUTINES
*/
void viewFoodMenu()
{
    initializeFoodMenu();

    printf("\n");
    printf("  =================== FOOD MENU ===================\n\n");
    printf("  %-5s %-20s %-12s %-10s %-12s\n",
           "ID", "Food Item", "Category", "Price", "Availability");
    printf("  ---------------------------------------------------------------\n");

    temp = head;

    while (temp != NULL)
    {
        printf("  %-5d %-20s %-12s Rs.%-7.2f %-12s\n",
               temp->id,
               temp->name,
               temp->category,
               temp->price,
               temp->stock > 0 ? "Available" : "Out of stock");

        temp = temp->next;
    }

    printf("  ---------------------------------------------------------------\n");
}

void searchFoodItem()
{
    char searchName[30];
    int found = 0;

    initializeFoodMenu();

    printf("\n  Enter food name to search: ");
    scanf("%29s", searchName);

    temp = head;

    while (temp != NULL)
    {
        if (_stricmp(temp->name, searchName) == 0)
        {
            printf("\n  Food Item Found!\n");
            printf("  ID       : %d\n", temp->id);
            printf("  Name     : %s\n", temp->name);
            printf("  Category : %s\n", temp->category);
            printf("  Price    : Rs. %.2f\n", temp->price);
            printf("  Stock    : %d\n", temp->stock);

            found = 1;
            break;
        }

        temp = temp->next;
    }

    if (!found)
        printf("\n  Food item not found.\n");
}
void filterFoodByCategory()
{
    char searchCategory[20];
    int found = 0;
    initializeFoodMenu();
    printf("\n  Enter category (Breakfast/Lunch/Snacks/Drinks): ");
    scanf("%19s", searchCategory);

    temp = head;

    printf("\n  ------------ FILTERED FOOD MENU -------------\n");

    while (temp != NULL)
    {
        if (_stricmp(temp->category, searchCategory) == 0)
        {
            printf("\n  ID       : %d", temp->id);
            printf("\n  Name     : %s", temp->name);
            printf("\n  Category : %s", temp->category);
            printf("\n  Price    : Rs. %.2f", temp->price);
            printf("\n  Stock    : %d\n", temp->stock);

            found = 1;
        }

        temp = temp->next;
    }

    if (!found)
        printf("\n  No food items found in this category.\n");
}

void addToCart()
{
    char searchName[30];
    int quantity, i, choice;

    initializeFoodMenu();

    do
    {
        printf("\n  Enter Food Name: ");
        scanf("%29s", searchName);

        printf("  Enter Quantity: ");
        scanf("%d", &quantity);

        if (quantity <= 0)
        {
            printf("\n  Invalid quantity!\n");
        }
        else
        {
            temp = head;

            while (temp != NULL)
            {
                if (_stricmp(temp->name, searchName) == 0)
                {
                    break;
                }
                temp = temp->next;
            }

            if (temp == NULL)
            {
                printf("\n  Food item not found!\n");
            }
            else if (temp->stock < quantity)
            {
                printf("\n  Only %d items available.\n", temp->stock);
            }
            else
            {
                for (i = 0; i < cartCount; i++)
                {
                    if (cart[i].foodId == temp->id)
                    {
                        break;
                    }
                }

                if (i < cartCount)
                {
                    if (cart[i].quantity + quantity > temp->stock)
                    {
                        printf("\n  Not enough stock available.\n");
                    }
                    else
                    {
                        cart[i].quantity += quantity;
                        printf("\n  Cart quantity updated successfully!\n");
                    }
                }
                else if (cartCount >= 20)
                {
                    printf("\n  Cart is full!\n");
                }
                else
                {
                    cart[cartCount].foodId = temp->id;
                    strcpy(cart[cartCount].name, temp->name);
                    cart[cartCount].price = temp->price;
                    cart[cartCount].quantity = quantity;
                    cartCount++;

                    printf("\n  Item added to cart successfully!\n");
                }
            }
        }

        printf("\n  1. Add Another Item\n");
        printf("  2. Finish Adding\n");
        printf("  Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ;
            choice = 2;
        }

    } while (choice == 1);
}
void viewCart()
{
    int i;
    float total = 0;

    printf("\n  ------------------ YOUR CART -----------------\n\n");

    if (cartCount == 0)
    {
        printf("  Your cart is empty!\n");
        return;
    }

    printf("  %-20s %-10s %-10s %-10s\n",
           "Food Item", "Price", "Quantity", "Subtotal");

    printf("  ----------------------------------------------------\n");

    for (i = 0; i < cartCount; i++)
    {
        float subtotal = cart[i].price * cart[i].quantity;

        printf("  %-20s Rs.%-7.2f %-10d Rs.%.2f\n",
               cart[i].name,
               cart[i].price,
               cart[i].quantity,
               subtotal);

        total += subtotal;
    }

    printf("  ----------------------------------------------------\n");
    printf("  Total Amount: Rs. %.2f\n", total);
}

void updateCart()
{
    char searchName[30];
    int choice, quantity, i, j;

    if (cartCount == 0)
    {
        printf("\nYour cart is empty!\n");
        return;
    }

    printf("\n1. Update Item Quantity\n");
    printf("2. Remove Item from Cart\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    if (choice != 1 && choice != 2)
    {
        printf("\nInvalid choice!\n");
        return;
    }
    printf("Enter Food Name: ");
    scanf("%29s", searchName);

    for (i = 0; i < cartCount; i++)
    {
        if (_stricmp(cart[i].name, searchName) == 0)
        {
            if (choice == 1)
            {
                printf("Enter New Quantity: ");
                scanf("%d", &quantity);

                if (quantity <= 0)
                {
                    printf("\nInvalid quantity!\n");
                    return;
                }

                temp = head;

                while (temp != NULL && temp->id != cart[i].foodId)
                    temp = temp->next;

                if (temp == NULL)
                {
                    printf("\nFood item no longer exists in the menu.\n");
                    return;
                }

                if (quantity > temp->stock)
                {
                    printf("\nOnly %d items available.\n", temp->stock);
                    return;
                }

                cart[i].quantity = quantity;
                printf("\nCart quantity updated successfully!\n");
                return;
            }
            else if (choice == 2)
            {
                for (j = i; j < cartCount - 1; j++)
                    cart[j] = cart[j + 1];

                cartCount--;
                printf("\nItem removed from cart successfully!\n");
                return;
            }
            else
            {
                printf("\nInvalid choice!\n");
                return;
            }
        }
    }

    printf("\nFood item not found in cart!\n");
}

void placeOrder(void)
{
    int i;
    struct Order *newOrder;

    if (cartCount == 0)
    {
        printf("\nYour cart is empty!\n");
        return;
    }
    if (queueCount == MAX_PENDING_ORDERS)
    {
        printf("\nPending order queue is full. Try again later.\n");
        return;
    }

    initializeFoodMenu();

    for (i = 0; i < cartCount; i++)
    {
        temp = head;

        while (temp != NULL && temp->id != cart[i].foodId)
            temp = temp->next;

        if (temp == NULL || cart[i].quantity > temp->stock)
        {
            printf("\nInsufficient stock for %s!\n", cart[i].name);
            return;
        }
    }

    newOrder = malloc(sizeof(struct Order));

    if (newOrder == NULL)
    {
        printf("\nMemory allocation failed!\n");
        return;
    }

    newOrder->token = nextToken++;
    newOrder->itemCount = cartCount;
    newOrder->total = 0;
    strcpy(newOrder->status, "Order Placed");
    newOrder->next = NULL;
    newOrder->hashNext = NULL;

    for (i = 0; i < cartCount; i++)
    {
        newOrder->items[i] = cart[i];

        newOrder->total += cart[i].price * cart[i].quantity;

        temp = head;

        while (temp != NULL && temp->id != cart[i].foodId)
            temp = temp->next;

        temp->stock -= cart[i].quantity;
    }

    if (orderHead == NULL)
    {
        orderHead = newOrder;
        orderTail = newOrder;
    }
    else
    {
        orderTail->next = newOrder;
        orderTail = newOrder;
    }

    insertOrderHash(newOrder);
    enqueueOrder(newOrder);

    printf("\nOrder placed successfully!\n");
    printf("Your Order Token: %d\n", newOrder->token);
    printf("Total Amount: Rs. %.2f\n", newOrder->total);

    cartCount = 0;

    printf("\nPlease keep your token to track your order.\n");
}
void viewBill(void)
{
    int i;
    int token;
    struct Order *order;

    printf("\nEnter Order Token: ");
    scanf("%d", &token);

    order = searchOrderHash(token);

    if (order == NULL)
    {
        printf("\nOrder not found!\n");
        return;
    }

    printf("\n========== CANTEEN BILL ==========\n");
    printf("Order Token: %d\n", order->token);
    printf("Order Status: %s\n", order->status);
    printf("----------------------------------\n");

    for (i = 0; i < order->itemCount; i++)
    {
        printf("Food: %s\n", order->items[i].name);
        printf("Price: Rs. %.2f\n", order->items[i].price);
        printf("Quantity: %d\n", order->items[i].quantity);
        printf("Subtotal: Rs. %.2f\n",
               order->items[i].price * order->items[i].quantity);
        printf("----------------------------------\n");
    }

    printf("Total Amount: Rs. %.2f\n", order->total);
    printf("==================================\n");
}
void trackOrder()
{
    int token;
    struct Order *order;

    printf("\nEnter Order Token: ");
    scanf("%d", &token);

    order = searchOrderHash(token);

    if (order == NULL)
    {
        printf("\nOrder not found!\n");
        return;
    }

    printf("\nOrder Found!\n");
    printf("Order Token: %d\n", order->token);
    printf("Order Status: %s\n", order->status);
    printf("Total Amount: Rs. %.2f\n", order->total);
}

void viewOrderHistory()
{
    struct Order *current;
    int i;

    current = orderHead;

    if (current == NULL)
    {
        printf("\nNo orders found!\n");
        return;
    }

    printf("\n========== ORDER HISTORY ==========\n");

    while (current != NULL)
    {
        printf("\nOrder Token: %d\n", current->token);
        printf("Status: %s\n", current->status);
        printf("Items:\n");

        for (i = 0; i < current->itemCount; i++)
        {
            printf("  %s x %d\n",
                   current->items[i].name,
                   current->items[i].quantity);
        }

        printf("Total Amount: Rs. %.2f\n", current->total);
        printf("-----------------------------------\n");

        current = current->next;
    }
}

void manageFoodItems()
{
    int inCart, k;
    int choice, stock, found, maxId, position, ch;
    float price, newPrice;
    int newStock;
    char name[30], category[20];
    struct Food *current, *previous;
    struct UpdateUndo *action;

    initializeFoodMenu();

    do
    {
        printf("\n--- MANAGE FOOD ITEMS ---\n");
        printf("1. Add Food Item\n");
        printf("2. Update Food Price and Stock\n");
        printf("3. Remove Food Item\n");
        printf("4. Back\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ;
            printf("Invalid input.\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            printf("Enter food name: ");
            scanf("%29s", name);

            printf("Enter category (Breakfast/Lunch/Snacks/Drinks): ");
            scanf("%19s", category);

            printf("Enter price: ");
            if (scanf("%f", &price) != 1 || price <= 0)
            {
                while (getchar() != '\n')
                    ;
                printf("Invalid price.\n");
                break;
            }

            printf("Enter stock: ");
            if (scanf("%d", &stock) != 1 || stock < 0)
            {
                while (getchar() != '\n')
                    ;
                printf("Invalid stock.\n");
                break;
            }

            maxId = 0;
            current = head;

            while (current != NULL)
            {
                if (current->id > maxId)
                    maxId = current->id;

                current = current->next;
            }

            addFoodNode(maxId + 1, name, category, price, stock);

            current = head;
            while (current != NULL && current->id != maxId + 1)
                current = current->next;

            if (current == NULL)
            {
                printf("Could not add food item.\n");
                break;
            }

            action = malloc(sizeof(struct UpdateUndo));

            if (action == NULL)
            {
                printf("Warning: Undo unavailable for this action.\n");
            }
            else
            {
                action->type = UNDO_ADD;
                action->foodId = maxId + 1;
                pushUndo(action);
            }

            printf("Food item added successfully. ID: %d\n", maxId + 1);
            break;

        case 2:
            printf("Enter food ID or name to update: ");
            scanf("%29s", name);

            current = head;
            found = 0;

            while (current != NULL)
            {
                if (_stricmp(current->name, name) == 0 ||
                    (atoi(name) > 0 && current->id == atoi(name)))
                {
                    found = 1;
                    break;
                }

                current = current->next;
            }

            if (!found)
            {
                printf("Food item not found.\n");
                break;
            }

            printf("Food: %s\n", current->name);
            printf("1. Update Price Only\n");
            printf("2. Update Stock Only\n");
            printf("3. Update Both\n");
            printf("Enter choice: ");

            if (scanf("%d", &ch) != 1)
            {
                while (getchar() != '\n')
                    ;
                printf("Invalid choice.\n");
                break;
            }

            if (ch < 1 || ch > 3)
            {
                printf("Invalid choice.\n");
                break;
            }

            newPrice = current->price;
            newStock = current->stock;

            if (ch == 1 || ch == 3)
            {
                printf("Enter new price: ");

                if (scanf("%f", &newPrice) != 1 || newPrice <= 0)
                {
                    while (getchar() != '\n')
                        ;
                    printf("Invalid price.\n");
                    break;
                }
            }

            if (ch == 2 || ch == 3)
            {
                printf("Enter new stock: ");

                if (scanf("%d", &newStock) != 1 || newStock < 0)
                {
                    while (getchar() != '\n')
                        ;
                    printf("Invalid stock.\n");
                    break;
                }
            }

            action = malloc(sizeof(struct UpdateUndo));

            if (action == NULL)
            {
                printf("Memory allocation failed. Update cancelled.\n");
                break;
            }

            action->type = UNDO_UPDATE;
            action->foodId = current->id;
            action->oldPrice = current->price;
            action->oldStock = current->stock;
            pushUndo(action);

            current->price = newPrice;
            current->stock = newStock;

            printf("Food item updated successfully.\n");
            break;

        case 3:
            printf("Enter food ID or name to remove: ");
            scanf("%29s", name);

            current = head;
            previous = NULL;
            found = 0;
            position = 0;

            while (current != NULL)
            {
                if (_stricmp(current->name, name) == 0 ||
                    (atoi(name) > 0 && current->id == atoi(name)))
                {
                    found = 1;
                    break;
                }

                previous = current;
                current = current->next;
                position++;
            }

            if (!found)
            {
                printf("Food item not found.\n");
                break;
            }
            inCart = 0;

            for (k = 0; k < cartCount; k++)
            {
                if (cart[k].foodId == current->id)
                {
                    inCart = 1;
                    break;
                }
            }

            if (inCart)
            {
                printf("\nCannot remove item because it is in a cart.\n");
                break;
            }

            action = malloc(sizeof(struct UpdateUndo));

            if (action == NULL)
            {
                printf("Memory allocation failed. Removal cancelled.\n");
                break;
            }

            action->type = UNDO_REMOVE;
            action->foodData = *current;
            action->foodData.next = NULL;
            action->position = position;
            pushUndo(action);
            if (previous == NULL)
                head = current->next;
            else
                previous->next = current->next;

            printf("%s removed successfully.\n", current->name);
            free(current);
            break;

        case 4:
            printf("Returning to staff menu...\n");
            break;

        default:
            printf("Invalid choice.\n");
        }

    } while (choice != 4);
}

void viewStaffOrders()
{
    struct Order *current;
    int choice, found = 0;

    printf("\n--- VIEW ORDERS ---\n");
    printf("1. View All Orders\n");
    printf("2. View Pending Orders\n");
    printf("Enter choice: ");

    if (scanf("%d", &choice) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("Invalid choice.\n");
        return;
    }

    if (choice != 1 && choice != 2)
    {
        printf("Invalid choice.\n");
        return;
    }

    current = orderHead;

    while (current != NULL)
    {
        if (choice == 1 || strcmp(current->status, "Pending") == 0 || strcmp(current->status, "Order Placed") == 0)
        {
            printf("\nToken: %d\n", current->token);
            if (strcmp(current->status, "Order Placed") == 0)
                printf("Status: Pending\n");
            else
                printf("Status: %s\n", current->status);
            printf("Items:\n");

            for (int i = 0; i < current->itemCount; i++)
            {
                printf("%s x %d = Rs. %.2f\n",
                       current->items[i].name,
                       current->items[i].quantity,
                       current->items[i].price * current->items[i].quantity);
            }

            printf("Total: Rs. %.2f\n", current->total);
            found = 1;
        }

        current = current->next;
    }

    if (!found)
        printf("No matching orders found.\n");
}

void processNextOrder()
{
    struct Order *order;

    order = dequeueOrder();

    if (order == NULL)
    {
        printf("\nNo pending orders to process.\n");
        return;
    }

    strcpy(order->status, "Preparing");

    printf("\nOrder accepted for preparation!\n");
    printf("Order Token: %d\n", order->token);
    printf("Status: %s\n", order->status);
}
void searchStaffOrder()
{
    int token;
    struct Order *order;

    printf("\nEnter order token: ");
    scanf("%d", &token);

    order = searchOrderHash(token);

    if (order == NULL)
    {
        printf("\nOrder not found.\n");
        return;
    }

    printf("\nOrder Details\n");
    printf("Token: %d\n", order->token);
    printf("Total: Rs. %.2f\n", order->total);
    if (strcmp(order->status, "Order Placed") == 0)
        printf("Status: Pending\n");
    else
        printf("Status: %s\n", order->status);

    printf("\nItems:\n");

    for (int i = 0; i < order->itemCount; i++)
    {
        printf("%s x %d - Rs. %.2f\n",
               order->items[i].name,
               order->items[i].quantity,
               order->items[i].price * order->items[i].quantity);
    }
}
void updateOrderStatus()
{
    int token, choice;
    struct Order *order;

    printf("\nEnter order token: ");
    scanf("%d", &token);

    order = searchOrderHash(token);

    if (order == NULL)
    {
        printf("\nOrder not found.\n");
        return;
    }

    printf("\nCurrent Status: %s\n", order->status);
    printf("\n1. Preparing");
    printf("\n2. Ready");
    printf("\n3. Completed");
    printf("\nEnter new status: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        strcpy(order->status, "Preparing");
        break;

    case 2:
        strcpy(order->status, "Ready");
        break;

    case 3:
        strcpy(order->status, "Completed");
        break;

    default:
        printf("\nInvalid choice.\n");
        return;
    }
    removeOrderFromQueue(order->token);
    printf("\nOrder status updated successfully!\n");
    printf("Token: %d\n", order->token);
    printf("New Status: %s\n", order->status);
}
void SalesReport()
{
    struct Order *current = orderHead;
    float totalSales = 0;
    int completedOrders = 0;

    printf("\n========== SALES REPORT ==========\n");

    while (current != NULL)
    {
        if (strcmp(current->status, "Completed") == 0)
        {
            totalSales += current->total;
            completedOrders++;

            printf("\nToken: %d", current->token);
            printf("\nAmount: Rs. %.2f\n", current->total);
        }

        current = current->next;
    }

    printf("\n----------------------------------------\n");
    printf("Completed Orders: %d\n", completedOrders);
    printf("Total Sales: Rs. %.2f\n", totalSales);
    printf("========================================\n");
}
void viewCompletedOrders()
{
    struct Order *current = orderHead;
    int found = 0;

    printf("\n========== COMPLETED ORDERS ==========\n");

    while (current != NULL)
    {
        if (strcmp(current->status, "Completed") == 0)
        {
            found = 1;

            printf("\nToken: %d\n", current->token);
            printf("Total: Rs. %.2f\n", current->total);
            printf("Status: %s\n", current->status);
            printf("Items:\n");

            for (int i = 0; i < current->itemCount; i++)
            {
                printf("%s x %d\n",
                       current->items[i].name,
                       current->items[i].quantity);
            }

            printf("--------------------------------------\n");
        }

        current = current->next;
    }

    if (!found)
        printf("\nNo completed orders found.\n");

    printf("======================================\n");
}

void popularFoodReport()
{
    initializeFoodMenu();
    struct Order *current;
    struct Food *food;
    char names[100][30];
    int counts[100] = {0};
    int n = 0, i, j, found, tempCount;
    char tempName[30];

    for (food = head; food != NULL && n < 100; food = food->next)
    {
        strcpy(names[n], food->name);
        counts[n] = 0;
        current = orderHead;

        while (current != NULL)
        {
            found = 0;

            for (i = 0; i < current->itemCount; i++)
            {
                if (strcmp(current->items[i].name, food->name) == 0)
                {
                    found = 1;
                    break;
                }
            }

            if (found)
                counts[n]++;

            current = current->next;
        }

        n++;
    }

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (counts[j] > counts[i])
            {
                tempCount = counts[i];
                counts[i] = counts[j];
                counts[j] = tempCount;

                strcpy(tempName, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], tempName);
            }
        }
    }

    printf("\n========== TOP 3 POPULAR FOOD ITEMS ==========\n");

    found = 0;

    for (i = 0; i < n && found < 3; i++)
    {
        if (counts[i] > 0)
        {
            printf("\n%d. %s", found + 1, names[i]);
            printf("\n   Number of Orders: %d\n", counts[i]);
            found++;
        }
    }

    if (found == 0)
        printf("\nNo orders found.\n");

    printf("\n==============================================\n");
}

void stockReport()
{
    initializeFoodMenu();
    struct Food *current = head;
    int found = 0;

    printf("\n========== STOCK REPORT ==========\n");

    while (current != NULL)
    {
        printf("\nFood: %s", current->name);
        printf("\nAvailable Stock: %d", current->stock);

        if (current->stock == 0)
            printf("\nStatus: OUT OF STOCK\n");
        else if (current->stock <= 5)
            printf("\nStatus: LOW STOCK\n");
        else
            printf("\nStatus: AVAILABLE\n");

        found = 1;
        current = current->next;
    }

    if (!found)
        printf("\nNo food items available.\n");

    printf("\n==================================\n");
}
void undoFoodUpdate(void)
{
    struct UpdateUndo *action;
    struct Food *current, *previous, *restored;
    int i;

    action = popUndo();

    if (action == NULL)
    {
        printf("\nNothing to undo.\n");
        return;
    }

    switch (action->type)
    {
    case UNDO_UPDATE:
        current = head;

        while (current != NULL && current->id != action->foodId)
            current = current->next;

        if (current == NULL)
        {
            printf("\nFood item not found.\n");
            pushUndo(action);
            return;
        }

        current->price = action->oldPrice;
        current->stock = action->oldStock;

        printf("\nPrevious price and stock restored.\n");
        break;

    case UNDO_ADD:
        current = head;
        previous = NULL;

        while (current != NULL && current->id != action->foodId)
        {
            previous = current;
            current = current->next;
        }

        if (current == NULL)
        {
            printf("\nAdded food item not found.\n");
            pushUndo(action);
            return;
        }

        if (previous == NULL)
            head = current->next;
        else
            previous->next = current->next;

        free(current);

        printf("\nLast added food item removed.\n");
        break;

    case UNDO_REMOVE:
        current = head;

        while (current != NULL &&
               current->id != action->foodData.id)
            current = current->next;

        if (current != NULL)
        {
            printf("\nFood ID already exists. Cannot restore.\n");
            pushUndo(action);
            return;
        }

        restored = malloc(sizeof(struct Food));

        if (restored == NULL)
        {
            printf("\nMemory allocation failed.\n");
            pushUndo(action);
            return;
        }

        *restored = action->foodData;
        restored->next = NULL;

        if (action->position == 0 || head == NULL)
        {
            restored->next = head;
            head = restored;
        }
        else
        {
            current = head;

            for (i = 0; i < action->position - 1 &&
                        current->next != NULL;
                 i++)
                current = current->next;

            restored->next = current->next;
            current->next = restored;
        }

        printf("\nRemoved food item restored.\n");
        break;

    default:
        printf("\nInvalid undo action.\n");
        pushUndo(action);
        return;
    }

    free(action);
}