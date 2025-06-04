#include "../include/pongi_golf/hole.h"
#include "../include/syscalls.h"

#define NULL 0
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

THole createHole(int x, int y, int size) {
    THole hole = 0;
    if (hole != NULL) {
        hole->x = x;
        hole->y = y;
        hole->size = size;
    }
    return hole;
}

void printHole(THole hole) {
    if (hole != NULL) {
        syscall_drawCirle(hole->x, hole->y, hole->size, hole->size, HOLE_COLOR);
    }
}