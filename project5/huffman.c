//
//  huffman.c
//
//
//  Created by christopher j nelson on 6/1/17.
//
//Creates a huffman tree to compreess a text file using lossless compression

#include <stdio.h>
#include <stdlib.h>
#include "pack.h"
#include "pqueue.h"
#include <ctype.h>
#include <assert.h>



static int intcmp(struct node *i1, struct node *i2)
{
    return (i1->count < i2->count) ? -1 : (i1->count > i2->count);
}

int main(int argc, char *argv[])  {
    FILE *fp=fopen(argv[1],"r");  //declares a file pointer and sets it to the location entered on the command line
    assert(fp!=NULL);
    struct node *leaves[257] = {NULL};
    int occurs[257]={0};
    
    
    while(fgetc(fp)!=EOF) {
        occurs[fgetc(fp)]++;
        
    }
    occurs[256]=0;
    //creates queue
    PQ *pq = createQueue(intcmp);
    for (int i=0; i<257;i++) {
        if(occurs[i]!=0)  {
            leaves[i]=malloc(sizeof(struct node));
            leaves[i]->count=occurs[i];
            leaves[i]->parent=NULL;
            addEntry(pq, leaves[i]);
        }
    }
    //special case for EOF
    leaves[256]=malloc(sizeof(struct node));
    //creates huffman tree
    while(numEntries(pq)>1)  {
        struct node *sum = malloc(sizeof(struct node));
        struct node *ch1;
        struct node *ch2;
        sum->parent=NULL;
        
        ch1= removeEntry(pq);
        ch2=removeEntry(pq);
        ch1->parent = sum;
        ch2->parent = sum;
        sum->count= ch1->count + ch2->count;
        addEntry(pq, sum);
        
    }
    //node to be used to find space required for each letter in the text file
    struct node *target;
    target=NULL;
    for(int i=0; i<257; i++){
        int height = 0;
        if(leaves[i]!=NULL)  {
            //fprintf(stderr,"2\n");
            target = leaves[i];
            
            while(target->parent!=NULL) {
                height++;
                target = target->parent;
            }
           
            //printable vs unprintable
            if(isprint(i)!=0)  {
                printf("%c : %d x %d bits = %d bits\n", i, occurs[i], height, (occurs[i]*height));
            }
            else {
                printf("%03o : %d x %d bits = %d bits\n", i, occurs[i], height, (occurs[i]*height));
            }
           
        }
    }
    pack(argv[1], argv[2], leaves);
    fclose(fp);
}
