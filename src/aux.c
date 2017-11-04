#include <ctype.h>
#include <stdio.h>

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
