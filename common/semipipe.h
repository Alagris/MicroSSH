//
//  semipipe.h
//  MicroSSH
//
//  Created by Alagris on 05/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#ifndef semipipe_h
#define semipipe_h
#include <stddef.h>
#include <sys/types.h>
typedef unsigned char mshSemiPipeElem;

struct mshSemiPipe{
    size_t size;
    mshSemiPipeElem * buffer;
    ssize_t available;
};
#define mshDefaultSemiPipe {.size=0,.buffer=0,.available=0}


void mshOpenSemiPipe(struct mshSemiPipe * const p,const size_t size);

void mshCloseSemiPipe(struct mshSemiPipe * const p);

void mshClearSemiPipe(struct mshSemiPipe * const p);

void mshResetSemiPipe(struct mshSemiPipe * const p);


static inline const size_t mshFreeSpaceInSemiPipe(const struct mshSemiPipe * const p){
    return p->size - p->available;
}
static inline mshSemiPipeElem *const mshPtrToEndInSemiPipe(const struct mshSemiPipe * const p){
    return p->buffer + p->available;
}


/**returns number of pushed bytes*/
const size_t mshPushSemiPipe(struct mshSemiPipe * const p,
                             const void *const src,
                             const size_t bytesNum);

#define mshPrimitivePushSemiPipe(p,m) mshPushSemiPipe( p , & m , sizeof( m ) )

#define mshPrimitiveGetSemiPipe(pipe,offset,type) *((type *)((pipe).buffer+offset))

static inline void mshPopSemiPipe(struct mshSemiPipe * const p,const size_t bytesToPop){
    if(p->available<=bytesToPop)
        p->available=0;
    else
        p->available-=bytesToPop;
}

static inline const size_t mshSearchSemiPipe(struct mshSemiPipe * const p,const mshSemiPipeElem e,size_t offset){
    while(offset<p->size && p->buffer[offset]!=e)offset++;
    return offset;
}
static inline const size_t mshSearchAvailableSemiPipe(struct mshSemiPipe * const p,const mshSemiPipeElem e,size_t offset){
    while(offset<p->available && p->buffer[offset]!=e)offset++;
    return offset;
}
static inline const size_t mshUpdateAvailableSemiPipe(struct mshSemiPipe * const p){
    return p->available = mshSearchSemiPipe(p, '\0', 0);
}
#endif /* semipipe_h */
