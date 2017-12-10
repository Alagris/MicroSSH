//
//  semipipe.c
//  MicroSSH
//
//  Created by Alagris on 05/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#include "semipipe.h"
#include <stdlib.h>
#include <string.h>
void mshOpenSemiPipe(struct mshSemiPipe * const p,const size_t size){
    p->size=size;
    p->available=0;
    p->buffer=malloc(size*sizeof(mshSemiPipeElem));
    memset(p->buffer,0,p->size);
}

void mshCloseSemiPipe(struct mshSemiPipe * const p){
    free(p->buffer);
    p->buffer=0;
    p->size=0;
    p->available=0;
}

void mshResetSemiPipe(struct mshSemiPipe * const p){
    p->available=0;
}

void mshClearSemiPipe(struct mshSemiPipe * const p){
    memset(p->buffer,0,p->size);
    mshResetSemiPipe(p);
}


const size_t min(const size_t a,const size_t b){
    return b<a?b:a;
}

const size_t mshPushSemiPipe(struct mshSemiPipe * const p,
                             const void *const src,
                             const size_t bytesNum)
{
    const size_t bytesToCopy=min(bytesNum,mshFreeSpaceInSemiPipe(p));
    memcpy(mshPtrToEndInSemiPipe(p), src, bytesToCopy);
    p->available+=bytesToCopy;
    return bytesToCopy;
}
