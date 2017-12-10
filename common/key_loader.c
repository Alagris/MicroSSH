//
//  key_loader.c
//  MicroSSH
//
//  Created by Alagris on 06/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#include "key_loader.h"
#include <stdarg.h>
#include <stdio.h>



const enum mshError mshLoadPublicKey(struct mshPublicKey *const pubKey,
                                     const char * const file)
{
    FILE *const f=fopen(file, "r");
    if(f==0)return MSH_FILE_OPEN_FAIL;
    const size_t numsToRead=1;
    if(fread(&pubKey->n, sizeof(size_t), numsToRead, f)!=numsToRead)
        return MSH_FILE_READ_FAIL;
    fclose(f);
    return MSH_SUCCESS;
}
const enum mshError mshLoadPrivateKey(struct mshPrivateKey *const privKey,
                                      const char * const file)
{
    FILE *const f=fopen(file, "r");
    if(f==0)return MSH_FILE_OPEN_FAIL;
    const size_t numsToRead=4;
    size_t arr[4];
    if(fread(arr, sizeof(size_t), numsToRead, f)!=numsToRead)
        return MSH_FILE_READ_FAIL;
    privKey->d=arr[0];
    privKey->n=arr[1];
    privKey->p=arr[2];
    privKey->q=arr[3];
    fclose(f);
    return MSH_SUCCESS;
}
const enum mshError mshSavePublicKey(const struct mshPublicKey *const pubKey,
                                     const char * const file)
{
    FILE *const f=fopen(file, "w");
    if(f==0)return MSH_FILE_OPEN_FAIL;
    const size_t numsToRead=1;
    if(fwrite(&pubKey->n, sizeof(size_t), numsToRead, f)!=numsToRead)
        return MSH_FILE_WRITE_FAIL;
    fclose(f);
    return MSH_SUCCESS;
}
const enum mshError mshSavePrivateKey(const struct mshPrivateKey *const privKey,
                                      const char * const file)
{
    FILE *const f=fopen(file, "w");
    if(f==0)return MSH_FILE_OPEN_FAIL;
    const size_t numsToRead=4;
    size_t arr[4]={privKey->d,privKey->n,privKey->p,privKey->q};
    if(fwrite(arr, sizeof(size_t), numsToRead, f)!=numsToRead)
        return MSH_FILE_WRITE_FAIL;
    fclose(f);
    return MSH_SUCCESS;
}
