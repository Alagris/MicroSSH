//
//  modulo.c
//  MicroSSH
//
//  Created by Alagris on 06/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#include "modulo.h"
#include "math.h"
const size_t mshModularInverse(const size_t num,const size_t mod){
    if(num%mod==0)return 0;
    const size_t rem = num%mod;
    for(size_t i=1;i<mod;i++){
        const size_t ceil=mshCeil(mod*i,rem);
        const size_t newRem=(ceil*rem)%mod;
        if(newRem==1)return ceil;
    }
    return 0;
}
