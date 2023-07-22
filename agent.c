#include "agent.h"
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

void initialize_agent(Agent *a){
    a->agent_id = 0;
    a->name[0] = '\0';
    a->a_phone_no = 0;
    a->curr_acc_comm = 0;
    a->free = YES;
}

aNode* create_agent_list(int n){
    aNode *p,*q,*t;
    p = (aNode*)malloc(sizeof(aNode));
    initialize_agent(&(p->agent));
    p->next = NULL;
    q=p;

    for(int i=1;i<n;i++){
        t = (aNode*)malloc(sizeof(aNode));
        initialize_agent(&(t->agent));
        q->next = t;
        q=t;
        t->next = NULL;
    }

    return p;
}

void set_agent_details(aNode *a,int id,char n[],long long l){
    a->agent.agent_id=id;
    strcpy(a->agent.name,n);
    a->agent.a_phone_no=l;
}

void print_agent_details(aNode *p){
    printf("ordered will be delivered by: %s\n",p->agent.name);
    printf("agent id: %d\n",p->agent.agent_id);
    printf("agent phone number: %lld\n",p->agent.a_phone_no);

}

void take_agent_input_and_set(aNode *a_list,int num_agent){
    aNode *p;
    p=a_list;
    for(int i=0;i<num_agent;i++){
        char name[SIZE],food[SIZE],add[SIZE];
        int id;
        long long phone_no;
        printf("enter id: ");
        scanf("%d",&id);
        printf("enter name: ");
        scanf("%s",name);
        printf("enter phone number: ");
        scanf("%lld",&phone_no);
        
        set_agent_details(p,id,name,phone_no);
        p=p->next;
    }
}

void print_agent_list(aNode *a_list){
    aNode *p = a_list;
    while(p){
        printf("agent id: %d\n",p->agent.agent_id);
        printf("agent name: %s\n",p->agent.name);
        printf("phone no: %lld\n",p->agent.a_phone_no);
        if(p->agent.free == YES){
            printf("agent is free");
        }
        else{
            printf("agent is not free");
        }

        p=p->next;
    }
}

void print_area_wise_agents(aNode *a_list){
    aNode *a = a_list;
    printf("----- Area1 ------\n");
    while(a){
        if(strcmp(a->agent.area ,"Area1")==0){
            printf("%s\n",a->agent.name);
        }
    }
    a=a_list;
    printf("----- Area2 ------\n");
    while(a){
        if(strcmp(a->agent.area ,"Area2")==0){
            printf("%s\n",a->agent.name);
        }
    }
    a=a_list;
    printf("----- Area3 ------\n");
    while(a){
        if(strcmp(a->agent.area ,"Area3")==0){
            printf("%s\n",a->agent.name);
        }
    }

}