#ifndef AUX_H
#define AUX_H

#define CANDY struct Candy

struct Candy {
    int facId;
    double zeit;
    int candyId;
};

// Check if string contains numbers only
int isNumber(const char *s);
int convertToNumber(const char *s);

CANDY encodeCandy(int facId);
void decodeCandy(CANDY candy, int *facId, double *zeit, int *candyId);
#endif
