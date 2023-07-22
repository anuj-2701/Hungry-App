#ifndef AGENT_H
#define AGENT_H

#define SIZE 100

typedef enum {NO,YES} bool;

typedef struct agent_tag
{
    int agent_id;
    long long a_phone_no;
    char name[SIZE];
    int curr_acc_comm;
    bool free;
    char area[SIZE];
} Agent;

typedef struct agent_node_tag
{
    Agent agent;
    struct agent_node_tag * next;
} aNode;

#endif