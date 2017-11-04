#ifndef BBUFF_H
#define BBUFF_H

#define BUFFER_SIZE 10

int buffInit(int size);
void buffPush(int item);
int buffPop();
_Bool buffEmpty();
_Bool buffFull();
void buffFree();

#endif
