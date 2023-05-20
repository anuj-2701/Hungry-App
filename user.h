#ifndef USER_H
#define USER_H
#define SIZE 100

#include "prevorder.h"

typedef struct user_tag
{
    int user_id;
    char name[SIZE];
    char address[SIZE];
    long long u_phone_no;
    poNode *pn;
    int total_p_ord;
} User;

typedef struct user_node_tag
{
    User user;
    struct user_node_tag *left;
    struct user_node_tag *right;
    
} uNode;

#endif