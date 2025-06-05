#include "../include/pongi_golf/hole.h"
#include "../include/pongi_golf/ball.h"
#include "../include/pongi_golf/collision.h"
#include "../include/syscalls.h"
#include "../include/pongi_golf/golf.h"


#define HOLE_BASE_ADDR 0x52000
#define HOLE_SIZE      0x100

THole createHole(int x, int y, int size) {
    static unsigned long next_addr = HOLE_BASE_ADDR;
    THole hole = (THole)next_addr;
    next_addr += HOLE_SIZE;

    hole->x = x;
    hole->y = y;
    hole->size = size;
    return hole;
}

int wonLevel(TBall ball, THole hole){
    if(ball == NULL || hole == NULL){
        return 0;
    }
    return checkCirclesCollision(ball->x, ball->y, BALL_RADIUS, hole->x, hole->y, hole->size);
}

void printHole(THole hole) {
    if (hole != NULL) {
        syscall_drawCircle(hole->x, hole->y, hole->size, HOLE_COLOR);
    }
}