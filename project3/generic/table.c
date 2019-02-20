/*
 
 table.c - generic
 This program will create a set and add and remove elements as well as return an array of data stored in the set
 It is also able to destroy the created set when finished
 This program can run using an array of any varible type
 Dr. Atkinson
 Lab Thurs 9:15
 
 Created by Chris Nelson on 5/4/17. "May the 4th be with you"
 */
//included libraries and files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"

//defines values of EMPTY, FILLED, and DELETED
#define EMPTY 0
#define FILLED 1
#define DELETED 2

//defines a struct set
struct set  {
    int count; //number of elements
    int length;  //length of the array
    void **data; //the actual data
    char *flags;  //holds info about the state of each slot in the hash table
    int (*compare)();  //user defined compare function for comparing given data types
    unsigned (*hash)();  //user defined hash function for hashing given data types
};


/*
 given a set, search will look for a given element in set  data[] by checking each element and return the location if found
 Runtime: O(1) or O(n) at worst
 */
static int search(SET *sp, void *elt, bool *found)  {
    assert(sp != NULL && elt!=NULL);
    int h = ((*sp->hash)(elt))%sp->length;  //hash varible
    int firstDel =-1; /* if first delete remains -1, it means no deleted spots were found while probing*/
    //will run through the length of data[] unless the item is found
    for (int i=0; i<(sp->length);i++)  {
        int locn= (h+i)%sp->length; //linear probng sequence
        if (sp->flags[locn]==EMPTY)  {
            //if flag location is empty then probing can stop as the given value is not there
            *found = false;
            /*if the item used to be there but was deleted, firstDel would have been changed
             so if no deleted spots were found, the first empty location can be returned
             */
            if (firstDel==-1)  {
                return locn;
            }
            return firstDel;
        }
        /*if a flag location is deleted, the location will be saved into firdtDel if its the first deleted spot found
         this way the probe sequence can continue searching until it finds an empty slot*/
        else if (sp->flags[locn]==DELETED)  {
            if (firstDel==-1) {
                firstDel=locn;
            }
        }
        /*if a spot is filled then it's value is checked against the element being searched for
         if it is the value, the location is returned and found is set to true, otherwise nothing occurs and the loop keeps running
         */
        else if (sp->flags[locn]==FILLED)  {
            if ((*sp->compare)(sp->data[locn], elt)==0)  {
                *found = true;
                return locn;
            }
        }
        
    }
    *found=false;
    return -1;  //will return 1 only if hash table is full
}


/*
 allocates memory for and creates a set
 Runtime: O(1) /* should be O(n) */
 */
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) {
    SET *sp;
    
    sp = malloc(sizeof(SET));  //allocates memory for the set
    assert(sp!=NULL);
    
    //assigns values to varibles
    sp->count=0;
    sp->length=maxElts;
    sp->data=malloc(sizeof(void*)*maxElts);
    sp->flags=malloc(sizeof(char)*maxElts);
    sp->hash=hash;
    sp->compare=compare;
    assert (sp->data!=NULL);
    assert (sp->flags!=NULL);
    
    for (int i=0; i<maxElts; i++)  {
        sp->flags[i] = EMPTY;
    }
    return sp;  // returns pointer to created set
}

/*
 destroySet will destroy the passed set by freeing all pointers within data and then free the pointer to data itself and sp
 Runtime: O(n) /* should be O(1) */
 */
void destroySet(SET *sp) {
    assert(sp!=NULL);
    free (sp->data);
    free (sp->flags);
    free (sp);
}

/*
 numElements simply returns the number of elements in data[] stored in count
 Runtime: O(1)
 */
int numElements(SET *sp)  {
    /* missing assert */
    return sp->count;
}

/*
 addElement will add an element to the end of the data[] array as long as the element is not found in the array already
 Runtime: O(1) or O(n) at worst due to using search
 */
void addElement(SET *sp, void *elt)  {
    bool found;  //set to true of false based on whether or not elt is found
    assert(sp->count < sp->length);
    int locn = search(sp, elt, &found);
    if(found==false){
        //if elt is not already in the array, it will be added
        sp->data[locn]=elt; // index set to point to elt
        sp->flags[locn]=FILLED;
        sp->count++;
    }
}

/*
 removeElement will remove the passed element from the end of the data[] array as long as the element is found in the array
 Runtime: O(1) or O(n) at worst due to using search
 */

void removeElement(SET *sp, void *elt) {
    bool found;  //set to true of false based on whether or not elt is found
    int locn = search(sp, elt, &found);
    if (found) {
        assert(sp!=NULL && elt!=NULL);
        // if elt is in the array, its pointer will be freed and sets the locations flag to EMPTY
        sp->flags[locn]=DELETED;
        sp->count--;  //decrements count
        
    }
    
}

/*
 findElement will search for a given elemnet and return it
 Runtime: O(1) or O(n) at worst
 */
void *findElement(SET *sp, void *elt)  {
    assert(sp!=NULL);
    assert(elt!=NULL);
    bool found;
    int locn = search(sp, elt, &found);
    // if elt is in the array, it's pointer is returned, else NULL is returned
    if (found)
        return sp->data[locn];
    return NULL;
}

/*
 getElements duplicates data[] into a new array and returns a pointer to that array
 Runtime: O(n)
 */
void *getElements(SET *sp)  {
    void **objects;
    assert(sp!=NULL);
    objects= malloc(sizeof(void*)*sp->count); //allocates enough memory for x number of character pointers
    assert(objects!=NULL);
    int n =0;
    for (int i=0; i<sp->length;i++) //for all elements in data[], copies all elements into new array that is then reutned
        if(sp->flags[i]==FILLED)  {
            objects[n]=sp->data[i];
            n++;
        }
    return objects;
    
}






