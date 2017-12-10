//
//  connection.h
//  MicroSSH
//
//  Created by Alagris on 05/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#ifndef connection_h
#define connection_h
#include "errors.h"
#include "pipe.h"
struct mshConn{
    int sockfd;
    struct mshPipe pipe;
};
#define mshDefaultConn {.sockfd=-1,.pipe=mshDefaultPipe}

const enum mshError mshFReadFromConn(struct mshConn *const c,int destination_fd);

const enum mshError mshFWriteToConn(struct mshConn *const c,int source_fd);

static inline const enum mshError mshWriteToConn(struct mshConn *const c){
    return mshFWriteToConn(c,c->sockfd);
}

static inline const enum mshError mshReadFromConn(struct mshConn *const c){
    return mshFReadFromConn(c,c->sockfd);
}
const enum mshError mshCloseConn(struct mshConn *const c);

#endif /* connection_h */
