//
//  unsorted.c
//  
//
//  Created by Chris Nelson on 4/11/17.
//
//

#include <stdio.h>
#inclide <stdlib.h>
#include <assert.h>
#include set.h

struct set  {
    int count; //number of elements
    int length;  //length of the array
    char **data; //the actual data
};
typeof struct set SET;



SET *createSet(int maxElts) {
    SET *sp;
    
    sp = malloc(sizeof(SET));
    assert(sp!=NULL);
    
    sp->count=0;
    sp->length=maxElts;
    sp->data=malloc(sizeof(char*)*maxElts);
    assert (sp->data!=NULL);
    return sp;
}

SET destroySet(SET *sp) {
    int i;
    
    for(i=0;i<sp->count; i++)
        free(sp->data[i]);
    free (sp->data);
    free (sp);
}

int numElements(SET *sp)  {
    int i=0;
    while(sp->data[i]!=NULL)  {
        i++; //increments i as long as data is being read at each next index
    }
    return i;
}

int static search(SET *sp, char *elt, bool *found)  {
    
}

void removeElement(SET *sp, char *elt) {
    assert(sp!=NULL && lets!=NULL);
    locn = search(sp, elt);
    if (locn!=-1) {
        free(sp->data[locn]);
        sp->data[locn]=sp->data[--sp->count];















