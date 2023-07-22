#include "user.h"
#include<stdio.h>
#include<stdlib.h>
//#include "mergesort.c"
#include "menu.h"
#include "restaurant.c"
#include "date.h"


void initialize_user(User *u){
    u->user_id = 0;
    u->name[0] = '\0';
    u->address[0] = '\0';
    u->u_phone_no = 0;
    
    u->pn = NULL;

}

uNode* updateUser(uNode *p,char n[],char a[],int id,long long no){
	int flag=0;
	while(flag==0&&p->user.user_id!=0&&p){
		if(strcmp(p->user.name,n)==0){
			flag=1;
		}
		else{
			p=p->next;
		}
	}
	if(flag==0){
		strcpy(p->user.name,n);
		strcpy(p->user.address,a);
		p->user.user_id=id;
		p->user.u_phone_no=no;
	}
	return p;
}


uNode* create_user_list(int n){
    uNode *p,*q,*t;
    p=(uNode*)malloc(sizeof(uNode));
    initialize_user(&(p->user));
    p->next=NULL;
    q=p;
    for(int i=1;i<n;i++){
        t=(uNode*)malloc(sizeof(uNode));
        initialize_user(&t->user);
        q->next=t;
        q=t;
        t->next=NULL;
    }
    return p;
}

int inthreemonths(Date x,Date y){
	int retval=0;
	if(x.year==y.year){
		if(y.month-x.month<=3){
			retval=1;
		}
	}
	return retval;
}

void Find_fav_food(uNode *ulist,int id){
	uNode *u=ulist;
	int flag=0;
	uNode *ptr;
	Date da;
	printf("enter the present date:day,month,year");
	scanf("%d %d %d ",&da.day,&da.month,&da.year);
	while(u&&flag==0){
		if(u->user.user_id==id){
			ptr=u;
			flag=1;
		}
		else{
			u=u->next;
		}
	}
	poNode *p;
	p=ptr->user.pn;
	item *favlist=NULL,*last=NULL;
	while(p){
		if(favlist==NULL&&inthreemonths(p->p_order.order_date,da)){
			item *t=(item*)malloc(sizeof(item));
			t->count=1;
			strcpy(t->fname,p->p_order.item_name);
			t->next=NULL;
			favlist=t;
			last=t;
		}
		else{
			int flag=0;
			item *l=favlist;
			while(l&&flag==0){
				if(strcmp(l->fname,p->p_order.item_name)==0){
					flag=1;
					l->count++;
				}
				else{
					l=l->next;
				}
			}
			if(l==NULL&&inthreemonths(p->p_order.order_date,da)){
				item *t=(item*)malloc(sizeof(item));
				t->count=1;
				strcpy(t->fname,p->p_order.item_name);
				t->next=NULL;
				last->next=t;
				last=t;
			}
		}
		p=p->next;
	}
	favlist=mergeSort(favlist);
	last=favlist;
	for(int i=0;i<3&&last;i++){
		printf("The %d favourite food item is %s \n",i+1,last->fname);
		last=last->next;
	}
}

void Find_favfood(uNode *ulist,int id){
	uNode *u=ulist;
	int flag=0;
	uNode *ptr;
	while(u&&flag==0){
		if(u->user.user_id==id){
			ptr=u;
			flag=1;
		}
		else{
			u=u->next;
		}
	}
	poNode *p;
	p=ptr->user.pn;
	item *favlist =NULL,*last=NULL;
	while(p){
		if(favlist==NULL){
			item *t=(item*)malloc(sizeof(item));
			t->count=1;
			strcpy(t->fname,p->p_order.item_name);
			t->next=NULL;
			favlist=t;
			last=t;
		}
		else{
			int flag=0;
			item *l=favlist;
			while(l&&flag==0){
				if(strcmp(l->fname,p->p_order.item_name)==0){
					flag=1;
					l->count++;
				}
				else{
					l=l->next;
				}
			}
			if(l==NULL){
				item *t=(item*)malloc(sizeof(item));
				t->count=1;
				strcpy(t->fname,p->p_order.item_name);
				t->next=NULL;
				last->next=t;
				last=t;
			}
		}
		p=p->next;
	}
	favlist=mergeSort(favlist);
	favlist = reverseList(favlist);
	last=favlist;
	for(int i=0;i<3&&last;i++){
		printf("The %d favourite food item of user is %s \n",i+1,last->fname);
		last=last->next;
	}
}
