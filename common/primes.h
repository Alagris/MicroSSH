//
//  primes.h
//  MicroSSH
//
//  Created by Alagris on 05/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#ifndef primes_h
#define primes_h
#include <stddef.h>
void mshInitEratosthenesSieve(const size_t size);
const _Bool mshIsInitEratosthenesSieve(void);
const _Bool mshIsPrime(const size_t number);
const size_t mshGetRandomPrime(const size_t minInclusive);
#endif /* primes_h */
