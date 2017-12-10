//
//  math.h
//  MicroSSH
//
//  Created by Alagris on 06/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#ifndef math_h
#define math_h
#include <stddef.h>
const size_t mshCeil(const size_t num,const size_t div);
const size_t mshPow(const size_t base, size_t exponent);
static inline const size_t mshMax(const size_t b,const size_t a){
    return a>b?a:b;
}
static inline const size_t mshMin(const size_t b,const size_t a){
    return a<b?a:b;
}
int mshIsCarryFlagSet();

#endif /* math_h */
