/*
 
 File: pqueue.c
 
 Dr. Atkinson
 Lab: Thurs 9:15
 
 Created by Chris Nelson on 5/25/17
 Description: pqueue.c is able to create and build a min priority queue
    using a binary heap ADT implemented with an array. It is able to deal 
    with any data type, and so requires that a compare function is given 
    to it before the priority queue can be created. Once built, items 
    from the priority queue can be removed and the entire heap can be 
    destroyed.
 */

//included libraries and files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "pqueue.h"

//global definitions
#define START_LENGTH 10  /* array start length */
#define p(x) (((x)-1)/2) /* parent index function */
#define l(x) (((x)*2)+1)  /* left child index function */
#define r(x) (((x)*2)+2)  /* right child index function */


/*
 Description: defines a priortity queue
 Runtime: O(1)
 */
struct pqueue {
    int count;
    int length;
    void **data;
    int (*compare)();
    
};

/*
 Description: returns a pointer to a new priority queue
 Runtime: O(1)
 */
PQ *createQueue(int (*compare)()) {
    assert (compare!=NULL);
    PQ *pq;
    pq = malloc(sizeof(PQ));
    pq->count=0;
    pq->length = START_LENGTH;
    pq->compare=compare;
    pq->data = malloc(sizeof(void*)*(pq->length));
    return pq;
}

/*
 Description: frees pointers associated with pq
 Runtime: O(1)
 */
void destroyQueue(PQ *pq)  {
    assert(pq!=NULL);
    free(pq->data);
    free (pq);
    
}

/*
 Description: returns the count or the number of items in the heap
 Runtime: O(1)
 */
int numEntries(PQ *pq)  {
    assert(pq!=NULL);
    return pq->count;
}



/*
 Description: Adds entry to next open value in the heap (array) and swaps it with its parent until it is in the correct min heap sort location
 Runtime: O(logn)
 */
void addEntry(PQ *pq, void *entry)  {
    assert(pq!=NULL && entry!=NULL);
    if (pq->count==pq->length)  {
        //array is full so size is doubled
        pq->data= realloc(pq->data, sizeof(void*)*(pq->length)*2);
        pq->length=(pq->length)*2;
    }
    pq->data[pq->count]=entry; //new elt added to end of array
    int idx = pq->count; //holds index of new elt in 'idx'
    pq->count++;
    void *temp;
    /* while new entry is less than its parent, they are swapped */
    while (pq->compare(pq->data[idx], pq->data[p(idx)])<0)  {
        temp = pq->data[idx]; //temp set to added elt
        pq->data[idx] = pq->data[p(idx)];  //last index set to parent of new elt
        pq->data[p(idx)]=temp; //new elt placed in parents old index
        idx=p(idx); //index of new elt set to its new location
    }
}

/*
 Description: Removes first/least item from the heap (array). The item at the bottom of the heap is put into the removed position and swapped with its children until it is in the correct min heap sort location
 Runtime: O(logn)
 */
void *removeEntry(PQ *pq)  {
    assert(pq!=NULL);
    void *least = pq->data[0];  //holds smallest entry in a varible to be returned later
    pq->data[0]=pq->data[pq->count-1]; //replaces first spot will item at the end
    pq->count--;
    int idx = 0;
    int smallIdx =0;
    //while's purpose is to reach bottom of the heap if neccesary
    while(l(idx)< pq->count)  {
        smallIdx = l(idx);
        if(r(idx)<= pq->count)  {
            //checks if right or left child is smalelr
            if(pq->compare(pq->data[r(idx)],pq->data[l(idx)])<0) {
                smallIdx = r(idx);
            }
        }
        //if data in pos idx is smaller than data in small index, swap them
        if(pq->compare(pq->data[idx], pq->data[smallIdx])>0)  {
            void *temp = pq->data[smallIdx];
            pq->data[smallIdx] = pq->data[idx];
            pq->data[idx]=temp;
            idx = smallIdx;
        }
        else {
            break;
        }
        
        
    }
    //return data on the top of the heap aka the smallest value
    return least;
    
}




