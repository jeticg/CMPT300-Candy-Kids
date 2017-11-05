#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "aux.h"


int isNumber(const char *s) {
    while (*s) {
        if (isdigit(*s++) == 0) return 0;
    }
    return 1;
}

int convertToNumber(const char *s) {
    int result = 0;
    while (*s) {
        result *= 10;
        result += (int)(*s++ - '0');
    }
    return result;
}

double currentTime() {
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return (double)now.tv_sec * 1000.0 + (double)now.tv_nsec/1000000.0;
}

CANDY encodeCandy(int facId) {
    CANDY candy;
    candy.candyId = rand();
    candy.facId = facId;
    candy.zeit = currentTime();
    return candy;
}

void decodeCandy(CANDY candy, int *facId, double *zeit, int *candyId) {
    *zeit = currentTime() - candy.zeit;
    *facId = candy.facId;
    *candyId = candy.candyId;
}
