//
//  main.c
//  MicroSSH
//
//  Created by Alagris on 05/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include "default_port.h"
#include "default_host.h"
#include "client.h"
#include "connection.h"
#include "default_rsa_key_path.h"
#include "key_loader.h"
#include "protocol.h"
const _Bool authorize(const struct mshPrivateKey *const priv,struct mshConn *const c){
    mshReadFromConn(c);
    const size_t cip=mshGetReplyConn(c, 0);
    printf("Cip=%lu\n",cip);
    const size_t decip=mshDecipherNumberRSA(cip, priv);
    mshResetPipe(&c->pipe);
    printf("Decip=%ld\n",decip);
    mshPushReplyConn(c, decip);
    mshWriteToConn(c);
    mshResetPipe(&c->pipe);
    mshReadFromConn(c);
    const enum mshProtocol reply=mshGetProtocolConn(c, 0);
    mshResetPipe(&c->pipe);
    return reply==MSH_PROTOCOL_AUTH_ACCEPTED;
    
}

int main(int argc, char *argv[]){
    struct mshPrivateKey priv=mshDefaultPrivateKey;
    if(mshLoadPrivateKey(&priv, MSH_DEFAULT_RSA_KEY_PATH)!=MSH_SUCCESS){
        fprintf(stderr, "Make sure \'%s\' is in working directory!\n", MSH_DEFAULT_RSA_KEY_PATH);
        return 0;
    }
    printf("Loaded private key:\n");
    printf("%ld %ld %ld %ld\n",priv.n,priv.d,priv.p,priv.q);
    
    
    const int port=argc==3?atoi(argv[2]):MSH_DEFAULT_PORT;
    const char *const host=argc>=2?argv[1]:MSH_DEFAULT_HOST;
    printf("Connecting to %s:%d\n",host,port);
    struct mshClient client=mshDefaultClient;
    mshConfigureClient(&client, port, host);
    mshOpenClient(&client);
    struct mshConn conn=mshDefaultConn;
    if(mshConnectClient(&client,&conn)!=MSH_SUCCESS){
        fprintf(stderr, "Connection problems!\n");
        return 0;
    }
    
    
    
    ///Client authorization
    if(authorize(&priv,&conn)){
        ///After client passed authorization
        while(1){
            char buff[32];
            scanf("%31s",buff);
            size_t extectedReplies=0;
            for(size_t i=0;buff[i]!='\0';i++){
                enum mshProtocol signal;
                switch (buff[i]) {
                    case '+':
                        signal=MSH_PROTOCOL_INC;
                        break;
                    case '-':
                        signal=MSH_PROTOCOL_DEC;
                        break;
                    case '>':
                        signal=MSH_PROTOCOL_MOV_RIGHT;
                        break;
                    case '<':
                        signal=MSH_PROTOCOL_MOV_LEFT;
                        break;
                    case '.':
                        extectedReplies++;
                        signal=MSH_PROTOCOL_GET;
                        break;
                    default:
                        signal=MSH_PROTOCOL_NOTHING;
                        break;
                }
                mshPushProtocolConn(&conn, signal);
            }
            mshPushProtocolConn(&conn, MSH_PROTOCOL_END);
            mshWriteToConn(&conn);
            mshResetSemiPipe(&conn.pipe.output);
            if(extectedReplies>0){
                mshReadFromConn(&conn);
                for(size_t offset=0;extectedReplies-->0;offset+=sizeof(mshProtocolReply)){
                    const mshProtocolReply reply=mshGetReplyConn(&conn, offset);
                    printf("%lu\n",reply);
                }
                mshResetSemiPipe(&conn.pipe.input);
            }
        }
    }else{
        printf("Connection denied by server! Private key not matching!\n");
    }
}
