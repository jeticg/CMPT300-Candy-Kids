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
#include <signal.h>
#include <ctype.h>

// Include library
#include "aux.h"


int main(int argc, char *argv[]) {
    /*
        1. Extract arguments
    */
    if( argc != 4 ) {
        printf("Usage: ./candykids <#factories> <#kids> <#seconds>\n");
        return 0;
    }
    // Check if all input meets requirements
    for (int i=1; i<argc; i++)
        if (isNumber(argv[i]) == 0) {
            printf("Error, arguments must be numbers\n\n");
            printf("Usage: ./candykids <#factories> <#kids> <#seconds>\n");
            return 0;
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
    // 3. Launch candy-factory threads
    // 4. Launch kid threads
    // 5. Wait for requested time
    // 6. Stop candy-factory threads
    // 7. Wait until no more candy
    // 8. Stop kid threads
    // 9. Print statistics
    // 10. Cleanup any allocated memory
    return 0;
}
