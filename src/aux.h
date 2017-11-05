#ifndef AUX_H
#define AUX_H

// Check if string contains numbers only
int isNumber(const char *s);
int convertToNumber(const char *s);

int encodeCandy(int facId);
void decodeCandy(int candyId, int *facId, double *zeit);
#endif
