#include "order.h"
#include "agent.h"
#include "agent.c"
#include "menu.h"
#include "restaurant.h"
#include "date.h"
#include "prevorder.h"
#include "prevorder.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{FALSE,TRUE} Boolean;

order_list list;


void initialize_order_list(order_list *p){
    p->front=NULL;
    p->rear=NULL;
}



Boolean isOrderlist_empty(order_list *p){
    Boolean retval;
    if(p->front==NULL&&p->rear==NULL){
        retval=TRUE;
    }
    else{
        retval=FALSE;
    }
    return retval;
}

void Insert(order_list *o,oNode *p){
    if(isOrderlist_empty(o)){
        o->front=o->rear=p;
    }
    else{
        o->rear->next=p;
        o->rear=p;
    }
}

// void allotOrder(order_list *o, oNode *p)
// {
//     oNode *del;
//     if (isOrderlist_empty)
//     {
//         printf("all orders delivered\n");
//     }
//     else
//     {
//         del = o->front;
//         o->front = o->front->next;
//         if (o->front == NULL)
//         {
//             o->rear = NULL;
//         }
//         free(del);
//     }
// }

void initialize_order(Order *o){
    o->cus_name[0] = '\0';
    o->add[0] = '\0';
    o->Phone_no =0;
    o->Eating_joint[0] = '\0';
    o->item[0] ='\0';
    o->d.day=0;
    o->d.month=0;
    o->d.year=0;
    o->ord_ag_ptr=NULL;
    o->ord_u_ptr = NULL;
}

void print_order_details(oNode *p){
    printf("ordered by: %s\n",p->ord.cus_name);
    printf("will be delivered at: %s\n",p->ord.add);
    printf("Item ordered is : %s\n",p->ord.item);
}


void cancel_order(order_list *o,char n[],char m[]){
    oNode *p;
    oNode *z=o->front;
    int flag=0;
    while(z&&flag==0){
        if(strcmp(z->ord.cus_name,n)==0&&strcmp(z->ord.item,m)==0){
            p=z;
            flag=1;
        }
        else{
            z=z->next;
        }
    }

    if(flag==0){
        printf("order not found");
        return;
    }

    // p is pointing to the node to be deleted.

    oNode *t=o->front,*del,*r=NULL;
    if(p==o->front){
        del=o->front;
        o->front=o->front->next;
        if(o->front==NULL){
            o->rear=NULL;
        }
        // freeing agent
        t->ord.ord_ag_ptr->agent.free = YES;
        t->ord.ord_ag_ptr = NULL;

        free(del);
    }
    else{
        while(t){
            if(t==p){
                del=t;
                r->next=t->next;
                if(r->next==NULL){
                    o->rear=r;
                }
                // freeing agent
                t->ord.ord_ag_ptr->agent.free = YES;
                t->ord.ord_ag_ptr = NULL;

                free(del);
            }
            else{
                r=t;
                t=t->next;
            }
        }
    }
    
}

void Order_placing(char n[],char a[],long long no,char eat[],char m[],aNode *ap,uNode *u){
    aNode *aptr = ap;
    oNode *t;
    
    Date dm;
    printf("enter the date-Day,month,year");
    scanf("%d %d %d",&dm.day,&dm.month,&dm.year);
    
    t=(oNode*)malloc(sizeof(oNode));
    strcpy(t->ord.cus_name,n);
    strcpy(t->ord.add,a);
    t->ord.Phone_no=no;
    strcpy(t->ord.Eating_joint,eat);
    strcpy(t->ord.item,m);
    t->next=NULL;
    t->ord.ord_u_ptr=u;
    t->ord.d=dm;
    
    Insert(&list,t);

    int flag=0;
    while(aptr&&flag==0){
        if(aptr->agent.free == YES){
            flag=1;
            
            print_order_details(t);
            print_agent_details(aptr);

            aptr->agent.free = NO;
            t->ord.ord_ag_ptr = aptr;
        }
        else{
            aptr=aptr->next;
        }
    }
    if(flag==0){
        printf("No agent is free please wait for sometime\n");
    }
    
}

void delivery(rNode *r){
	oNode *p,*del;
	aNode *ag;
	poNode *pre;
	uNode *u;
	
	

	if(isOrderlist_empty(&list)){
		printf("ALL order delivered\n");
	}
	else{
        // increment no of orders from that restaurant
        r->res.no_of_orders++;

		p=list.front;
		del=p;
		u=p->ord.ord_u_ptr;
		
		pre=(poNode*)malloc(sizeof(poNode));
		strcpy(pre->p_order.item_name,p->ord.item);
		strcpy(pre->p_order.r_name,p->ord.Eating_joint);
		pre->p_order.order_date=p->ord.d;
		u->user.pn=update_preOrder(u,pre);
		
		list.front=list.front->next;
		if(list.front==NULL){
			list.rear=NULL;
		}
		ag=p->ord.ord_ag_ptr;
		ag->agent.free=YES;
		printf("order delivered to %s by agent %s\n",p->ord.cus_name,ag->agent.name);



		//ag=NULL;
		rNode *t=r;
		int flag=0,prime;
		int cost;
		while(t&&flag==0){
			if(strcmp((t->res.res_name),p->ord.Eating_joint)==0){
				prime=0;
                t->res.no_of_orders++;
				for(int i=0;i<NUM_MENU&&prime==0;i++){
					if(strcmp(t->res.menu[i].fname,p->ord.item)==0){
						prime=1;
						flag=1;
						cost=t->res.menu[i].price;
                        t->res.menu[i].num_orders++;
					}
				}
			}
			t=t->next;
		}
		ag->agent.curr_acc_comm+=(0.1)*cost;

		free(p);	
	}
}

void print_live_orders(){
    oNode *p = list.front;

    while(p){
        printf("ordered: %s",p->ord.item);
        printf("ordered from: %s",p->ord.Eating_joint);
        printf("ordered by: %s",p->ord.cus_name);
        printf("ordered on: %d/%d/%d",p->ord.d.day,p->ord.d.month,p->ord.d.year);

        p=p->next;
    }

}
