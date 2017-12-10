//
//  default_rsa_key_path.c
//  MicroSSH
//
//  Created by Alagris on 09/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#include "default_rsa_key_path.h"

#define MSH_PUB_SUFFIX_MACRO ".pub"
const char * const MSH_DEFAULT_RSA_KEY_PATH="rsakey";
const size_t MSH_DEFAULT_RSA_KEY_PATH_LEN=sizeof(MSH_DEFAULT_RSA_KEY_PATH)-1;
const char * const MSH_DEFAULT_RSA_PUBKEY_PATH="rsakey" MSH_PUB_SUFFIX_MACRO;
const size_t MSH_DEFAULT_RSA_PUBKEY_PATH_LEN=sizeof(MSH_DEFAULT_RSA_PUBKEY_PATH)-1;
const char * const MSH_PUB_SUFFIX=MSH_PUB_SUFFIX_MACRO;
const size_t MSH_PUB_SUFFIX_LEN=sizeof(MSH_PUB_SUFFIX)-1;
#undef MSH_PUB_SUFFIX_MACRO
