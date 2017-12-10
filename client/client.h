//
//  client.h
//  MicroSSH
//
//  Created by Alagris on 05/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#ifndef client_h
#define client_h
#include <netinet/in.h>
#include "errors.h"
#include "connection.h"
struct mshClient{
    int sockfd;
    int port;
    struct sockaddr_in serv_addr;
};
#define mshDefaultClient {.sockfd=-1,.port=-1}
const enum mshError mshConfigureClient(struct mshClient * const client,
                                       const int port,
                                       const char *const host);
const enum mshError mshOpenClient(struct mshClient * const client);


const enum mshError mshConnectClient(const struct mshClient* const client,
                                     struct mshConn *const c);


#endif /* client_h */
