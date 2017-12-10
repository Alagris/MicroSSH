//
//  cryptography.h
//  MicroSSH
//
//  Created by Alagris on 05/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#ifndef cryptography_h
#define cryptography_h
#include <stddef.h>

struct mshPrivateKey{
    size_t n,d,p,q;
};
#define mshDefaultPrivateKey {.n=0,.d=0,.p=0,.q=0}
struct mshPublicKey{
    size_t n;
};
#define mshDefaultPublicKey {.n=0}
void mshKeyGenRSA(struct mshPublicKey * const publicKey,
                  struct mshPrivateKey * const privateKey);
const size_t mshCipherNumberRSA(const size_t num,
                                const struct mshPublicKey * const publicKey);
const size_t mshDecipherNumberRSA(const size_t num,
                                 const struct mshPrivateKey * const privateKey);
const size_t mshGenRandomNumberRSA(const size_t n);
//
//void mshCipherBuffer(byte * const buffer,
//                     size_t bufLen,
//                     const struct mshPublicKey * const publicKey);
//
//void mshDecipherBuffer(byte * const buffer,
//                       size_t bufLen,
//                       const struct mshPrivateKey * const privateKey);

#endif /* cryptography_h */
