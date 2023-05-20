#ifndef RESTAURANT_H
#define RESTAURANT_H

#define SIZE 100
#define NUM_MENU 9

#include "menu.h"

typedef struct restaurant_tag
{
    char res_name[SIZE];
    char res_address[SIZE];
    int no_of_seats;
    Food menu[NUM_MENU];
    char res_category[SIZE];
    char food_category[SIZE];
    int no_of_orders;

} Restaurant;


typedef struct restaurant_node_tag
{
    Restaurant res;
    struct restaurant_node_tag *left;
    struct restaurant_node_tag *right;

} rNode;


rNode* create_res_Node(Restaurant r);

void r_inorderTraversal(rNode*);

int r_height(rNode *root);

int r_getBalance(rNode *rnode);

rNode *r_rightRotate(rNode *y);

rNode *r_leftRotate(rNode *x);

rNode* r_insert(rNode* node, Restaurant key);

rNode *create_res_tree(Restaurant r_arr[]);



#endif