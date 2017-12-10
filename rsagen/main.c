//
//  main.c
//  MicroSSH
//
//  Created by Alagris on 09/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#include <stdio.h>
#include "cryptography.h"
#include "key_loader.h"
#include <string.h>
#include "default_rsa_key_path.h"
int main(int argc, char *argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: rsagen <path/to/generated/file>");
        return 0;
    }
    const char * const privFile=argv[1];
    const size_t privFileLen=strlen(privFile);
    
    const size_t pubFileLen=privFileLen+MSH_PUB_SUFFIX_LEN;
    char pubFile[pubFileLen+1];//plus '\0'
    strcpy(pubFile, privFile);
    strcat(pubFile, MSH_PUB_SUFFIX);
    
    struct mshPublicKey pub;
    struct mshPrivateKey priv;
    mshKeyGenRSA(&pub, &priv);
    
    printf("Generated keys:\n");
    printf("PUBLIC:\n");
    printf("%ld\n",pub.n);
    printf("PRIVATE:\n");
    printf("%ld %ld %ld %ld\n",priv.n,priv.d,priv.p,priv.q);
    
    mshSavePublicKey(&pub, pubFile);
    mshSavePrivateKey(&priv, privFile);
    
}
