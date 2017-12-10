//
//  bigint.c
//  MicroSSH
//
//  Created by Alagris on 06/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//


#include "bigint.h"
#include "math.h"
#include <stdlib.h>
#include <string.h>
void __mshRelocateBigUInt(struct mshBigUInt *const num,const size_t newLen)
{
    if(newLen<=num->len)return;
    mshBigUIntElem*const newData=malloc(newLen*sizeof(mshBigUIntElem));
    memcpy(newData, num->data, num->len*sizeof(mshBigUIntElem));
    mshBigUIntElem*const oldData=num->data;
    num->data=newData;
    num->len=newLen;
    free(oldData);
}
void __mshAllocateBigUInt(struct mshBigUInt *const num,const size_t newLen)
{
    if(newLen<=num->len)return;
    free(num->data);
    num->data=malloc(newLen*sizeof(mshBigUIntElem));
    num->len=newLen;
    memset(num->data, 0, num->len*sizeof(mshBigUIntElem));
    
}

const _Bool __mshEndsWithZeroBigUInt(const struct mshBigUInt *const num)
{
    return num->data[0]==0;
}
const _Bool __mshValidateElemIndex(const struct mshBigUInt *const num,const size_t index){
    return index<num->len;
}
const mshBigUIntElem __mshSafeElemAtBigUInt(const struct mshBigUInt *const num,const size_t index)
{
    return __mshValidateElemIndex(num,index)?num->data[index]:0;
}
const mshBigUIntElem  __mshRightHalfOfDoubleElem(const mshBigUIntDoubleElem e){
    return (mshBigUIntElem) e;
}
const mshBigUIntElem  __mshLeftHalfOfDoubleElem(const mshBigUIntDoubleElem e){
    return (mshBigUIntElem) (e>>(sizeof(mshBigUIntElem)*8));
}
void __mshAddElem(struct mshBigUInt *const num,const mshBigUIntElem elem,size_t index){
    num->data[index]=num->data[index]+elem;
    int carry=mshIsCarryFlagSet();
    while(carry==1){
        index--;
        num->data[index]=num->data[index]+1;
        carry=mshIsCarryFlagSet();
    }
}
void mshCreateBigUInt(struct mshBigUInt *const dest,
                      const void *const num,
                      const size_t bytes)
{
    dest->len=mshCeil(bytes,sizeof(mshBigUIntElem));
    free(dest->data);
    dest->data=malloc(dest->len);
    memcpy(dest->data, num, bytes);
}
void mshDestroyBigUInt(struct mshBigUInt *const num){
    free(num->data);
    num->data=0;
    num->len=0;
}
/*This function is designed in a way that will work even if ab is a pointer to a or b*/
void mshAddBigUInt(const struct mshBigUInt *const a,
                   const struct mshBigUInt *const b,
                   struct mshBigUInt *const ab)
{
    size_t abNewLen;
    if(a->len>b->len){
        abNewLen=a->len+!__mshEndsWithZeroBigUInt(a);
    }else{
        abNewLen=b->len+!__mshEndsWithZeroBigUInt(b);
    }
    __mshRelocateBigUInt(ab, abNewLen);
    for(size_t ia=a->len-1,ib=b->len-1,iab=ab->len-1;
        __mshValidateElemIndex(a,ia)||__mshValidateElemIndex(b,ib);
        ia--,ib--,iab--)
    {
        ab->data[iab]=__mshSafeElemAtBigUInt(a,ia)+__mshSafeElemAtBigUInt(b,ib);
        int carry=mshIsCarryFlagSet();
        for(size_t jab=iab-1;carry==1;jab--){
            ab->data[jab]=ab->data[jab]+1;
            carry=mshIsCarryFlagSet();
        }
    }
}

const _Bool mshGtBigUInt(const struct mshBigUInt *const a,
                         const struct mshBigUInt *const b)
{
    if(a->len==0&&b->len==0)return 0;
    for(size_t i=mshMax(a->len,b->len)-1;;i--)
    {
        const size_t ad=mshDigitAtBigUInt(a, i);
        const size_t bd=mshDigitAtBigUInt(b, i);
        if(ad>bd)return 1;
        if(ad<bd)return 0;
        if(i==0)break;
    }
    return 0;
}
const _Bool mshLtBigUInt(const struct mshBigUInt *const a,
                         const struct mshBigUInt *const b)
{
    if(a->len==0&&b->len==0)return 0;
    for(size_t i=mshMax(a->len,b->len)-1;;i--)
    {
        const size_t ad=mshDigitAtBigUInt(a, i);
        const size_t bd=mshDigitAtBigUInt(b, i);
        if(ad>bd)return 0;
        if(ad<bd)return 1;
        if(i==0)break;
    }
    return 0;
}
const _Bool mshEqBigUInt(const struct mshBigUInt *const a,
                         const struct mshBigUInt *const b)
{
    if(a->len==0&&b->len==0)return 1;
    for(size_t i=mshMax(a->len,b->len)-1;;i--)
    {
        const size_t ad=mshDigitAtBigUInt(a, i);
        const size_t bd=mshDigitAtBigUInt(b, i);
        if(ad!=bd)return 0;
        if(i==0)break;
    }
    return 1;
}
/*This function is designed in a way that will work even if ab is a pointer to a or b*/
void mshSubBigUInt(const struct mshBigUInt *const a,
                   const struct mshBigUInt *const b,
                   struct mshBigUInt *const ab)
{
    if(mshLtBigUInt(a, b)){
        mshDestroyBigUInt(ab);
        return;
    }
    __mshRelocateBigUInt(ab, a->len);
    const mshBigUIntDoubleElem BORROWED_VAL=((mshBigUIntElem)-1)+(mshBigUIntDoubleElem)1;
    _Bool borrow=0;
    for(size_t i=0;i<a->len;i++){
        mshBigUIntDoubleElem ad=mshDigitAtBigUInt(a, i)-borrow;
        const mshBigUIntDoubleElem bd=mshDigitAtBigUInt(b, i);
        if(ad<bd){
            borrow=1;
            ad+=BORROWED_VAL;
        }
        const mshBigUIntElem newDigit = (mshBigUIntElem)(ad - bd);
        mshSetDigitAtBigUInt(ab, i, newDigit);
    }
}


void mshMulBigUInt(const struct mshBigUInt *const a,
                   const struct mshBigUInt *const b,
                   struct mshBigUInt *const ab)
{
    //Toom–Cook and
    //Schönhage–Strassen
    //multiplication algorithms
    //are most likely not necessary here.
    //We will be mostly multiplying
    //relatively tiny numbers so O(n^2) is ok
    __mshAllocateBigUInt(ab,a->len+b->len);
    for(size_t ai=0;ai<a->len;ai++){
        for(size_t bi=0;bi<b->len;bi++){
            const mshBigUIntDoubleElem de=
                (mshBigUIntDoubleElem)a->data[ai]*
                (mshBigUIntDoubleElem)b->data[bi];
            __mshAddElem(ab,__mshLeftHalfOfDoubleElem(de),ai+bi);
            __mshAddElem(ab,__mshRightHalfOfDoubleElem(de),ai+bi+1);
        }
    }
}

//void mshDivBigUInt(const struct mshBigUInt *const a,
//                   const struct mshBigUInt *const b,
//                   struct mshBigUInt *const ab)
//{
//    __mshAllocateBigUInt(ab,a->len);
//
//}
//
//
//void mshModBigUInt(const struct mshBigUInt *const a,
//                   const struct mshBigUInt *const b,
//                   struct mshBigUInt *const ab)
//{
//
//}


//void mshModularInverseBigUInt(const struct mshBigUInt *const num,
//                              const struct mshBigUInt *const mod,
//                              struct mshBigUInt *const out){
//    if(num%mod==0)return 0;
//    const size_t rem = num%mod;
//    for(size_t i=1;i<mod;i++){
//        const size_t ceil=mshCeil(mod*i,rem);
//        const size_t newRem=(ceil*rem)%mod;
//        if(newRem==1)return ceil;
//    }
//    return 0;
//}





