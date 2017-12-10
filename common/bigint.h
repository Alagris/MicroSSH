//
//  bigint.h
//  MicroSSH
//
//  Created by Alagris on 06/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#ifndef bigint_h
#define bigint_h
#include <stddef.h>
typedef unsigned int mshBigUIntElem;
typedef unsigned long long mshBigUIntDoubleElem;

struct mshBigUInt{
    mshBigUIntElem * data;
    size_t len;
};
#define mshDefaultBigUInt {.len=0,.data=0}
void mshCreateBigUInt(struct mshBigUInt *const dest,
                      const void *const num,
                      const size_t bytes);
void mshDestroyBigUInt(struct mshBigUInt *const num);
void mshMulBigUInt(const struct mshBigUInt *const a,
                   const struct mshBigUInt *const b,
                   struct mshBigUInt *const ab);
void mshDivBigUInt(const struct mshBigUInt *const a,
                   const struct mshBigUInt *const b,
                   struct mshBigUInt *const ab);
void mshAddBigUInt(const struct mshBigUInt *const a,
                   const struct mshBigUInt *const b,
                   struct mshBigUInt *const ab);
void mshSubBigUInt(const struct mshBigUInt *const a,
                   const struct mshBigUInt *const b,
                   struct mshBigUInt *const ab);
void mshModBigUInt(const struct mshBigUInt *const a,
                   const struct mshBigUInt *const b,
                   struct mshBigUInt *const ab);
const _Bool mshGtBigUInt(const struct mshBigUInt *const a,
                         const struct mshBigUInt *const b);
const _Bool mshLtBigUInt(const struct mshBigUInt *const a,
                         const struct mshBigUInt *const b);
const _Bool mshEqBigUInt(const struct mshBigUInt *const a,
                         const struct mshBigUInt *const b);
/**Index 0 is the least significant digit*/
static inline const mshBigUIntElem mshDigitAtBigUInt(const struct mshBigUInt *const num,
                                                     const size_t index)
{
    return index>=num->len?0:num->data[num->len-1-index];
}
/**Index 0 is the least significant digit*/
static inline void mshSetDigitAtBigUInt(const struct mshBigUInt *const num,
                                        const size_t index,
                                        const mshBigUIntElem digit)
{
    if(index<num->len)num->data[num->len-1-index]=digit;
}
static inline const size_t mshSizeOfBigUInt(const struct mshBigUInt *const num)
{
    size_t i=num->len;
    while(i>0)
        if(num->data[i-1]==0)
            i--;
        else
            break;
    return i;
}
#endif /* bigint_h */
