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
//    printf("Reply=%d / %d",reply,MSH_PROTOCOL_AUTH_ACCEPTED);
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
    
    
    ////////
//    int sock;
//    struct sockaddr_in server;
//    char message[1000] , server_reply[2000];
//
//    //Create socket
//    sock = socket(AF_INET , SOCK_STREAM , 0);
//    if (sock == -1)
//    {
//        printf("Could not create socket");
//    }
//    puts("Socket created");
//
//    server.sin_addr.s_addr = inet_addr("127.0.0.1");
//    server.sin_family = AF_INET;
//    server.sin_port = htons( 8888 );
//
//    //Connect to remote server
//    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
//    {
//        perror("connect failed. Error");
//        return 1;
//    }
    ///////
    
    struct mshClient client=mshDefaultClient;
    switch(mshConfigureClient(&client, port, host)){
        case MSH_HOST_RESOLVE_FAIL:
            perror("Unresolved host name!");
            return 0;
        case MSH_SUCCESS:
            break;
        default:
            perror("Error while setting up clinet!");
            return 0;
    }
    
    if(mshOpenClient(&client)!=MSH_SUCCESS){
            perror("Could not open socket!");
            return 0;
    }
    
    struct mshConn conn=mshDefaultConn;
    if(mshConnectClient(&client,&conn)!=MSH_SUCCESS){
        perror( "Connection problems!");
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
