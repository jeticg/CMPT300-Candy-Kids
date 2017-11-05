#include <stdio.h>
#include <stdlib.h>
#include "bbuff.h"

// Global variables
int* bbuff;
// Number of items in buffer
int full;
// Number of empty slots in buffer
int empty;
// Point to the item currently on top of the stack
int top;

int buffInit(int size) {
    bbuff = malloc(sizeof(int) * (unsigned long)size);
    full = 0;
    top = 0;
    empty = size;
    #ifdef DEBUG
    printf("--DEBUG: BUFF: top: %d, full: %d, empty: %d\n", top, full, empty);
    #endif
    if (bbuff == NULL)
        // This means an error has occured
        return 1;
    return 0;
}

void buffPush(int item) {
    #ifdef DEBUG
    printf("--DEBUG: BUFF: top: %d, full: %d, empty: %d\n", top, full, empty);
    #endif
    bbuff[(top + full) % (empty + full)] = item;
    full += 1;
    empty -= 1;
    #ifdef DEBUG
    printf("--DEBUG: BUFF: top: %d, full: %d, empty: %d\n", top, full, empty);
    #endif
    return;
}

int buffPop() {
    #ifdef DEBUG
    printf("--DEBUG: BUFF: top: %d, full: %d, empty: %d\n", top, full, empty);
    #endif
    int result = bbuff[top];
    top = (top + 1) % (full + empty);
    full -= 1;
    empty += 1;
    #ifdef DEBUG
    printf("--DEBUG: BUFF: top: %d, full: %d, empty: %d\n", top, full, empty);
    #endif
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
    return;
}
