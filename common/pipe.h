//
//  pipe.h
//  MicroSSH
//
//  Created by Alagris on 27/11/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#ifndef pipe_h
#define pipe_h

#include "semipipe.h"
struct mshPipe{
    struct mshSemiPipe input;
    struct mshSemiPipe output;
};
#define mshDefaultPipe {.input=mshDefaultSemiPipe,.output=mshDefaultSemiPipe}

void mshOpenPipe(struct mshPipe * const p,const size_t size);

void mshClosePipe(struct mshPipe * const p);

void mshClearPipe(struct mshPipe * const p);

void mshResetPipe(struct mshPipe * const p);

void mshReversePipe(struct mshPipe * const p);

#endif /* pipe_h */
