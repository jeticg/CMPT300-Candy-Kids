#ifndef BBUFF_H
#define BBUFF_H

#define BUFFER_SIZE 10
#include "aux.h"

int buffInit(int size);
void buffPush(CANDY item);
CANDY buffPop();
_Bool buffEmpty();
_Bool buffFull();
void buffFree();

#endif
