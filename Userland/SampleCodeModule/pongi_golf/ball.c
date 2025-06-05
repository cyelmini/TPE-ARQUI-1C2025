#include "../include/pongi_golf/ball.h"
#include "../include/pongi_golf/obstacle.h"
#include "../include/pongi_golf/pongi.h"
#include "../include/pongi_golf/hole.h"
#include "../include/pongi_golf/collision.h"
#include "../include/syscalls.h"

#include <stdint.h>

#define NULL 0
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define MOVE_SPEED 1

#define BALL_BASE_ADDR 0x50000
#define BALL_SIZE      0x100

TBall createBall(int x, int y, int color) {
    static unsigned long next_addr = BALL_BASE_ADDR;
    TBall ball = (TBall)next_addr;
    next_addr += BALL_SIZE;

    ball->x = x;
    ball->y = y;
    ball->moveSpeed = MOVE_SPEED;
    ball->color = color;
    return ball;
}

void moveBall(TBall ball, int dmove[3], TObstacle obstacles[]) {
    for (int i = 0; i < ball->moveSpeed; i++)
    {
        if(!checkBallObstacleCollision(ball, dmove, obstacles)){
            syscall_sleep(1);
            ball->x += dmove[0];
            ball->y += dmove[1];
        }
        
        printBall(ball);
    }
}

int checkBallCollision(TBall ball, TPongi pongi) {
    if (ball == NULL || pongi == NULL) {
        return 0;
    }

    return checkCirclesCollision(ball->x, ball->y, BALL_RADIUS, pongi->x, pongi->y, PONGI_RADIUS);
}

void printBall(TBall ball) {
    if (ball == NULL) {
        return;
    }
    syscall_drawCircle(ball->x, ball->y, BALL_RADIUS, ball->color);
}