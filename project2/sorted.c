//
//  sorted.c
//
//
//  Created by Chris Nelson on 4/16/17.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "set.h"

struct set  {
    int count; //number of elements
    int length;  //length of the array
    char **data; //the actual data
};


static void sort(SET *sp)  {
    assert(sp!=NULL);
    int n = numElements(sp);
    assert(n>1);
    char *temp
    for(int i=0; i < n-2 ; i++){
        for(j=i+1; j< n-1; j++)
        {
            if(strcmp(sp->data[i],sp->data[j]) > 0)
            {
                strcpy(temp,sp->data[i]);
                strcpy(sp->data[i],sp->data[j]);
                strcpy(sp->data[j],temp);
            }
        }
    }
}

static int search(SET *sp, char *elt, bool *found)  {
    assert(sp!=NULL);
   	int lo,hi,mid;
    lo=0;
    hi=sp->count-1;
    while (lo<=hi) {
        mid =(lo+hi)/2; //will truncate to an int
        diff=strcmp(elt, sp->data[mid])
        if (diff<0)
            hi =mid-1;
        else if (diff>0)
            lo=mid+1;
        else{
            *found =true;
            return mid;
        }						    }
    *found=false;
    return lo;
                    
}
                    
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

void destroySet(SET *sp) {
    int i;
    
    for(int i=0;i<sp->count; i++)
        free(sp->data[i]);
        free (sp->data);
        free (sp);
    }
                    
int numElements(SET *sp)  {
    return sp->count;
}
                    
void addElement(SET *sp, char *elt)  {
    if(search(sp, elt)==-1&&(sp->count<sp->length)){
        sp->data[sp->count]=strdup(elt);
        assert(sp->data[sp->count]!=NULL);
        sp->count++;
    }
}
                    
void removeElement(SET *sp, char *elt) {
    assert(sp!=NULL && elt!=NULL);
    int locn = search(sp, elt); //****do I need to give this three arguments?***
    if (locn!=-1) {
        free(sp->data[locn]);
        sp->data[locn]=sp->data[--sp->count];
        
    }
}
                    
char *findElement(SET *sp, char *elt)  {
    int i = search(sp, elt);
    assert (i!=-1);
    return sp->data[i];
}
                    
                    
                    
char **getElements(SET *sp)  {
    char **strings;
    assert(sp!=NULL);
    strings= malloc(sizeof(char*)*sp->count); //allocates enough memory for x number of character pointers
    assert(strings!=NULL);
    for (int i=0; i<sp->count;i++)
        strings[i]=sp->data[i];
    return strings;
}
