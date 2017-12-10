//
//  bitset.h
//  MicroSSH
//
//  Created by Alagris on 05/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#ifndef bitset_h
#define bitset_h
#include <stddef.h>
typedef unsigned long long mshBitsetElem;
struct mshBitset{
    mshBitsetElem * data;
    size_t len;
};
#define mshDefaultBitset {.data=0,.len=0}

const _Bool mshTestBitset(const struct mshBitset * const set,const size_t index);
void mshSetBitset(const struct mshBitset * const set,const size_t index,const _Bool value);
void mshFlipBitset(const struct mshBitset * const set,const size_t index);
void mshClearBitset(const struct mshBitset * const set);
const size_t mshCountBitsInBitset(const struct mshBitset * const set);
const _Bool mshValidateIndexBitset(const struct mshBitset * const set,const size_t index);
void mshEnsureCapacityBitset(struct mshBitset * const set,const size_t index);
void mshDestroyBitset(struct mshBitset * const set);
static inline const size_t mshNextSetBitInBitset(const struct mshBitset * const set,
                                                size_t offsetExclusive)
{
    while(++offsetExclusive<mshCountBitsInBitset(set))
        if(mshTestBitset(set, offsetExclusive))break;
    return offsetExclusive;
}
static inline const size_t mshNextUnsetBitInBitset(const struct mshBitset * const set,
                                                   size_t offsetExclusive)
{
    while(++offsetExclusive<mshCountBitsInBitset(set))
        if(!mshTestBitset(set, offsetExclusive))break;
    return offsetExclusive;
}
static inline const size_t mshPrevSetBitInBitset(const struct mshBitset * const set,
                                                 size_t offsetExclusive)
{
    while(1)
        if(mshTestBitset(set, offsetExclusive))
            break;
        else if(offsetExclusive==0)
                return mshCountBitsInBitset(set);
            else
                offsetExclusive--;
    return offsetExclusive;
}
static inline const size_t mshPrevUnsetBitInBitset(const struct mshBitset * const set,
                                                   size_t offsetExclusive)
{
    while(1)
        if(!mshTestBitset(set, offsetExclusive))
            break;
        else if(offsetExclusive==0)
            return mshCountBitsInBitset(set);
        else
            offsetExclusive--;
    return offsetExclusive;
}
#endif /* bitset_h */
