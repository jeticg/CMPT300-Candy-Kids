#include <ctype.h>
#include <stdio.h>
#include <time.h>

#include "aux.h"

#define ENC_N 1000000

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
    return now.tv_sec * 1000.0 + now.tv_nsec/ENC_N.0;
}

int encodeCandy(int facId) {
    return (int)(currentTime()*ENC_N)<<10+facId;
}

void decodeCandy(int candyId, int *facId, double *zeit) {
    *zeit = (double)(((int)(currentTime()*ENC_N)<<10-candyId)>>10)/ENC_N.0;
    *facId = candyId%(1<<10);
}
