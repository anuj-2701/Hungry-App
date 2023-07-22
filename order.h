#ifndef ORDER_H
#define ORDER_H

#include "agent.h"
#include "user.h"
#include "date.h"

#define SIZE 100

typedef struct order_tag{
    char cus_name[SIZE];
    char add[SIZE];
    long long Phone_no;
    char Eating_joint[SIZE];
    char item[SIZE];
    Date d;
    aNode *ord_ag_ptr;
    uNode *ord_u_ptr;
} Order;

typedef struct Node_tag{
    Order ord;
    struct Node_tag *next;
} oNode;

typedef struct order_list_tag{
    oNode *front;
    oNode *rear;
} order_list;



#endif
