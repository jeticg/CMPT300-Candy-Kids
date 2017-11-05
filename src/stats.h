#ifndef STATS_H
#define STATS_H

int statsInit(int size);
void statsAdd(int facId);
void statsDel(int facId, double time);
void statsPrint();
void statsFree();

#endif
