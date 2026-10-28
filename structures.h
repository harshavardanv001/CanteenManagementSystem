#ifndef STRUCTURES_H
#define STRUCTURES_H
#define HASH_SIZE 10
#define MAX_PENDING_ORDERS 100
#define UNDO_UPDATE 1
#define UNDO_ADD 2
#define UNDO_REMOVE 3
struct Food         //LINKED LIST FOR STORING FOOD ITEMS
{
    int id;
    char name[30];
    char category[20];
    float price;
    int stock;
    struct Food *next;
};


struct CartItem   //STRUCTURE FOR CART
{
    int foodId;
    char name[30];
    float price;
    int quantity;
};

struct Order    //HASH TABLE + LINKED LIST FOR STORING ORDERS
{
    int token;
    struct CartItem items[20];
    int itemCount;
    float total;
    char status[30];
    struct Order *next;
    struct Order *hashNext;
};



extern struct Order *orderQueue[MAX_PENDING_ORDERS]; 
//QUEUE FOR PROCESSING PENDING ORDERS 

struct UpdateUndo   //STACK FOR UNDO OPERATION
{
    int type;
    int foodId;
    float oldPrice;
    int oldStock;
    struct Food foodData;
    int position;
    struct UpdateUndo *next;
};

#endif