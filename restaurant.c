
#include "order.c"
#include "restaurant.h"
#include "menu.h"
#include <stdlib.h>
#include <stdio.h>
#include "mergesort.c"
#include <string.h>

void initialize_res(Restaurant *p){
    p->address[0]='\0';
    p->no_of_seats=0;
    for(int i=0;i<NUM_MENU;i++){
    	p->menu[i].fname[0]='\0';
    	p->menu[i].price=0;
        p->menu[i].num_orders = 0;
    }
    p->res_category[0]='\0';
    p->food_category[0]='\0';
    p->res_name[0] = '\0';
}

rNode* create_res_list(int n){
    rNode *p,*q,*t;
    p=(rNode*)malloc(sizeof(rNode));
    initialize_res(&(p->res));
    p->next=NULL;
    q=p;
    for(int i=1;i<n;i++){
        t=(rNode*)malloc(sizeof(rNode));
        initialize_res(&t->res);
        q->next=t;
        q=t;
        t->next=NULL;
    }
    return p;

}

void set_res_details(rNode *r, char n[], char c[], char f[],char a[]){
    strcpy(r->res.res_name,n);
    strcpy(r->res.res_category,c);
    strcpy(r->res.food_category,f);
    strcpy(r->res.address,a);

}

void take_res_input_and_set(rNode *res_list,int num_res){
    rNode *p;
    p=res_list;
    for(int i=0;i<num_res;i++){
        char name[SIZE],cat[SIZE],food[SIZE],add[SIZE];
        printf("enter name\n");
        scanf("%s",name);
        printf("enter restaurant category: ");
        scanf("%s",cat);
        printf("enter food category: ");
        scanf("%s",food);
        printf("enter address: ");
        scanf("%s",add);
        set_res_details(p,name,cat,food,add);
        p=p->next;
    }
}




// --------------------- QUESTION 1  ---------------------
void search_by_res_category(rNode *r, char c[] ){
    rNode *p=r;
    int flag=0;
    while(p){
        if(strcmp(c,p->res.res_category)==0){
            printf("%s\n",p->res.res_name);
            flag=1;
        }
        p=p->next;
    }
    if(!flag){
        printf("none found :( ");
    }
}

void search_by_food_category(rNode *r, char f[]){
    rNode *p=r;
    int flag=0;
    while(p){
        if(strcmp(f,p->res.food_category)==0){
            printf("%s\n",p->res.res_name);
            flag=1;
        }
        p=p->next;
    }
    if(!flag){
        printf("none found :( ");
    }
}

void search_by_area(rNode *r, char a[]){
    rNode *p=r;
    int flag=0;
    while(p){
        if(strcmp(a,p->res.address)==0){
            printf("%s\n",p->res.res_name);
            flag=1;
        }
        p=p->next;
    }
    if(!flag){
        printf("none found :( ");
    }
}



void FindFavoriteFoodsAcrossRestaurants(int N){
	oNode *o=list.front;
	item *favlist=NULL,*last=NULL;
	while(o){
		if(favlist==NULL){
			item *t=(item*)malloc(sizeof(item));
			t->count=1;
			strcpy(t->fname,o->ord.item);
			t->next=NULL;
			favlist=t;
			last=t;
		}
		else{
			int flag=0;
			item *l=favlist;
			while(l&&flag==0){
				if(strcmp(l->fname,o->ord.item)==0){
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
				strcpy(t->fname,o->ord.item);
				t->next=NULL;
				last->next=t;
				last=t;
			}
		}
		o=o->next;
	}
	favlist=mergeSort(favlist);
    favlist = reverseList(favlist);
	last=favlist;
	for(int i=0;i<3&&last;i++){
		printf("The %d favourite food item in restaurant is %s \n",i+1,last->fname);
		last=last->next;
	}
	
	
}
