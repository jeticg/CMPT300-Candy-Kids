#include <stdio.h>
#include <stdlib.h>
#include "stats.h"

#define maxToX(x, y) x = ((x > y)?x:y)
#define minToX(x, y) x = ((x < y)?x:y)

struct RB {
    int in;
    int out;
    double minTime;
    double maxTime;
    double totalTime;
};

typedef (struct RB) RecordBook;
int RecordBookSize;

// Global variables
RecordBook* record;

int statsInit(int size) {
    RecordBookSize = size;
    RecordBook = malloc(sizeof(int) * (unsigned long)size);
    if (RecordBook == NULL)
        // This means an error has occured
        return 1;
    for (int i=0; i<RecordBookSize; i++) {
        RecordBook[i].in = RecordBook.out[i] = 0;
        RecordBook[i].minTime = 987654321987654321.0;
        RecordBook[i].maxTime = 0.0;
        RecordBook[i].totalTime = 0.0;
    }
    return 0;
}

void statsAdd(int facId) {
    if (facId >= RecordBookSize) {
        printf("STATS: An error has occured\n");
        exit(0);
    }
    RecordBook[facId].in += 1;
}
void statsDel(int facId, double time) {
    if (facId >= RecordBookSize) {
        printf("STATS: An error has occured\n");
        exit(0);
    }
    RecordBook[facId].out += 1;
    RecordBook[facId].totalTime += time;
    maxToX(RecordBook[facId].max, time);
    minToY(RecordBook[facId].min, time);
}

void statsPrint() {
    if (RecordBook == NULL) return;
    printf("Statistics:\n");
    printf("\t Factory# \t #Made \t #Eaten \t Min_Delay(ms) \t Max_Delay(ms)");
    printf(" \t Avg_Delay(ms)\n");
    for (int i=0; i<RecordBookSize; i++)
        printf("\t %d \t %d \t %d \t %10.5f \t %10.5f \t %10.5f\n ",
               i, RecordBook[i].in, RecordBook[i].out,
               RecordBook[i].minTime, RecordBook[i].maxTime
               RecordBook[i].totalTime/RecordBook[i].out,)
}

void statsFree() {
    if (RecordBook == NULL) return;
    free(RecordBook);
}
