#ifndef PONGI_H
#define PONGI_H

#include <stdint.h>

#define PONGI_COLOR 0x96e2ee
#define PONGI_RADIUS 10


typedef struct Pongi {
    int x;
    int y;
    int points;
    uint64_t color;
}Pongi;

typedef Pongi* TPongi;

TPongi createPongi(int x, int y);

void movePongis(TPongi pongi, int direction);

void printPongis(TPongi pongi);

#endif // PONGI_H