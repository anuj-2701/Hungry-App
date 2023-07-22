#ifndef MENU_H
#define MENU_H

#define SIZE 100

typedef struct food_tag{
    char fname[SIZE];
    int price;
    int num_orders;

} Food;

typedef struct item_tag{
	char fname[SIZE];
	int count;
	struct item_tag *next;
	
} item;

// typedef struct menu_tag{
//     Food f[SIZE];
// } Menu;


#endif