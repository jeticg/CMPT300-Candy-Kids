// Include standard library
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <pthread.h>
#include <signal.h>
#include <ctype.h>

// Include library
#include "aux.h"
#include "bbuff.h"

// Global variables
pthread_t tid;
pthread_attr_t attr;

void* factory(void* param) {
    (void)param;
    printf("I am a factory\n");
    return NULL;
}

void* kid(void* param) {
    (void)param;
    printf("I am a kid\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    /*
        1. Extract arguments
    */
    if( argc != 4 ) {
        printf("Error, must have 3 arguments\n\n");
        printf("Usage: ./candykids <#factories> <#kids> <#seconds>\n");
        return 1;
    }
    // Check if all input meets requirements
    for (int i=1; i<argc; i++) {
        if (isNumber(argv[i]) == 0) {
            printf("Error, arguments must be numbers\n\n");
            printf("Usage: ./candykids <#factories> <#kids> <#seconds>\n");
            return 1;
        }
        if (convertToNumber(argv[i]) <= 0) {
            printf("Error, arguments must be positive integers\n\n");
            printf("Usage: ./candykids <#factories> <#kids> <#seconds>\n");
            return 1;
        }
    }

    // Process arguments
    int numFac = convertToNumber(argv[1]);
    int numKid = convertToNumber(argv[2]);
    int numSec = convertToNumber(argv[3]);
    #ifdef DEBUG
    printf("--DEBUG: numFac = %d\n", numFac);
    printf("--DEBUG: numKid = %d\n", numKid);
    printf("--DEBUG: numSec = %d\n", numSec);
    #endif


    /* 2. Initialize modules */
    buffInit(5);
    // 3. Launch candy-factory threads
    for(int i=0; i<numFac; i++) {
        /* Create the thread */
        pthread_create(&tid, &attr, factory, NULL);
    }
    // 4. Launch kid threads
    for(int i=0; i<numKid; i++) {
        /* Create the thread */
        pthread_create(&tid, &attr, kid, NULL);
    }
    // 5. Wait for requested time
    /* Sleep for the specified amount of time in milliseconds */
    sleep((unsigned int)numSec);
    // 6. Stop candy-factory threads
    // 7. Wait until no more candy
    // 8. Stop kid threads
    // 9. Print statistics
    // 10. Cleanup any allocated memory
    return 0;
}
