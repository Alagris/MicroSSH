//
//  threadsafe_shared_resources.h
//  MicroSSH
//
//  Created by Alagris on 10/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#ifndef threadsafe_shared_resources_h
#define threadsafe_shared_resources_h
#include "shared_resources.h"
void mshInitThreadsafetyInArray(void);
void mshThreadsafeMoveRightInArray(void);
void mshThreadsafeMoveLeftInArray(void);
void mshThreadsafeIncrementInArray(void);
void mshThreadsafeDecrementInArray(void);
const mshArrayElem mshThreadsafeGetInArray(void);
#endif /* threadsafe_shared_resources_h */
