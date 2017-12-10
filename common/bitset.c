//
//  bitset.c
//  MicroSSH
//
//  Created by Alagris on 05/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#include "bitset.h"
#include <string.h>
#include <stdlib.h>
static const size_t MSH_BITSET_ELEM_SIZE=sizeof(mshBitsetElem)*8;

static const size_t __mshFindElemIndexInBitset(const size_t bitIndex){
    return bitIndex/MSH_BITSET_ELEM_SIZE;
}
static const size_t __mshFindBitIndexInElem(const size_t bitIndex){
    return bitIndex%MSH_BITSET_ELEM_SIZE;
}
static const mshBitsetElem __mshGetBitMaskForIndex(const size_t bitIndex){
    const mshBitsetElem one=1;
    const size_t index=__mshFindBitIndexInElem(bitIndex);
    return one<<(MSH_BITSET_ELEM_SIZE-1-index);
}
static const _Bool __mshTestBitInElem(const mshBitsetElem elem,const size_t bitIndex){
    return (__mshGetBitMaskForIndex(bitIndex)&elem)>0;
}
static const mshBitsetElem __mshFlipBitInElem(const mshBitsetElem elem,const size_t bitIndex){
    return __mshGetBitMaskForIndex(bitIndex)^elem;
}
static const mshBitsetElem __mshSetBitInElem(const mshBitsetElem elem,const size_t bitIndex){
    return __mshGetBitMaskForIndex(bitIndex)|elem;
}
static const mshBitsetElem __mshUnsetBitInElem(const mshBitsetElem elem,const size_t bitIndex){
    return (~__mshGetBitMaskForIndex(bitIndex))&elem;
}
//static const _Bool __mshValidateElemIndex(const struct mshBitset * const set,
//                                          const size_t elemIndex)
//{
//    return elemIndex<set->len;
//}
const _Bool mshTestBitset(const struct mshBitset * const set,const size_t index){
    const size_t elemIndex=__mshFindElemIndexInBitset(index);
    return __mshTestBitInElem(set->data[elemIndex],index);
}
void mshSetBitset(const struct mshBitset * const set,const size_t index,const _Bool value){
    const size_t elemIndex=__mshFindElemIndexInBitset(index);
    const mshBitsetElem elem = set->data[elemIndex];
    set->data[elemIndex]=value?
        __mshSetBitInElem(elem,index):
        __mshUnsetBitInElem(elem,index);
}
void mshFlipBitset(const struct mshBitset * const set,const size_t index){
    const size_t elemIndex=__mshFindElemIndexInBitset(index);
    set->data[elemIndex]=__mshFlipBitInElem(set->data[elemIndex],index);
}
void mshClearBitset(const struct mshBitset * const set){
    memset(set->data, 0, sizeof(mshBitsetElem)*set->len);
}
const _Bool mshValidateIndexBitset(const struct mshBitset * const set,const size_t index){
    return __mshFindElemIndexInBitset(index)<set->len;
}
const size_t mshCountBitsInBitset(const struct mshBitset * const set){
    return set->len*MSH_BITSET_ELEM_SIZE;
}
void mshEnsureCapacityBitset(struct mshBitset * const set,const size_t index){
    const size_t capacity=__mshFindElemIndexInBitset(index)+1;
    if(set->len<capacity){
        mshBitsetElem * newData=malloc(capacity*sizeof(mshBitsetElem));
        memcpy(newData, set->data, set->len*sizeof(mshBitsetElem));
        free(set->data);
        set->data=newData;
        set->len=capacity;
    }
}
void mshDestroyBitset(struct mshBitset * const set){
    free(set->data);
    set->data=0;
    set->len=0;
}

