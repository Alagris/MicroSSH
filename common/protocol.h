//
//  protocol.h
//  MicroSSH
//
//  Created by Alagris on 10/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#ifndef protocol_h
#define protocol_h
#include "semipipe.h"
#include "connection.h"
#include <stddef.h>
enum mshProtocol{
    MSH_PROTOCOL_AUTH_ACCEPTED,
    MSH_PROTOCOL_AUTH_DENIED,
    MSH_PROTOCOL_MOV_LEFT,
    MSH_PROTOCOL_MOV_RIGHT,
    MSH_PROTOCOL_INC,
    MSH_PROTOCOL_DEC,
    MSH_PROTOCOL_GET,
    MSH_PROTOCOL_END,
    MSH_PROTOCOL_NOTHING,
    
};

typedef size_t mshProtocolReply;


static inline const size_t mshPushProtocolSemiPipe(struct mshSemiPipe * const p,
                                                   const enum mshProtocol m)
{
    return mshPrimitivePushSemiPipe(p,m);
}
static inline const size_t mshPushProtocolPipe(struct mshPipe * const p,
                                               const enum mshProtocol m)
{
    return mshPushProtocolSemiPipe(&p->output,m);
}
static inline const size_t mshPushProtocolConn(struct mshConn * const c,
                                               const enum mshProtocol m)
{
    return mshPushProtocolPipe(&c->pipe,m);
}
///////////
const enum mshProtocol mshPopProtocolSemiPipe(struct mshSemiPipe * const p);
static inline const enum mshProtocol mshPopProtocolPipe(struct mshPipe * const p)
{
    return mshPopProtocolSemiPipe(&p->input);
}
static inline const enum mshProtocol mshPopProtocolConn(struct mshConn * const c)
{
    return mshPopProtocolPipe(&c->pipe);
}
///////////
static inline const enum mshProtocol mshGetProtocolSemiPipe(struct mshSemiPipe * const p,
                                                            const size_t offset)
{
    return mshPrimitiveGetSemiPipe(*p,offset,const enum mshProtocol);
}
static inline const enum mshProtocol mshGetProtocolPipe(struct mshPipe * const p,
                                                            const size_t offset)
{
    return mshGetProtocolSemiPipe(&p->input,offset);
}
static inline const enum mshProtocol mshGetProtocolConn(struct mshConn * const c,
                                                        const size_t offset)
{
    return mshGetProtocolPipe(&c->pipe,offset);
}
///////////
static inline const size_t mshPushReplySemiPipe(struct mshSemiPipe * const p,
                                                const mshProtocolReply m)
{
   return mshPrimitivePushSemiPipe(p,m);
}
static inline const size_t mshPushReplyPipe(struct mshPipe * const p,
                                                const mshProtocolReply m)
{
    return mshPushReplySemiPipe(&p->output,m);
}
static inline const size_t mshPushReplyConn(struct mshConn * const c,
                                            const mshProtocolReply m)
{
    return mshPushReplyPipe(&c->pipe,m);
}
///////////
static inline const mshProtocolReply mshGetReplySemiPipe(struct mshSemiPipe * const p,
                                                            const size_t offset)
{
    return mshPrimitiveGetSemiPipe(*p,offset,const mshProtocolReply);
}

static inline const mshProtocolReply mshGetReplyPipe(struct mshPipe * const p,
                                                     const size_t offset)
{
    return mshGetReplySemiPipe(&p->input,offset);
}
static inline const mshProtocolReply mshGetReplyConn(struct mshConn * const c,
                                                     const size_t offset)
{
    return mshGetReplyPipe(&c->pipe,offset);
}
#endif /* protocol_h */
