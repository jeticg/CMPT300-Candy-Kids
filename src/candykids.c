// Include standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>


// Include library
#include "aux.h"
#include "bbuff.h"

// Global variables
pthread_t* kids;
pthread_t* factories;

void* factory(void* threadId) {
    int facId = *(int*)threadId;
    printf("I am a factory, #%d!\n", facId);
    pthread_exit(NULL);
}

void* kid(void* threadId) {
    int kidId = *(int*)threadId;
    printf("I am a kid, #%d!\n", kidId);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    /*
        1. Extract arguments
    */
    if(argc != 4) {
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


    /*
        2. Initialize modules
    */
    #ifdef DEBUG
    printf("--DEBUG: Initialising\n");
    #endif
    buffInit(5);
    int* facIds = malloc(sizeof(int) * (unsigned int)numFac);
    int* kidIds = malloc(sizeof(int) * (unsigned int)numKid);
    factories = malloc(sizeof(pthread_t) * (unsigned int)numFac);
    kids = malloc(sizeof(pthread_t) * (unsigned int)numKid);
    #ifdef DEBUG
    printf("--DEBUG: Initialisation complete\n");
    #endif

    /*
        3. Launch candy-factory threads
    */
    #ifdef DEBUG
    printf("--DEBUG: Creating factories\n");
    #endif
    for(int i=0; i<numFac; i++) {
        /* Create the factory */
        facIds[i] = i;
        pthread_create(&factories[i], NULL, factory, (void *)&facIds[i]);
    }
    #ifdef DEBUG
    printf("--DEBUG: Factories created\n");
    #endif

    /*
        4. Launch kid threads
    */
    #ifdef DEBUG
    printf("--DEBUG: Creating kids\n");
    #endif
    for(int i=0; i<numKid; i++) {
        /* Create the kid */
        kidIds[i] = i;
        pthread_create(&kids[i], NULL, kid, (void *)&kidIds[i]);
    }
    #ifdef DEBUG
    printf("--DEBUG: Kids created\n");
    #endif

    /*
        5. Wait for requested time
    */
    #ifdef DEBUG
    printf("--DEBUG: Main thread sleeping\n");
    #endif
    sleep((unsigned int)numSec);
    #ifdef DEBUG
    printf("--DEBUG: Main thread awaking\n");
    #endif

    /*
        6. Stop candy-factory threads
    */
    #ifdef DEBUG
    printf("--DEBUG: Stopping facotries\n");
    #endif
    for(int i=0; i<numFac; i++) {
        // stop the factories
        pthread_cancel(factories[i]);
    }
    #ifdef DEBUG
    printf("--DEBUG: Releasing factories and facIds memory\n");
    #endif
    free(facIds);
    free(factories);
    #ifdef DEBUG
    printf("--DEBUG: Factories stopped\n");
    #endif

    /*
        7. Wait until no more candy
    */

    /*
        8. Stop kid threads
    */
    #ifdef DEBUG
    printf("--DEBUG: Stopping kids\n");
    #endif
    for(int i=0; i<numKid; i++) {
        // stop the kids
        pthread_cancel(kids[i]);
    }
    #ifdef DEBUG
    printf("--DEBUG: Releasing kids and kidIds memory\n");
    #endif
    free(kidIds);
    free(kids);
    #ifdef DEBUG
    printf("--DEBUG: Kids stopped\n");
    #endif

    // 9. Print statistics
    // 10. Cleanup any allocated memory
    #ifdef DEBUG
    printf("--DEBUG: Start cleaning up\n");
    #endif
    buffFree();
    pthread_exit(NULL);
    #ifdef DEBUG
    printf("--DEBUG: Cleanup complete, Programme exits\n");
    #endif
    return 0;
}
