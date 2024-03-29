// Include standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
//     threads and locks
#include <pthread.h>
#include <fcntl.h>
#include <semaphore.h>


// Include library
#include "aux.h"
#include "bbuff.h"
#include "stats.h"

// Global variables
pthread_t* kids;
pthread_t* factories;
//     Locks!
pthread_mutex_t mutex;
sem_t fullLock, emptyLock;
//     Factory Status
int factoryRuns;

void* factory(void* threadId) {
    int facId = *(int*)threadId;
    printf("Candy-factory %d Open for business!\n", facId);

    CANDY candy;
    while (factoryRuns == 1) {
        unsigned int napTime = (unsigned int)rand() % 4;  // Either 0 or 1 or 2 or 3

        // Generate candy
        candy = encodeCandy(facId);

        // Put the candy into buffer
        sem_wait(&emptyLock);
        pthread_mutex_lock(&mutex);
        // Achtung, kritische Abteilung!!!
        buffPush(candy);
        statsAdd(facId);
        printf("\tFactory %d ships candy %d & waits %ds\n",
               facId, candy.candyId, napTime);
        pthread_mutex_unlock(&mutex);
        sem_post(&fullLock);

        // nap time
        sleep(napTime);
    }
    printf("Candy-factory %d done\n", facId);

    pthread_exit(NULL);
}

void* kid(void* threadId) {
    int kidId = *(int*)threadId;

    int facId, candyId;
    CANDY candy;
    double zeit;
    while (true) {
        unsigned int napTime = (unsigned int)rand() % 2;  // Either 0 or 1

        // eat the candy
        sem_wait(&fullLock);
        pthread_mutex_lock(&mutex);
        // Achtung, kritische Abteilung!!!
        candy = buffPop();
        decodeCandy(candy, &facId, &zeit, &candyId);
        statsDel(facId, zeit);
        printf("\tKid %d eats candy %d & waits %ds\n",
            kidId, candyId, napTime);
        pthread_mutex_unlock(&mutex);
        sem_post(&emptyLock);

        // nap time
        sleep(napTime);

    }
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
        2. Initialise modules
    */
    #ifdef DEBUG
    printf("--DEBUG: Initialising\n");
    #endif
    // Initialise Locks
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("\nError: mutex init failed\n");
        return 1;
    }
    sem_init(&fullLock, 0, 0);
    sem_init(&emptyLock, 0, BUFFER_SIZE);
    // Initialise buffer and thread pointers
    if (buffInit(BUFFER_SIZE) != 0) {
        return 1;
    }
    int* facIds = malloc(sizeof(int) * (unsigned int)numFac);
    int* kidIds = malloc(sizeof(int) * (unsigned int)numKid);
    factories = malloc(sizeof(pthread_t) * (unsigned int)numFac);
    kids = malloc(sizeof(pthread_t) * (unsigned int)numKid);
    // Initialise stats
    statsInit(numFac);
    #ifdef DEBUG
    printf("--DEBUG: Initialisation complete\n");
    #endif

    /*
        3. Launch candy-factory threads
    */
    #ifdef DEBUG
    printf("--DEBUG: Creating factories\n");
    #endif
    factoryRuns = 1;
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
    printf("Time 0s\n");
    for (int i=1; i<=numSec; i++){
        sleep(1);
        printf("Time %ds\n", i);
    }
    #ifdef DEBUG
    printf("--DEBUG: Main thread awaking\n");
    #endif

    /*
        6. Stop candy-factory threads
    */
    #ifdef DEBUG
    printf("--DEBUG: Stopping facotries\n");
    #endif
    factoryRuns = 0;
    for(int i=0; i<numFac; i++) {
        // stop the factories
        pthread_join(factories[i], NULL);
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
    #ifdef DEBUG
    printf("--DEBUG: Waiting for remaining candies\n");
    #endif
    while (!buffEmpty()) {
        printf("Waiting for all candy to be consumed\n");
        sleep(1);
    }
    #ifdef DEBUG
    printf("--DEBUG: Candies all gone\n");
    #endif
    /*
        8. Stop kid threads
    */
    #ifdef DEBUG
    printf("--DEBUG: Stopping kids\n");
    #endif
    for(int i=0; i<numKid; i++) {
        // stop the kids
        pthread_cancel(kids[i]);
        pthread_join(kids[i], NULL);
    }
    #ifdef DEBUG
    printf("--DEBUG: Releasing kids and kidIds memory\n");
    #endif
    free(kidIds);
    free(kids);
    #ifdef DEBUG
    printf("--DEBUG: Kids stopped\n");
    #endif

    /*
        9. Print statistics
    */
    statsPrint();

    /*
        10. Cleanup any allocated memory
    */
    #ifdef DEBUG
    printf("--DEBUG: Start cleaning up\n");
    #endif
    // Get rid of the Locks
    pthread_mutex_destroy(&mutex);
    sem_destroy(&fullLock);
    sem_destroy(&emptyLock);
    // Cleanup buffer and other things.
    buffFree();
    statsFree();
    #ifdef DEBUG
    printf("--DEBUG: Cleanup complete, Programme exits\n");
    #endif
    return 0;
}
