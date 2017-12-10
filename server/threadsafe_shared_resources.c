//
//  threadsafe_shared_resources.c
//  MicroSSH
//
//  Created by Alagris on 10/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#include "threadsafe_shared_resources.h"
#include <pthread.h>
pthread_mutex_t __mshMutex;
void mshInitThreadsafetyInArray(void){
    pthread_mutex_init(&__mshMutex, 0);
}
void mshThreadsafeMoveRightInArray(void){
    pthread_mutex_lock(&__mshMutex);
    mshMoveRightInArray();
    pthread_mutex_unlock(&__mshMutex);
}
void mshThreadsafeMoveLeftInArray(void){
    pthread_mutex_lock(&__mshMutex);
    mshMoveLeftInArray();
    pthread_mutex_unlock(&__mshMutex);
}
void mshThreadsafeIncrementInArray(void){
    pthread_mutex_lock(&__mshMutex);
    mshIncrementInArray();
    pthread_mutex_unlock(&__mshMutex);
}
void mshThreadsafeDecrementInArray(void){
    pthread_mutex_lock(&__mshMutex);
    mshDecrementInArray();
    pthread_mutex_unlock(&__mshMutex);
}
const mshArrayElem mshThreadsafeGetInArray(void){
    pthread_mutex_lock(&__mshMutex);
    const mshArrayElem out = mshGetInArray();
    pthread_mutex_unlock(&__mshMutex);
    return out;
}
