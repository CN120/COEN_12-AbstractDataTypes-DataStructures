/*
 
 File: list.c
 
 Dr. Atkinson
 Lab Thurs 9:15
 
 Created by Chris Nelson on 5/11/17
 Description: This file defines functions for creating and destroying a linked list,
 as well as adding and deleting nodes from it. The linked list contains a dummy
 node, is circular, and is doubly linked.
 */

//included libraries and files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"
#include "list.h"


/*
 Description: Defines a node
 Runtime: O(1)
 */
struct node  {
    void *data; //the actual data
    struct node *next;
    struct node *prev;
};

/*
 Description: Defines a list
 Runtime: O(1)
 */
struct list {
    int count;
    struct node *head;
    int (*compare)();
    
};

/*
 Description: allocates memory for, creates, and returns a pointer to a new circular, doubly-linked list with a dummy node
 Runtime: O(1)
 */
LIST *createList(int (*compare)())  {
    LIST *lp;
    struct node *dum;
    lp=malloc(sizeof(LIST));
    dum=malloc(sizeof(struct node));
    dum->data=NULL;
    /* initially, the list will just contain the dummy node, so its next and previous pointer will point to itself */
    dum->next=dum;
    dum->prev=dum;
    lp->count=0;
    lp->compare=compare;
    lp->head= dum;
    return lp;
}




/*
 Description: Frees all node pointers in the linked list
 Runtime: O(n)
 */
void destroyList(LIST *lp)  {
    struct node *np;
    //will delete last node each time through
    for (int i=lp->count;i>0; i--)  {
        np =lp->head->prev->prev;
        free(lp->head->prev);
        lp->head->prev=np;
        lp->count--;
    }
    free(lp->head);
    free(lp);
    
}

/*
 Description: returns the number of items in the list
 Runtime: O(1)
 */
int numItems(LIST *lp){
    return lp->count;
}

/*
 Description: Adds the passed item into the first slot in the linked list. --The new node’s prev pointer is pointed at the dummy node, and its next pointer points to the previous first node. The dummy’s next is then pointed at the new node, and old first node’s prev pointed at the new node.--
 Runtime: O(1)
 
 */
void addFirst(LIST *lp, void *item)  {
    assert(item!=NULL);
    struct node *pNew;
    pNew=malloc(sizeof(struct node));
    pNew->data=item;
    pNew->prev=lp->head;
    pNew->next=lp->head->next;
    lp->head->next=pNew;
    pNew->next->prev=pNew;
    lp->count++;
}


/*
 Description: Adds the passed item into the last slot in the linked list. --The new node’s next pointer is pointed at the dummy node, and its prev pointer points to the old last node. The dummy’s prev is then pointed at the new node, and the old last node’s next pointer is set to the new node.--
 Runtime: O(1)
 
 */
void addLast(LIST *lp, void *item)  {
    struct node *pNew;
    pNew=malloc(sizeof(struct node));
    pNew->data=item;
    pNew->prev=lp->head->prev;
    pNew->next=lp->head;
    pNew->prev->next=pNew;
    lp->head->prev=pNew;
    lp->count++;
}

/*
 Description: The first node is removed and returned. --A temporary pointer is pointed at the first node. The dummy node is pointed to the second node, and the second node is pointed to the dummy node. The first node is then freed.--
 Runtime: O(1)
 */
void *removeFirst(LIST *lp)  {
    assert(lp->count>0);
    void *val=lp->head->next->data;
    struct node *Del;
    Del=lp->head->next;
    lp->head->next=lp->head->next->next;
    lp->head->next->prev=lp->head;
    free(Del);
    lp->count--;
    return val;
}

/*
 Description: The last node is removed and returned. --A temporary pointer is pointed at the last node. The 2nd to last node is pointed to the dummy, the dummy is pointed to the 2nd to last node. The pointer to the last node is then freed.--
 Runtime: O(1)
 */
void *removeLast(LIST *lp)  {
    assert(lp->count>0);
    void *val = lp->head->prev->data;
    struct node *Del;
    Del =lp->head->prev;
    lp->head->prev=lp->head->prev->prev;
    lp->head->prev->next=lp->head;
    free(Del);
    lp->count--;
    return val;
    
}

/*
 Description: Returns the data stored in the first node of the list
 Runtime: O(1)
 */
void *getFirst(LIST *lp)  {
    assert(lp->count>0);
    void *val = lp->head->next->data;
    return val;
}

/*
 Description: Returns the data stored in the last node of the list
 Runtime: O(1)
 */
void *getLast(LIST *lp)  {
    assert(lp->count!=0);
    void *val = lp->head->prev->data;
    return val;
}

/*
 Description: Given an item, the function the searches to see if the item is present, and if so, deletes it. When the the node containing the wanted data is found, the  node is freed.
 Runtime: O(n)
 */
void removeItem(LIST *lp, void *item)  {
    assert((*lp->compare)!=NULL && item!=NULL && lp->count>0);
    struct node *elt=lp->head;
    //compares data in each node to given item
    for(int i=lp->count;i>0;i--)  {
        elt=elt->next;
        if( (*lp->compare)(elt->data, item)==0 )  {
            elt->prev->next=elt->next;
            elt->next->prev=elt->prev;
            free(elt);
            lp->count--;
        }
    }
    
}

/*
 Description: Iterates through the linked list looking for a given item. If the item is found, it is returned.
 Runtime: O(n)
 */
void *findItem(LIST *lp, void *item)  {
    assert((*lp->compare)!=NULL && item!=NULL);
    struct node *elt=lp->head;
    //compares data in each node to given item
    for(int i=lp->count;i>0;i--)  {
        elt=elt->next;
        if( (*lp->compare)(elt->data, item)==0 )  {
            return elt->data;
        }
    }
    return NULL;
}

/*
 Description: Creates and allocates memory for a new array. The linked list is iterated through and the data in each node is put into a new array. The pointer to the array is then returned.
 Runtime: O(n)
 */
void *getItems(LIST *lp)  {
    assert(lp->count!=0);
    void **items;
    items=malloc(sizeof(void*) *lp->count);
    struct node *elt=lp->head;
    //assigns data in each node to array location
    for(int i=0;i<lp->count;i++)  {
        elt=elt->next;
        items[i]=elt->data;
    }
    return items;
}

