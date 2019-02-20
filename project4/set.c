/*
 
 File: set.c
 
 Dr. Atkinson
 Lab Thurs 9:15
 
 Created by Chris Nelson on 5/18/17
 
 Desciption: This files contains functions for creating a set(hash table). Unlike a
 traditional hash table, in which collisions would be solved using probing, each
 hash location contains a pointer to a linked list. So a value that hashes to a
 location already containg data is simply added to the end of the linked list at
 that location.
 */

//included libraries and files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"
#include "list.h"

#define Avg_LENGTH 20

/*
 Description: defines a set
 Runtime: O(1)
 */
struct set  {
    int count; //number of elements
    int length;  //length of the array
    LIST **list; //the actual data
    int (*compare)();  //user defined compare function for comparing given data types
    unsigned (*hash)();  //user defined hash function for hashing given data types
};



/*
 Description: allocates memory for and creates a set
 Runtime: O(1)
 */
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) {
    SET *sp;
    
    sp = malloc(sizeof(SET));  //allocates memory for the set
    assert(sp!=NULL);
    
    //assigns values to varibles
    sp->count=0;
    sp->length=maxElts/Avg_LENGTH;;
    sp->list=malloc(sizeof(LIST*)*sp->length);
    sp->hash=hash;
    sp->compare=compare;
    assert (sp->list!=NULL);
    for(int i=0; i<sp->length; i++)
        sp->list[i]= createList(compare);
    
    return sp;
}

/*
 Description: frees all memory associated with the set
 Runtime: O(n^2)
 */
void destroySet(SET *sp)  {
    assert(sp!=NULL);
    //destroys the list pointed to by each hash location
    for(int i=0; i<sp->length; i++)
        destroyList(sp->list[i]);   // O(n) function
    free (sp->list);
    free (sp);
    
}

/*
 Description: returns number of elements storred in the set
 Runtime: O(n)
 */
int numElements(SET *sp){
    return sp->count;
}

/*
 Description: Will search list at elts hash location to check to see if it is there. If it is not, then a node is added to the linked list at that hash location
 Runtime: O(n)
 */
void addElement(SET *sp, void *elt){
    assert(sp!=NULL && elt!=NULL);
    int h = ((*sp->hash)(elt))%sp->length;  //hash varible
    // Uses findItem (an O(n) function) to search the list, and the node is added to the end if it is not found
    if (findItem(sp->list[h], elt)==NULL)  {
        addLast(sp->list[h], elt);
        sp->count++;
    }
}

/*
 Description: Will search list at elts hash location to check to see if it is there. If it is, then the node is deleted from the linked list at that hash location
 Runtime: O(n)
 */
void removeElement(SET *sp, void *elt){
    assert(sp!=NULL && elt!=NULL);
    int h = ((*sp->hash)(elt))%sp->length;  //hash varible
    int c = numItems(sp->list[h]);
    removeItem(sp->list[h], elt);
    //if the number of items in the list has changed, then overall count is decremented
    if (c!= numItems(sp->list[h]))
        sp->count--;
}

/*
 Description: Uses find item to search for the given element in the linked list at the element's hash location. If found, the data will be returned, otherwise, NULL will be returned.
 Runtime: O(n)
 */
void *findElement(SET *sp, void *elt){
    int h = ((*sp->hash)(elt))%sp->length;  //hash varible
    return findItem(sp->list[h], elt);  // O(n) function
}

/*
 Description: Returns a pointer to a new array containing all elements stored in the set
 Runtime: O(n^2)
 */
void *getElements(SET *sp){
    void **elts, **temp;
    elts=malloc(sizeof(void*) *sp->count);
    int nDex = 0;
    //for each list, traverse all elements in the list
    for (int i=0; i<sp->length; i++)  {
        temp=getItems(sp->list[i]);  // O(n) function
        //traverses array stored in temp and adds data at each location to a bigger master array
        for (int j=0; j<(numItems(sp->list[i])); j++)  {
            elts[nDex]=temp[j];
            nDex++;
        }
    }
    return elts;
}
