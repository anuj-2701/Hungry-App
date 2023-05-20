#ifndef AGENT_H
#define AGENT_H

#define SIZE 100

//typedef enum {NO,YES} bool;

typedef struct agent_tag
{
    int agent_id;
    long long a_phone_no;
    char name[SIZE];
    int curr_acc_comm;
    int free;
    char area[SIZE];
} Agent;

typedef struct agent_node_tag
{
    Agent agent;
    struct agent_node_tag * left;
    struct agent_node_tag * right;
} aNode;


aNode* create_agent_Node(Agent);

void a_inorderTraversal(aNode*);

int a_height(aNode *root);

int a_getBalance(aNode *node);

aNode *a_rightRotate(aNode *y);

aNode *a_leftRotate(aNode *x);

aNode* a_insert(aNode* node, Agent key);

aNode *create_agent_tree(Agent a[]);



#endif