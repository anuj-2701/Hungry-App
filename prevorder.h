#ifndef PREV_H
#define PREV_H

#define SIZE 100

typedef struct prev_orders_tag{
    int p_ord_no;
    char item_name[SIZE];
    char r_name[SIZE];
} Prev_order;

typedef struct prevorder_node_tag{
    Prev_order p_order;
    struct prevorder_node_tag *left;
    struct prevorder_node_tag *right;
} poNode;

#endif