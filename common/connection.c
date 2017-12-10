//
//  connection.c
//  MicroSSH
//
//  Created by Alagris on 05/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#include "connection.h"
#include <unistd.h>//read,write
#include "default_buffer_len.h"

const enum mshError mshFReadFromConn(struct mshConn *const c,int destination_fd){
    c->pipe.input.available += read(destination_fd,
                                    mshPtrToEndInSemiPipe(&c->pipe.input),
                                    mshFreeSpaceInSemiPipe(&c->pipe.input));
    if (c->pipe.input.available < 0) return MSH_CONN_READ_FAIL;
    return MSH_SUCCESS;
}

const enum mshError mshFWriteToConn(struct mshConn *const c,int source_fd){
    const ssize_t n=write(source_fd,
                          c->pipe.output.buffer,
                          c->pipe.output.available);
    if (n < 0) return MSH_CONN_WRITE_FAIL;
    c->pipe.output.available-=n;
    return MSH_SUCCESS;
}

const enum mshError mshCloseConn(struct mshConn *const c){
    if(close(c->sockfd)==-1)
        return MSH_CONN_CLOSE_FAIL;
    c->sockfd=-1;
    mshClosePipe(&c->pipe);
    return MSH_SUCCESS;
}
