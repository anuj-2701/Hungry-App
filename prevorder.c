#include "prevorder.h"
#include "user.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void update_date(Date date,int d,int m, int y){
    date.day = d;
    date.month = m;
    date.year = y;
}

poNode* update_preOrder(uNode *ptr,poNode *p){
	poNode *t=ptr->user.pn;
	if(ptr){
		if(t){
			while(t->next!=NULL){
				t=t->next;
			}
			t->next=p;
			t=p;
			t->next=NULL;
		}
		else{
			ptr->user.pn=p;
		}
	}
	return ptr->user.pn;
}