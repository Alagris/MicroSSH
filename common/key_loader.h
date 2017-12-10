//
//  key_loader.h
//  MicroSSH
//
//  Created by Alagris on 06/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#ifndef key_loader_h
#define key_loader_h
#include "errors.h"
#include "cryptography.h"
const enum mshError mshLoadPublicKey(struct mshPublicKey *const pubKey,
                                     const char * const file);
const enum mshError mshLoadPrivateKey(struct mshPrivateKey *const privKey,
                                      const char * const file);
const enum mshError mshSavePublicKey(const struct mshPublicKey *const pubKey,
                                     const char * const file);
const enum mshError mshSavePrivateKey(const struct mshPrivateKey *const privKey,
                                      const char * const file);
#endif /* key_loader_h */
