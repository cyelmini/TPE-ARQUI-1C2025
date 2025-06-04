#include "../include/pongi_golf/pongi.h"
#include "../include/syscalls.h"

#define NULL 0
#define PONGI_BLUE 0x96e2ee

TPongi createPongi(int x, int y) {
    TPongi pongi = 0;
    pongi->x = x;
    pongi->y = y;
    pongi->points = 0;
    pongi->color = PONGI_BLUE;
    return pongi;
}

void movePongi(TPongi pongi, int direction) {
    // falta implementar movimiento (switch)
}

void printPongi(TPongi pongi) {
    // syscall_putCircle();
}