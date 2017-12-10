//
//  cryptography.c
//  MicroSSH
//
//  Created by Alagris on 05/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#include "cryptography.h"
#include "primes.h"
#include "modulo.h"
#include "math.h"
#include <time.h>
#include <stdlib.h>
/////////////////////////
///Implementation of RSA
/////////////////////////
static const size_t e=257;//it is prime

/**Issiues with key generation:
 - keys are very short (everything is stored in long numbers)
 - primes are generated pseudorandomly in a insecure way. Not
 to mention that the seed depends on current time. If attacker is able to
 estiamte time of key-generation then he could quite easily brute force it
 */
void mshKeyGenRSA(struct mshPublicKey * const publicKey,
                  struct mshPrivateKey * const privateKey)
{
    if(!mshIsInitEratosthenesSieve())mshInitEratosthenesSieve(1000);
    
    size_t p,q,d,n;
    while(1){
        while(1){
            p = mshGetRandomPrime(100);
            if((p-1)%e!=0)break;
        }
        while(1){
            q = mshGetRandomPrime(100);
            if((q-1)%e!=0)break;
        }
        n=p*q;
        /**multiplication overflow*/
        if(mshIsCarryFlagSet())continue;
        /**it is very important that the last bit of n is 0*/
        if(n>>(sizeof(size_t)*8-1))continue;
        const size_t phi=(p-1)*(q-1);
        d = mshModularInverse(e, phi);
        if(d!=0)break;
    }
    
    publicKey->n=n;
    privateKey->n=n;
    privateKey->d=d;
    privateKey->p=p;
    privateKey->q=q;
}
const size_t __mshMulMod(size_t a,const size_t b,const size_t mod){
    if(mod>>(sizeof(size_t)*8-1))return 0;
    a%=mod;
    size_t out=0;
    for(size_t i=0;i<sizeof(size_t)*8;i++,a=(a<<1)%mod)
        if((b>>i)&1)
            out=(out+a)%mod;
    return out;
    
}
const size_t __mshPowMod(size_t base,size_t exponent,const size_t mod){
    base%=mod;
    size_t out=1;
    size_t pow=base;
    while(exponent>0){
        if(exponent&1){
            out=__mshMulMod(out,pow,mod);
        }
        pow=__mshMulMod(pow,pow,mod);
        exponent>>=1;
    }
    
    return out;
}

const size_t mshCipherNumberRSA(const size_t num,
                             const struct mshPublicKey * const publicKey)
{
    
    return __mshPowMod(num, e,publicKey->n);
}

const size_t mshDecipherNumberRSA(const size_t num,
                              const struct mshPrivateKey * const privateKey)
{
    return __mshPowMod(num, privateKey->d,privateKey->n);
}

const size_t mshGenRandomNumberRSA(const size_t n){
    srand((unsigned int)time(NULL));
    return rand()%n;
}
//void mshDecipherBuffer(byte * const buffer,
//                       size_t bufLen,
//                       const struct mshPrivateKey * const privateKey);
//void mshCipherBuffer(byte * const buffer,
//                     size_t bufLen,
//                     const struct mshPublicKey * const publicKey)
//{
//}

