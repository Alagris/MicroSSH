//
//  protocol.c
//  MicroSSH
//
//  Created by Alagris on 10/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#include "protocol.h"
const enum mshProtocol mshPopProtocolSemiPipe(struct mshSemiPipe * const p){
    mshSemiPipeElem *const lestElem= mshPtrToEndInSemiPipe(p)-sizeof(enum mshProtocol);
    if(lestElem<p->buffer)return MSH_PROTOCOL_NOTHING;
    const enum mshProtocol signal = *((const enum mshProtocol*)lestElem);
    mshPopSemiPipe(p, sizeof(enum mshProtocol));
    return signal;
}


