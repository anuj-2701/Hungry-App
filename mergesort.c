#include <stdio.h>
#include "menu.h"

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