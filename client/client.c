//
//  client.c
//  MicroSSH
//
//  Created by Alagris on 05/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#include "client.h"
#include <string.h> //memset
#include <netdb.h> //gethostbyname
#include "default_buffer_len.h"

const enum mshError mshConfigureClient(struct mshClient * const client,
                                       const int port,
                                       const char *const host)
{
    struct hostent *const server = gethostbyname(host);
    if (server == NULL)
        return MSH_HOST_RESOLVE_FAIL;
    
    memset((char *) &client->serv_addr, sizeof(client->serv_addr),0);
    client->serv_addr.sin_family = AF_INET;
    memcpy((char *)server->h_addr,
           (char *)&client->serv_addr.sin_addr.s_addr,
           server->h_length);
    client->serv_addr.sin_port = htons(port);
    client->port=port;
    client->sockfd=-1;
    return MSH_SUCCESS;
}

const enum mshError mshOpenClient(struct mshClient * const client){
    client->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (client->sockfd < 0)
        return MSH_CLIENT_SOCKET_OPEN_FAIL;
    return MSH_SUCCESS;
}


const enum mshError mshConnectClient(const struct mshClient* const client,
                                     struct mshConn *const c)
{
    if (connect(client->sockfd,
                (const struct sockaddr *)&client->serv_addr,
                sizeof(client->serv_addr)) < 0)
        return MSH_SERV_CONNECTION_FAIL;
    c->sockfd=client->sockfd;
    mshOpenPipe(&c->pipe, MSH_DEFAULT_BUFFER_LEN);
    return MSH_SUCCESS;
}

