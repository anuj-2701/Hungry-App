#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "menu.h"

#define NUM_MENU 10 // max number of items in menu
#define SIZE 100

typedef struct restaurant_tag
{
    char res_name[SIZE];
    char address[SIZE];
    int no_of_seats;
    Food menu[NUM_MENU];
    char res_category[SIZE];
    char food_category[SIZE];
    int no_of_orders;

} Restaurant;

typedef struct restaurant_node_tag
{
    Restaurant res;
    struct restaurant_node_tag * next;
} rNode;

#endif