//
//  server.h
//  MicroSSH
//
//  Created by Alagris on 27/11/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#ifndef server_h
#define server_h
#include <netinet/in.h>
#include "errors.h"
#include "connection.h"
struct mshServer{
    int sockfd;
    int port;
    struct sockaddr_in serv_addr;
};
#define mshDefaultServer {.sockfd=-1,.port=-1}
void mshConfigureServ(struct mshServer * const serv,const int port);
const enum mshError mshOpenServ(struct mshServer * const serv);
const enum mshError mshBindServ(struct mshServer * const serv);
const enum mshError mshListenServ(struct mshServer * const serv);
const enum mshError mshConnectServ(const struct mshServer * const serv,
                                   struct mshConn *const c);


#endif /* server_h */
