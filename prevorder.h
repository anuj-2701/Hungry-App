#ifndef PREV_H
#define PREV_H
#include "date.h"
#define SIZE 100

typedef struct prev_orders_tag{
    char item_name[SIZE];
    char r_name[SIZE];
    Date order_date;
} Prev_order;

typedef struct prevorder_node_tag{
    Prev_order p_order;
    struct prevorder_node_tag *next;
} poNode;

#endif