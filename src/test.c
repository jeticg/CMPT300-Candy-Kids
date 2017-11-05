#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "aux.h"

int main() {
    CANDY tmp;
    int id;
    double zeit;
    tmp = encodeCandy(1);
    sleep(0);
    decodeCandy(tmp, &id, &zeit);
    printf("1:, id %d, time %10.5lf\n", id, zeit);
    tmp = encodeCandy(2);
    sleep(1);
    decodeCandy(tmp, &id, &zeit);
    printf("2:, id %d, time %10.5lf\n", id, zeit);
    tmp = encodeCandy(3);
    sleep(2);
    decodeCandy(tmp, &id, &zeit);
    printf("3:, id %d, time %10.5lf\n", id, zeit);
    tmp = encodeCandy(4);
    sleep(3);
    decodeCandy(tmp, &id, &zeit);
    printf("4:, id %d, time %10.5lf\n", id, zeit);
    tmp = encodeCandy(5);
    sleep(4);
    decodeCandy(tmp, &id, &zeit);
    printf("5:, id %d, time %10.5lf\n", id, zeit);
    tmp = encodeCandy(6);
    sleep(5);
    decodeCandy(tmp, &id, &zeit);
    printf("6:, id %d, time %10.5lf\n", id, zeit);
    tmp = encodeCandy(7);
    sleep(6);
    decodeCandy(tmp, &id, &zeit);
    printf("7:, id %d, time %10.5lf\n", id, zeit);
    return 0;
}
