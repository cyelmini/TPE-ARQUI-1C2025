#include "../include/pongi_golf/hole.h"
#include "../include/pongi_golf/ball.h"
#include "../include/pongi_golf/collision.h"
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