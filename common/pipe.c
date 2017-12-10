//
//  pipe.c
//  MicroSSH
//
//  Created by Alagris on 27/11/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#include "pipe.h"
#include <string.h>//memset


void mshOpenPipe(struct mshPipe * const p,const size_t size){
    mshOpenSemiPipe(&p->input, size);
    mshOpenSemiPipe(&p->output, size);
}

void mshClosePipe(struct mshPipe * const p){
    mshCloseSemiPipe(&p->input);
    mshCloseSemiPipe(&p->output);
}
void mshResetPipe(struct mshPipe * const p){
    mshResetSemiPipe(&p->input);
    mshResetSemiPipe(&p->output);
}

void mshClearPipe(struct mshPipe * const p){
    mshClearSemiPipe(&p->input);
    mshClearSemiPipe(&p->output);
}

void mshReversePipe(struct mshPipe * const p){
    mshSemiPipeElem * tmp =p->input.buffer;
    p->input.buffer=p->output.buffer;
    p->output.buffer=tmp;
    
    const ssize_t tmp2=p->input.available;
    p->input.available=p->output.available;
    p->output.available=tmp2;
    
    const ssize_t tmp3=p->input.size;
    p->input.size=p->output.size;
    p->output.size=tmp3;
}

