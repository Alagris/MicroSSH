//
//  shared_resources.c
//  MicroSSH
//
//  Created by Alagris on 09/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#include "shared_resources.h"
#include <stdlib.h>
#include <string.h>
typedef unsigned char mshArrayElem;
#define MSH_ARRAY_SIZE 32
struct __mshLinkedArrays{
    struct __mshLinkedArrays * next;
    struct __mshLinkedArrays * prev;
    mshArrayElem arr[MSH_ARRAY_SIZE];
};

struct __mshState{
    struct __mshLinkedArrays root;
    struct __mshLinkedArrays * current;
    size_t index;
    
}__state={.root={.next=NULL,.prev=NULL},.current=&__state.root,.index=0};

struct __mshLinkedArrays * const __mshCreateLinkedArray(){
    struct __mshLinkedArrays * const la=malloc(sizeof(struct __mshLinkedArrays));
    memset(la->arr,0,MSH_ARRAY_SIZE);
    la->next=NULL;
    la->prev=NULL;
    return la;
}

void __mshLinkArrays(struct __mshLinkedArrays * const prev,
                     struct __mshLinkedArrays * const next)
{
    prev->next=next;
    next->prev=prev;
}

void __mshAppendLinkedArray(struct __mshLinkedArrays * const last)
{
    __mshLinkArrays(last, __mshCreateLinkedArray());
}

void __mshPrependLinkedArray(struct __mshLinkedArrays * const first)
{
    __mshLinkArrays(__mshCreateLinkedArray(),first);
}


void mshMoveRightInArray(void){
    if(__state.index==MSH_ARRAY_SIZE-1){
        __state.index=0;
        if(__state.current->next==0)
            __mshAppendLinkedArray(__state.current);
        __state.current=__state.current->next;
    }else{
        __state.index++;
    }
}

void mshMoveLeftInArray(void){
    if(__state.index==0){
        __state.index=MSH_ARRAY_SIZE-1;
        if(__state.current->prev==0)
            __mshPrependLinkedArray(__state.current);
        __state.current=__state.current->prev;
    }else{
        __state.index--;
    }
}

void mshIncrementInArray(void){
    __state.current->arr[__state.index]++;
}

void mshDecrementInArray(void){
    __state.current->arr[__state.index]--;
}

const mshArrayElem mshGetInArray(void){
    return __state.current->arr[__state.index];
}

#undef MSH_ARRAY_SIZE
