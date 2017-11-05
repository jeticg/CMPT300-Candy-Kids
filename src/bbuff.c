#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "bbuff.h"

// Global variables
int* bbuff;
// Number of items in buffer
int full;
// Number of empty slots in buffer
int empty;
// Point to the item currently on top of the stack
int top;

// Lock
pthread_mutex_t buffMutex;

int buffInit(int size) {
    if (pthread_mutex_init(&buffMutex, NULL) != 0) {
        printf("\nError: mutex init failed\n");
        return 1;
    }
    bbuff = malloc(sizeof(int) * (unsigned long)size);
    full = 0;
    top = 0;
    empty = size;
    if (bbuff == NULL)
        // This means an error has occured
        return 1;
    return 0;
}

void buffPush(int item) {
    pthread_mutex_lock(&buffMutex);
    bbuff[(top + full) % (empty + full)] = item;
    full += 1;
    empty -= 1;
    pthread_mutex_unlock(&buffMutex);
    return;
}

int buffPop() {
    pthread_mutex_lock(&buffMutex);
    int result = bbuff[top];
    top = (top + 1) % (full + empty);
    full -= 1;
    empty += 1;
    pthread_mutex_unlock(&buffMutex);
    return result;
}

_Bool buffEmpty() {
    return (full == 0);
}

_Bool buffFull() {
    return (empty == 0);
}

void buffFree() {
    free(bbuff);
    pthread_mutex_destroy(&buffMutex);
    return;
}
