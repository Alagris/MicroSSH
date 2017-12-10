//
//  primes.c
//  MicroSSH
//
//  Created by Alagris on 05/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#include "primes.h"
#include "bitset.h"
#include <stdlib.h>
#include <time.h>
static struct mshBitset sieve=mshDefaultBitset;
static size_t maxPrime=0;
void mshInitEratosthenesSieve(const size_t size){
    mshEnsureCapacityBitset(&sieve, size);
    mshClearBitset(&sieve);
    //clear bit = prime
    //set bit = non-prime
    
    const size_t len=mshCountBitsInBitset(&sieve);
    
    for(size_t i=2;i<len/2;i++)
        for(size_t j=len/i+1;j>1;j--)
            if(mshIsPrime(j))
                if(i*j<len)
                    mshSetBitset(&sieve,i*j,1);
    
    maxPrime=mshPrevUnsetBitInBitset(&sieve,mshCountBitsInBitset(&sieve));
    srand((unsigned int)time(NULL));
}

const _Bool mshIsInitEratosthenesSieve(void){
    return sieve.data!=0;
}


const _Bool mshIsPrime(const size_t number){
    return !mshTestBitset(&sieve, number);
}

const size_t mshGetRandomPrime(const size_t minInclusive){
    const size_t maxExclusive=mshCountBitsInBitset(&sieve);
    const size_t range = maxExclusive-minInclusive;
    if(range<=0)return 0;
    const int random=rand();
    const size_t output=minInclusive+random*range/RAND_MAX;
    if(output>=maxPrime)
        return maxPrime;
    else
        return mshNextUnsetBitInBitset(&sieve, output);
}

