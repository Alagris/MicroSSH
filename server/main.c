//
//  main.c
//  MicroSSH
//
//  Created by Alagris on 27/11/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#include "server.h"
#include "connection.h"
#include "default_port.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "key_loader.h"
#include "default_rsa_key_path.h"
#include "protocol.h"
#include "threadsafe_shared_resources.h"

struct mshThreadArgs{
    struct mshConn * c;
    struct mshPublicKey * pub;
};

const _Bool authorize(const struct mshPublicKey *const pub,struct mshConn *const c){
    const size_t num = mshGenRandomNumberRSA(pub->n);
    printf("Num=%lu\n",num);
    const size_t cip=mshCipherNumberRSA(num, pub);
    printf("Cip=%lu\n",cip);
    mshPushReplyConn(c, cip);
    mshWriteToConn(c);
    mshResetPipe(&c->pipe);
    mshReadFromConn(c);
    const size_t decip = mshGetReplyConn(c, 0);
    printf("Decip=%ld\n",decip);
    mshResetPipe(&c->pipe);
    const _Bool output= decip==num;
    mshPushProtocolConn(c, output?MSH_PROTOCOL_AUTH_ACCEPTED:MSH_PROTOCOL_AUTH_DENIED);
    mshWriteToConn(c);
    mshResetPipe(&c->pipe);
    return output;
}

void * thread(void * arg){
    struct mshThreadArgs *const args= (struct mshThreadArgs *)arg;
    struct mshConn *const c = args->c;
    if(authorize(args->pub,c)){
        while(1){
            if(mshReadFromConn(c)!=MSH_SUCCESS)break;
            _Bool hasRepliesToSend=0;
            for(size_t offset=0;
                offset<c->pipe.input.available;
                offset+=sizeof(enum mshProtocol))
            {
                const enum mshProtocol signal=mshGetProtocolConn(c, offset);
                switch (signal) {
                    case MSH_PROTOCOL_END:
                        goto breakForLoop;
                    case MSH_PROTOCOL_GET:
                        mshPushReplyConn(c, mshThreadsafeGetInArray());
                        hasRepliesToSend=1;
                        printf(".");
                        break;
                    case MSH_PROTOCOL_MOV_LEFT:
                        mshThreadsafeMoveLeftInArray();
                        printf("<");
                        break;
                    case MSH_PROTOCOL_MOV_RIGHT:
                        mshThreadsafeMoveRightInArray();
                        printf(">");
                        break;
                    case MSH_PROTOCOL_INC:
                        mshThreadsafeIncrementInArray();
                        printf("+");
                        break;
                    case MSH_PROTOCOL_DEC:
                        mshThreadsafeDecrementInArray();
                        printf("-");
                        break;
                    default:
                        break;
                }
                
            }
        breakForLoop:
            fflush(stdout);
            if(hasRepliesToSend){
                mshWriteToConn(c);
            }
            mshResetPipe(&c->pipe);
        }
    }
    mshCloseConn(c);
    free(c);
    free(args);
    return NULL;
}


int main(int argc, char *argv[])
{
    struct mshPublicKey pub=mshDefaultPublicKey;
    if(mshLoadPublicKey(&pub, MSH_DEFAULT_RSA_PUBKEY_PATH)!=MSH_SUCCESS){
        fprintf(stderr, "Make sure \'%s\' is in working directory!\n", MSH_DEFAULT_RSA_PUBKEY_PATH);
        return 0;
    }
    printf("Loaded public key:\n");
    printf("%ld\n",pub.n);
    
    struct mshServer s=mshDefaultServer;
    int port=argc==2?atoi(argv[1]):MSH_DEFAULT_PORT;
    printf("Starting server on port %d\n",port);
    mshConfigureServ(&s, port);
    mshOpenServ(&s);
    mshBindServ(&s);
    mshListenServ(&s);
    
    
    mshInitThreadsafetyInArray();
    
    while(1){
        pthread_t t;
        struct mshConn * c=malloc(sizeof(struct mshConn));
        mshConnectServ(&s, c);
        struct mshThreadArgs * args=malloc(sizeof(struct mshThreadArgs));
        args->c=c;
        args->pub=&pub;
        pthread_create(&t, NULL, thread, (void*)args);
    }
    
}

