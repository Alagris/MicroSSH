//
//  math.c
//  MicroSSH
//
//  Created by Alagris on 06/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#include "math.h"

const size_t mshCeil(const size_t num,const size_t div){
    const size_t out=num/div;
    if(num%div==0)return out;
    return out+1;
}

const size_t mshPow(const size_t base, size_t exponent){
    size_t out=1;
    size_t pow=base;
    while(exponent>0){
        if(exponent&1)
            out*=pow;
        pow*=pow;
        exponent>>=1;
    }
    
    return out;
}
//IMPORTANT: doesn't work on 32 bit machines!
//TODO: add 32 bit machine support

asm(
#ifdef __APPLE__
    ".global _mshIsCarryFlagSet\n"
    "_mshIsCarryFlagSet:\n"
#elif defined(__linux__)
    ".global mshIsCarryFlagSet\n"
    "mshIsCarryFlagSet:\n"
#endif
    "jnc mshIsCarryFlagSet_false\n"
    "mshIsCarryFlagSet_true:\n"
    "movl $1,%eax\n"
    "ret\n"
    "mshIsCarryFlagSet_false:\n"
    "movl $0,%eax\n"
    "ret\n"
    );
