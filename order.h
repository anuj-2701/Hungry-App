#ifndef ORDER_H
#define ORDER_H

#include "agent.h"
#include "user.h"
//#include "date.h"

#define SIZE 100

typedef struct order_tag{
    int order_no;
    char cus_name[SIZE];
    long long Phone_no;
    char res[SIZE];
    char item[SIZE];
    //Date d;
    aNode *ord_ag_ptr;
    uNode *ord_u_ptr;
    int cost;
} Order;

typedef struct order_tree_tag{
    Order ord;
    struct order_tree_tag *left;
    struct order_tree_tag *right;

} oNode;


#endif