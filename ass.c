#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "restaurant.h"
#include "agent.h"
#include "user.h"
#include "prevorder.h"
#include "menu.h"
#include "order.h"

#define SIZE 100

oNode *order_tree=NULL;

int count=0;
int delivery_no=0;
static int flag=0;

//-------------------------------------------------------------

rNode* create_res_Node(Restaurant r);

void r_inorderTraversal(rNode*);

int r_height(rNode *root);

int r_getBalance(rNode *rnode);

rNode *r_rightRotate(rNode *y);

rNode *r_leftRotate(rNode *x);

rNode* r_insert(rNode* node, Restaurant key);

rNode *create_res_tree(Restaurant r_arr[]);



aNode* create_agent_Node(Agent);

void a_inorderTraversal(aNode*);

int a_height(aNode *root);

int a_getBalance(aNode *node);

aNode *a_rightRotate(aNode *y);

aNode *a_leftRotate(aNode *x);

aNode* a_insert(aNode* node, Agent key);

aNode *create_agent_tree(Agent a[]);


poNode* p_insert(poNode* node, Prev_order key);

//----------------------------------------------------------


item *Divide(item *lptr)
{
    item *p, *mid;
    mid = p = lptr;
    while (p)
    {
        p = p->next;
        if (p)
        {
            p = p->next;
        }
        if (p)
        {
            mid = mid->next;
        }
    }
    lptr = mid->next;
    mid->next = NULL;
    return lptr;
}

item *merge(item *p, item *q)
{
    item *last, *third;
    if (p->count < q->count)
    {
        third = last = p;
        p = p->next;
        third->next = NULL;
    }
    else
    {
        third = last = q;
        q = q->next;
        third->next = NULL;
    }
    while (p && q)
    {
        if (p->count < q->count)
        {
            last->next = p;
            last = p;
            p = p->next;
            last->next = NULL;
        }
        else
        {
            last->next = q;
            last = q;
            q = q->next;
            last->next = NULL;
        }
    }
    if (p)
    {
        last->next = p;
    }
    if (q)
    {
        last->next = q;
    }
    return third;
}

item *mergeSort(item *head)
{
    // your code here

    item *nptr, *lptr;
    lptr = head;
    if ((lptr != NULL) && (lptr->next != NULL))
    {
        nptr = Divide(lptr);
        lptr = mergeSort(lptr);
        nptr = mergeSort(nptr);
        lptr = merge(lptr, nptr);
    }
    return lptr;
}

item* reverseList(item* start){
    item *head=start,*mid=NULL,*tail=NULL;

    while(head){
        tail = mid;
        mid = head;
        head = head->next;
        mid->next = tail;
    }
    return mid;

}


//---------------------------------------------------------------------------------------

rNode *create_res_Node(Restaurant r){
    rNode *n = (rNode*)malloc(sizeof(rNode));
    
    // strcpy(n->res.res_name,r.res_name);
    // strcpy(n->res.res_address,r.res_address);
    // n->res.no_of_seats = r.no_of_seats;
    // strcpy(n->res.res_category,r.res_category);
    // strcpy(n->res.food_category,r.food_category);
    // n->res.no_of_orders = r.no_of_orders;

    n->res = r;

    n->left = NULL;
    n->right = NULL;

    return n;
}

void r_inorderTraversal(rNode *root){
    if(root){
        r_inorderTraversal(root->left);
        printf("%s ",root->res.res_name);
        r_inorderTraversal(root->right);
    }
}

int r_height(rNode *root){
    int h;
    if(root == NULL){
        h = 0;
    }
    else{
        int left_height = r_height(root->left);
        int right_height = r_height(root->right);

        if(left_height > right_height){
            h = left_height + 1;
        }
        else{
            h = right_height + 1;
        }
    }
    return h;
}

int r_getBalance(rNode *node){
    int retval;
    if(node == NULL){
        retval = 0;
    }
    else{
        retval = r_height(node->left) - r_height(node->right);
    }
    return retval;
}

rNode *r_rightRotate(rNode *y)
{
    rNode *x = y->left;
    rNode *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    // y->height = max(height(y->left),
    //                 height(y->right)) + 1;
    // x->height = max(height(x->left),
    //                 height(x->right)) + 1;
 
    // Return new root
    return x;
}

rNode *r_leftRotate(rNode *x)
{
    rNode *y = x->right;
    rNode *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    // Update heights
    // x->height = max(height(x->left),   
    //                 height(x->right)) + 1;
    // y->height = max(height(y->left),
    //                 height(y->right)) + 1;
 
    // Return new root
    return y;
}

rNode* r_insert(rNode* node, Restaurant key)
{
    rNode *retval = node;
    /* 1. Perform the normal BST insertion */

    if (node == NULL)
        return (create_res_Node(key));
 
    if (strcmp(key.res_name , node->res.res_name) < 0)
        node->left = r_insert(node->left, key);
    else if (strcmp(key.res_name , node->res.res_name) > 0)
        node->right = r_insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;
 
    /* 2. Update height of this ancestor node */
    // node->height = 1 + max(height(node->left),
    //                     height(node->right));
 
    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = r_getBalance(node);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && strcmp(key.res_name , node->left->res.res_name) < 0)
        return r_rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && strcmp(key.res_name , node->right->res.res_name) > 0)
        return r_leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && strcmp(key.res_name , node->left->res.res_name) > 0)
    {
        node->left = r_leftRotate(node->left);
        return r_rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && strcmp(key.res_name , node->right->res.res_name) < 0)
    {
        node->right = r_rightRotate(node->right);
        return r_leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}



rNode *create_res_tree(Restaurant r[]){
    rNode *retval = NULL;
    for(int i=0;i<5;i++){
        retval = r_insert(retval,r[i]);
    }
    return retval;
}

void search_by_res_category(rNode *root,char c[]){
    if(root){
        search_by_res_category(root->left,c);      
        if(strcmp(c,root->res.res_category)==0){
            printf("%s ",root->res.res_name);
        }
        search_by_res_category(root->right,c);   
    }
}

void search_by_food_category(rNode *root,char c[]){
    if(root){
        search_by_food_category(root->left,c);
        if(strcmp(c,root->res.food_category)==0){
            printf("%s ",root->res.res_name);
        }
        search_by_food_category(root->right,c);
    }
}

void search_by_area(rNode *root,char c[]){
    if(root){
        search_by_area(root->left,c);
        if(strcmp(c,root->res.res_address)==0){
            printf("%s ",root->res.res_name);
        }
        search_by_area(root->right,c);
    }
}

rNode *r_search(rNode *root ,char key[]){
 	if(strcmp(root->res.res_name,key)>0){
 		return r_search(root->right,key);
	 }
	 else if(strcmp(root->res.res_name,key)<0){
	 	return r_search(root->left,key);
	 }
	 else{
	 	return root;
	 }
 }


rNode* tree_to_list(rNode *r){
    rNode *root = r;
    while (root) {
        // if root->left is not NULL
        if (root->left != NULL) {
            // set curr node as root->left;
            rNode* curr = root->left;
            // traverse to the extreme right of curr
            while (curr->right) {
                curr = curr->right;
            }
            // join curr->right to root->right
            curr->right = root->right;
            // put root->left to root->right
            root->right = root->left;
            // make root->left as NULL
            root->left = NULL;
        }
        // now go to the right of the root
        root = root->right;
    }
    return r;
}



void FindFavoriteRestaurants(rNode *rlist){
    rNode *r = rlist,*first = rlist, *sec=rlist,*third = rlist;
    int max_orders = -1;

    while(r){
        if(r->res.no_of_orders > max_orders){
            max_orders = r->res.no_of_orders;
            first = r;
        }
        r=r->right;
    }

    r=rlist;
    int sec_max = -1;

    while(r){
        if(r!= first && r->res.no_of_orders >= sec_max){
            sec_max = r->res.no_of_orders;
            sec = r;
        }
        r=r->right;
    }

    r=rlist;
    int third_max = -1;

    while(r){
        if(r!= first && r!= sec && r->res.no_of_orders >= third_max){
            third_max = r->res.no_of_orders;
            third = r;
        }
        r=r->right;
    }

    printf("top 3 restaurants are : ");
    printf("%s \n",first->res.res_name);
    printf("%s \n",sec->res.res_name);
    printf("%s \n",third->res.res_name);

}

void FavoriteRestaurants(rNode *root){
    FindFavoriteRestaurants(tree_to_list(root));
}

// -------------------------------------------------------------------

item* createitem(item *root,char s[]){
	item *favlist=root,*p; 
	p=root;
	while(p){
		if(favlist==NULL){
			item *t=(item*)malloc(sizeof(item));
			t->count=1;
			strcpy(t->fname,s);
			t->next=NULL;
			favlist=t;
		}
		else{
			int flag=0;
			item *l=favlist,*prev;
			while(l&&flag==0){
				if(strcmp(l->fname,s)==0){
					flag=1;
					l->count++;
				}
				else{
					prev=l;
					l=l->next;
				}
			}
			if(l==NULL){
				item *t=(item*)malloc(sizeof(item));
				t->count=1;
				strcpy(t->fname,s);
				t->next=NULL;
				prev->next=t;
			}
		}
		p=p->next;
	}
	return favlist;
}

item* i_inorderTraversal(oNode *root,item *node){
    if(root){
        return i_inorderTraversal(root->left,node);
        node=createitem(node,root->ord.item);
        return i_inorderTraversal(root->right,node);
        
}
	return node;
}

void FindFavoriteFoodsAcrossRestaurants(){
	
	item *favlist=i_inorderTraversal(order_tree,NULL),*last;
	
	favlist=mergeSort(favlist);
    favlist = reverseList(favlist);
	last=favlist;
	for(int i=0;i<3&&last;i++){
		printf("The %d favourite food item in restaurant is %s \n",i+1,last->fname);
		last=last->next;
	}
	
	
}

//------------------------------------------------------------------------------------------

aNode *create_agent_Node(Agent x){
    aNode *n = (aNode*)malloc(sizeof(aNode));

    // n->agent.agent_id=x.agent_id;
    // strcpy(n->agent.area,x.area);
    // n->agent.a_phone_no=x.a_phone_no;
    // n->agent.free=0;
    // strcpy(n->agent.name,x.name);

    n->agent = x;

    n->left = NULL;
    n->right = NULL;

    return n;
}


void a_inorderTraversal(aNode *root){
    if(root){
        a_inorderTraversal(root->left);
        printf("%d ",root->agent.agent_id);
        a_inorderTraversal(root->right);
    }
}


int a_height(aNode *root){
    int h;
    if(root == NULL){
        h = 0;
    }
    else{
        int left_height = a_height(root->left);
        int right_height = a_height(root->right);

        if(left_height > right_height){
            h = left_height + 1;
        }
        else{
            h = right_height + 1;
        }
    }
    return h;
}

int a_getBalance(aNode *node){
    int retval;
    if(node == NULL){
        retval = 0;
    }
    else{
        retval = a_height(node->left) - a_height(node->right);
    }
    return retval;
}

aNode *a_rightRotate(aNode *y)
{
    aNode *x = y->left;
    aNode *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    // y->height = max(height(y->left),
    //                 height(y->right)) + 1;
    // x->height = max(height(x->left),
    //                 height(x->right)) + 1;
 
    // Return new root
    return x;
}

aNode *a_leftRotate(aNode *x)
{
    aNode *y = x->right;
    aNode *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    // Update heights
    // x->height = max(height(x->left),   
    //                 height(x->right)) + 1;
    // y->height = max(height(y->left),
    //                 height(y->right)) + 1;
 
    // Return new root
    return y;
}

aNode* a_insert(aNode* node, Agent key)
{
    aNode *retval = node;
    /* 1. Perform the normal BST insertion */

    if (node == NULL)
        return (create_agent_Node(key));
 
    if (key.agent_id < node->agent.agent_id)
        node->left = a_insert(node->left, key);
    else if (key.agent_id > node->agent.agent_id)
        node->right = a_insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;
 
    /* 2. Update height of this ancestor node */
    // node->height = 1 + max(height(node->left),
    //                     height(node->right));
 
    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = a_getBalance(node);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key.agent_id < node->left->agent.agent_id)
        return a_rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && key.agent_id > node->right->agent.agent_id)
        return a_leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && key.agent_id > node->left->agent.agent_id)
    {
        node->left = a_leftRotate(node->left);
        return a_rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && key.agent_id < node->right->agent.agent_id)
    {
        node->right = a_rightRotate(node->right);
        return a_leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}

aNode *create_agent_tree(Agent a[]){
        aNode* retval=NULL;
        for(int i=0;i<5;i++){
            retval=a_insert(retval,a[i]);
        }
        return retval;
    }


//--------------------------------------------------------------------------------------

uNode *create_user_Node(User u){
    uNode *n = (uNode*)malloc(sizeof(uNode));
    n->user = u;
    n->left = NULL;
    n->right = NULL;

    return n;
}

void u_inorderTraversal(uNode *root){
    if(root){
        u_inorderTraversal(root->left);
        printf("%s ",root->user.name);
        u_inorderTraversal(root->right);
    }
}

int u_height(uNode *root){
    int h;
    if(root == NULL){
        h = 0;
    }
    else{
        int left_height = u_height(root->left);
        int right_height = u_height(root->right);

        if(left_height > right_height){
            h = left_height + 1;
        }
        else{
            h = right_height + 1;
        }
    }
    return h;
}

int u_getBalance(uNode *node){
    int retval;
    if(node == NULL){
        retval = 0;
    }
    else{
        retval = u_height(node->left) - u_height(node->right);
    }
    return retval;
}

uNode *u_rightRotate(uNode *y)
{
    uNode *x = y->left;
    uNode *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    // y->height = max(height(y->left),
    //                 height(y->right)) + 1;
    // x->height = max(height(x->left),
    //                 height(x->right)) + 1;
 
    // Return new root
    return x;
}

uNode *u_leftRotate(uNode *x)
{
    uNode *y = x->right;
    uNode *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    // Update heights
    // x->height = max(height(x->left),   
    //                 height(x->right)) + 1;
    // y->height = max(height(y->left),
    //                 height(y->right)) + 1;
 
    // Return new root
    return y;
}

uNode* u_insert(uNode* node, User key)
{
    uNode *retval = node;
    /* 1. Perform the normal BST insertion */

    if (node == NULL)
        return (create_user_Node(key));
 
    if (key.user_id < node->user.user_id)
        node->left = u_insert(node->left, key);
    else if (key.user_id > node->user.user_id)
        node->right = u_insert(node->right, key);
    else // Equal keys are not allowed in BST
        //node->user.pn = p_insert(node->user.pn,p);
        return node;
 
    /* 2. Update height of this ancestor node */
    // node->height = 1 + max(height(node->left),
    //                     height(node->right));
 
    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = u_getBalance(node);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key.user_id < node->left->user.user_id)
        return u_rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && key.user_id > node->right->user.user_id)
        return u_leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && key.user_id > node->left->user.user_id)
    {
        node->left = u_leftRotate(node->left);
        return u_rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && key.user_id < node->right->user.user_id)
    {
        node->right = u_rightRotate(node->right);
        return u_leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}

uNode *u_search(uNode *root ,int key){
 	if(root->user.user_id<key){
 		return u_search(root->right,key);
	 }
	 else if(root->user.user_id>key){
	 	return u_search(root->left,key);
	 }
	 else{
	 	return root;
	 }
 }

 poNode* p_tree_to_list(poNode *r){
    poNode *root = r;
    while (root) {
        // if root->left is not NULL
        if (root->left != NULL) {
            // set curr node as root->left;
            poNode* curr = root->left;
            // traverse to the extreme right of curr
            while (curr->right) {
                curr = curr->right;
            }
            // join curr->right to root->right
            curr->right = root->right;
            // put root->left to root->right
            root->right = root->left;
            // make root->left as NULL
            root->left = NULL;
        }
        // now go to the right of the root
        root = root->right;
    }
    return r;
}

void Find_favfood(uNode *utree,int id){
	uNode *u=u_search(utree,id);
	int flag=0;
	
	poNode *p;
	p=u->user.pn;

    p = p_tree_to_list(p);

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
		p=p->right;
	}
	favlist=mergeSort(favlist);
	favlist = reverseList(favlist);
	last=favlist;
	for(int i=0;i<3&&last;i++){
		printf("The %d favourite food item of user is %s \n",i+1,last->fname);
		last=last->next;
	}
}

void RangeSearch(oNode *root,int id1, int id2){
    if(root){
        RangeSearch(root->left,id1,id2);
        if(root->ord.ord_u_ptr->user.user_id>=id1 && root->ord.ord_u_ptr->user.user_id<=id2){
            printf("order no. %d => %s ordered by %s from %s\n",root->ord.order_no,root->ord.item,root->ord.cus_name,root->ord.res);
        }
        RangeSearch(root->right,id1,id2);
    }
}

// -------------------------------------------------------------------------------------

/*oNode *createNode(int d){
    oNode n = (Node)malloc(sizeof(Node));
    n->data = d;
    n->left = NULL;
    n->right = NULL;

    return n;
}*/

void o_inorderTraversal(oNode *root){
    if(root){
        o_inorderTraversal(root->left);
        printf("%d ",root->ord.order_no);
        o_inorderTraversal(root->right);
    }
}


int o_height(oNode *root){
    int h;
    if(root == NULL){
        h = 0;
    }
    else{
        int left_height = o_height(root->left);
        int right_height = o_height(root->right);

        if(left_height > right_height){
            h = left_height + 1;
        }
        else{
            h = right_height + 1;
        }
    }
    return h;
}

int o_getBalance(oNode *node){
    int retval;
    if(node == NULL){
        retval = 0;
    }
    else{
        retval = o_height(node->left) - o_height(node->right);
    }
    return retval;
}

oNode *o_rightRotate(oNode *y)
{
    oNode *x = y->left;
    oNode *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    // y->height = max(height(y->left),
    //                 height(y->right)) + 1;
    // x->height = max(height(x->left),
    //                 height(x->right)) + 1;
 
    // Return new root
    return x;
}

oNode *o_leftRotate(oNode *x)
{
    oNode *y = x->right;
    oNode *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    // Update heights
    // x->height = max(height(x->left),   
    //                 height(x->right)) + 1;
    // y->height = max(height(y->left),
    //                 height(y->right)) + 1;
 
    // Return new root
    return y;
}

oNode* order_insert(oNode *node,oNode *key)
{
    /* 1. Perform the normal BST insertion */

    if (node == NULL)
    	
        return key;
 
    if (key->ord.order_no < node->ord.order_no)
        node->left = order_insert(node->left, key);
    else if (key->ord.order_no > node->ord.order_no)
        node->right = order_insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;
 
    /* 2. Update height of this ancestor node */
    // node->height = 1 + max(height(node->left),
    //                     height(node->right));
 
    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = o_getBalance(node);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key->ord.order_no < node->left->ord.order_no)
        return o_rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && key->ord.order_no > node->right->ord.order_no)
        return o_leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && key->ord.order_no > node->left->ord.order_no)
    {
        node->left = o_leftRotate(node->left);
        return o_rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && key->ord.order_no < node->right->ord.order_no)
    {
        node->right = o_rightRotate(node->right);
        return o_leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}



void allot_agent(oNode *t,aNode *root){
    if(root){
        allot_agent(t,root->left);
        if(root->agent.free==1&&flag==0){
            flag=1;
        	root->agent.free=0;
            t->ord.ord_ag_ptr = root;
		}
        allot_agent(t,root->right);
    }
}







void order_placing(char n[],long long no,char eat[],char m[],aNode *ap,uNode *u){
	//aNode *aptr = ap;
    oNode *t;
    
    //Date dm;
    // printf("enter the date-Day,month,year");
    // scanf("%d %d %d",&dm.day,&dm.month,&dm.year);
    
    t=(oNode*)malloc(sizeof(oNode));
    t->ord.order_no=++count;
    strcpy(t->ord.cus_name,n);
    t->ord.Phone_no=no;
    strcpy(t->ord.res,eat);
    strcpy(t->ord.item,m);
    t->left=NULL;
    t->right=NULL;
    t->ord.ord_u_ptr=u;
    //t->ord.d=dm;
    
    order_tree=order_insert(order_tree,t);
    printf("Your order no is %d\n",t->ord.order_no);
    printf("Your have ordered %s\n",t->ord.item);
    printf("Restaurant is %s\n",t->ord.res);
    
    allot_agent(t,ap);
    flag=0;
    //t->ord.ord_ag_ptr=allot_agent(ap);
     printf("Agent alloted is %s\n",t->ord.ord_ag_ptr->agent.name);
    printf("Agent phone no is %lld\n",t->ord.ord_ag_ptr->agent.a_phone_no);
    
    
}

oNode * minValueNode(oNode* node)
{
    oNode* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}



oNode *o_delete(oNode *root,int key)
{
     
    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == NULL)
        return root;
 
    // If the key to be deleted is smaller
    // than the root's key, then it lies
    // in left subtree
    if ( key < root->ord.order_no )
        root->left = o_delete(root->left, key);
 
    // If the key to be deleted is greater
    // than the root's key, then it lies
    // in right subtree
    else if( key > root->ord.order_no )
        root->right = o_delete(root->right, key);
 
    // if key is same as root's key, then
    // This is the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) ||
            (root->right == NULL) )
        {
            oNode *temp = root->left ?
                         root->left :
                         root->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
            *root = *temp; // Copy the contents of
                           // the non-empty child
            //temp->ord.ord_ag_ptr->agent.free=1;
            free(temp);
            
            
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            oNode* temp = minValueNode(root->right);
 
            // Copy the inorder successor's
            // data to this node
            root->ord = temp->ord;
 
            // Delete the inorder successor
            root->right = o_delete(root->right,
                                     temp->ord.order_no);
        }
    }
 
    // If the tree had only one node
    // then return
    if (root == NULL)
    return root;
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    // root->height = 1 + max(height(root->left),
    //                        height(root->right));
 
    // STEP 3: GET THE BALANCE FACTOR OF
    // THIS NODE (to check whether this
    // node became unbalanced)
    int balance = o_getBalance(root);
 
    // If this node becomes unbalanced,
    // then there are 4 cases
 
    // Left Left Case
    if (balance > 1 &&
        o_getBalance(root->left) >= 0)
        return o_rightRotate(root);
 
    // Left Right Case
    if (balance > 1 &&
        o_getBalance(root->left) < 0)
    {
        root->left = o_leftRotate(root->left);
        return o_rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 &&
        o_getBalance(root->right) <= 0)
        return o_leftRotate(root);
 
    // Right Left Case
    if (balance < -1 &&
        o_getBalance(root->right) > 0)
    {
        root->right = o_rightRotate(root->right);
        return o_leftRotate(root);
    }
  
    return root;
}



 void cancel_order(int n){
 	
 	order_tree=o_delete(order_tree,n);
    printf("order %d got successfully cancelled!\n",n);

 }
 
 
 
 
 
 
 
 oNode *o_search(oNode *root ,int key){
 	if(root->ord.order_no<key){
 		return o_search(root->right,key);
	 }
	 else if(root->ord.order_no>key){
	 	return o_search(root->left,key);
	 }
	 else{
	 	return root;
	 }
 }


// void delivery(rNode *r){
// 	if(order_tree==NULL){
// 		printf("All orders delivered\n");
// 	}
// 	else{
// 		delivery_no++;
// 		oNode *o=o_search(order_tree,delivery_no);
// 		if(o==NULL){
// 			printf("order was cancelled earlier\n");
// 			return;
// 		}
// 		Prev_order p;
// 		strcpy(	p.item_name,o->ord.item);
// 		strcpy(p.r_name,o->ord.res);

//         o->ord.ord_u_ptr->user.total_p_ord++;

// 		p.p_ord_no=o->ord.ord_u_ptr->user.total_p_ord;

// 		o->ord.ord_u_ptr->user.pn=p_insert(o->ord.ord_u_ptr->user.pn,p);

//         rNode *temp = r_search(r,o->ord.res);

//         temp->res.no_of_orders++;
//         int cost=0;
//         for(int i=0;i<NUM_MENU;i++){
//             if(strcmp(temp->res.menu[i].fname,o->ord.item)==0){
//                 cost=temp->res.menu[i].price;
//                 temp->res.menu[i].num_orders++;
//             }
//         }
//         o->ord.ord_ag_ptr->agent.curr_acc_comm+=(0.1)*cost;

// 		printf("order %d elivered by agent %s to %s\n",delivery_no,o->ord.ord_ag_ptr->agent.name,o->ord.cus_name);

// 		order_tree=o_delete(order_tree,delivery_no);
		
// 	}
	
// }

void delivery(rNode *r){
	if(order_tree==NULL){
		printf("All orders delivered\n");
	}
	else{
        r_inorderTraversal(r);
		delivery_no++;
        printf("hi1\n");
		oNode *o=o_search(order_tree,delivery_no);
        r_inorderTraversal(r);
        printf("hi2\n");
		if(o==NULL){
			printf("order was cancelled earlier\n");
			return;
		}
		Prev_order p;
		strcpy(	p.item_name,o->ord.item);
		strcpy(p.r_name,o->ord.res);
        o->ord.ord_u_ptr->user.total_p_ord++;

		p.p_ord_no=o->ord.ord_u_ptr->user.total_p_ord;

        printf("hi3\n");
		o->ord.ord_u_ptr->user.pn=p_insert(o->ord.ord_u_ptr->user.pn,p);
        printf("hi4\n");
        r_inorderTraversal(r);
        rNode *temp = r_search(r,o->ord.res);
        printf("hi4\n");
        r_inorderTraversal(r);
        temp->res.no_of_orders++;
        printf("%d\n",temp->res.no_of_orders);
        int cost=0;
        for(int i=0;i<NUM_MENU;i++){
            printf("hi\n");
            if(strcmp(temp->res.menu[i].fname,o->ord.item)==0){
                cost=temp->res.menu[i].price;
                temp->res.menu[i].num_orders++;
            }
        }
        printf("hi5\n");
        o->ord.ord_ag_ptr->agent.curr_acc_comm+=(0.1)*cost;

		printf("order %d elivered by agent %s to %s\n",delivery_no,o->ord.ord_ag_ptr->agent.name,o->ord.cus_name);

		order_tree=o_delete(order_tree,delivery_no);
        r_inorderTraversal(r);
        printf("hi6\n");
		
	}
	
}

//---------------------------------------------------------------------------

poNode *create_p_ord_Node(Prev_order p){
    poNode *n = (poNode*)malloc(sizeof(poNode));

    n->p_order = p;

    n->left = NULL;
    n->right = NULL;

    return n;
}

void p_inorderTraversal(poNode *root){
    if(root){
        p_inorderTraversal(root->left);
        printf("%s from %s \n",root->p_order.item_name,root->p_order.r_name);
        p_inorderTraversal(root->right);
    }
}

int p_height(poNode *root){
    int h;
    if(root == NULL){
        h = 0;
    }
    else{
        int left_height = p_height(root->left);
        int right_height = p_height(root->right);

        if(left_height > right_height){
            h = left_height + 1;
        }
        else{
            h = right_height + 1;
        }
    }
    return h;
}

int p_getBalance(poNode *node){
    int retval;
    if(node == NULL){
        retval = 0;
    }
    else{
        retval = p_height(node->left) - p_height(node->right);
    }
    return retval;
}

poNode *p_rightRotate(poNode *y)
{
    poNode *x = y->left;
    poNode *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    // y->height = max(height(y->left),
    //                 height(y->right)) + 1;
    // x->height = max(height(x->left),
    //                 height(x->right)) + 1;
 
    // Return new root
    return x;
}

poNode *p_leftRotate(poNode *x)
{
    poNode *y = x->right;
    poNode *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    // Update heights
    // x->height = max(height(x->left),   
    //                 height(x->right)) + 1;
    // y->height = max(height(y->left),
    //                 height(y->right)) + 1;
 
    // Return new root
    return y;
}

poNode* p_insert(poNode* node, Prev_order key)
{
    poNode *retval = node;
    /* 1. Perform the normal BST insertion */

    if (node == NULL)
        return (create_p_ord_Node(key));
 
    if (key.p_ord_no < node->p_order.p_ord_no)
        node->left = p_insert(node->left, key);
    else if (key.p_ord_no > node->p_order.p_ord_no)
        node->right = p_insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;
 
    /* 2. Update height of this ancestor node */
    // node->height = 1 + max(height(node->left),
    //                     height(node->right));
 
    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = p_getBalance(node);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key.p_ord_no < node->left->p_order.p_ord_no)
        return p_rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && key.p_ord_no > node->right->p_order.p_ord_no)
        return p_leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && key.p_ord_no > node->left->p_order.p_ord_no)
    {
        node->left = p_leftRotate(node->left);
        return p_rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && key.p_ord_no < node->right->p_order.p_ord_no)
    {
        node->right = p_rightRotate(node->right);
        return p_leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}

// ----------------------------------------------------------------


void newline(){
    printf("\n");
}



int main(){

    FILE *fptr1 = fopen("agent_data.txt","r");
    Agent agents[5];

    if(fptr1){
        fread(&agents,sizeof(Agent),5,fptr1);
    }

    aNode *agent_tree = create_agent_tree(agents);;

    FILE *fptr2 = fopen("res_data.txt","r");
    Restaurant restaurants[5];

    if(fptr2){
        fread(&restaurants,sizeof(Restaurant),5,fptr2);
    }

    rNode *res_tree = create_res_tree(restaurants);


    uNode *user_tree = NULL;

    // a_inorderTraversal(agent_tree);
    // newline();
    // r_inorderTraversal(res_tree);
    // newline();
    // search_by_res_category(res_tree,"Cafe");
    // newline();
    // search_by_food_category(res_tree,"continental");
    // newline();
    // search_by_area(res_tree,"Area1");
    // newline();

    // for(int i=0;i<3;i++){
    //     char cname[SIZE],fname[SIZE],addr[SIZE],rname[SIZE];
    //     int id;
    //     long long pno;

    //     printf("enter your name: ");
    //     scanf("%s",cname);
    //     printf("enter address: ");
    //     scanf("%s",addr);
    //     printf("enter your id: ");
    //     scanf("%d",&id);
    //     printf("enter you phone no: ");
    //     scanf("%lld",&pno);
    //     printf("what you want to order: ");
    //     scanf("%s",fname);
    //     printf("from where: ");
    //     scanf("%s",rname);

    //     User u ;
    //     u.user_id = id;
    //     strcpy(u.name,cname);
    //     strcpy(u.address,addr);
    //     u.u_phone_no = pno;
    //     u.total_p_ord = 0;
    //     u.pn=NULL;

    //     user_tree = u_insert(user_tree,u);

    //     uNode *curr_user = u_search(user_tree,id);

    //     order_placing(cname,pno,rname,fname,agent_tree,curr_user);


    // }

    // // order_placing("Anuj",83472384,"Dominos","PeppyPaneer",agent_tree,NULL);
    // // order_placing("Rajas",3434534,"Panino","NawabKabab",agent_tree,NULL);
    // // order_placing("Anuj",83472384,"Dominos","PeppyPaneer",agent_tree,NULL);
    // // order_placing("Rajas",3434534,"Panino","NawabKabab",agent_tree,NULL);
    // // order_placing("Anuj",83472384,"Dominos","PeppyPaneer",agent_tree,NULL);

    // cancel_order(3);

    // o_inorderTraversal(order_tree);
    // newline();
    // u_inorderTraversal(user_tree);
    // newline();
    // RangeSearch(order_tree,1,2);

    // delivery(res_tree);
    // r_inorderTraversal(res_tree);
    // //delivery(res_tree);

    // o_inorderTraversal(order_tree);

    // RangeSearch(order_tree,1,2);
    
    // FavoriteRestaurants(res_tree);

    // Find_favfood(user_tree,1);

    // FindFavoriteFoodsAcrossRestaurants();

    return 0;
}