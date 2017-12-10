//
//  server.c
//  MicroSSH
//
//  Created by Alagris on 27/11/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#include "server.h"
#include "default_buffer_len.h"

void mshConfigureServ(struct mshServer * const serv,const int port){
    serv->port=port;
    serv->serv_addr.sin_family = AF_INET;
    serv->serv_addr.sin_port = htons(port);
    serv->serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv->sockfd=-1;
}

const enum mshError mshOpenServ(struct mshServer * const serv){
    serv->sockfd=socket(AF_INET, SOCK_STREAM, 0);
    if (serv->sockfd < 0)
        return MSH_SERV_SOCKET_OPEN_FAIL;
    return MSH_SUCCESS;
}
const enum mshError mshBindServ(struct mshServer * const serv){
    struct sockaddr * addrptr =(struct sockaddr *) &serv->serv_addr;
    if (bind(serv->sockfd, addrptr,sizeof(serv->serv_addr)) < 0)
        return MSH_SERV_SOCKET_BIND_FAIL;
    return MSH_SUCCESS;
}

const enum mshError mshListenServ(struct mshServer * const serv){
    if(listen(serv->sockfd,5)!=0)
        return MSH_SERV_LISTEN_FAIL;
    return MSH_SUCCESS;
}

const enum mshError mshConnectServ(const struct mshServer * const serv,struct mshConn *const c)
{
    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    struct sockaddr * addrptr =(struct sockaddr *) &cli_addr;
    c->sockfd = accept(serv->sockfd, addrptr, &clilen);
    if (c->sockfd < 0)
        return MSH_SERV_CONNECTION_FAIL;
    mshOpenPipe(&c->pipe, MSH_DEFAULT_BUFFER_LEN);
    return MSH_SUCCESS;
}
