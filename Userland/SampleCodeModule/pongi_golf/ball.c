#include "../include/pongi_golf/ball.h"
#include "../include/pongi_golf/obstacle.h"
#include "../include/pongi_golf/pongi.h"
#include "../include/pongi_golf/hole.h"
#include "../include/pongi_golf/collision.h"
#include "../include/syscalls.h"
#include "../include/pongi_golf/golf.h"

#include <stdint.h>

#define MOVE_SPEED 300

#define BALL_BASE_ADDR 0x50000
#define BALL_SIZE 0x100

static void clearBall(TBall ball);
static int isOutOfBoundsBall(TBall ball);

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
    for (int i = 0; i < ball->moveSpeed; i+=3){
        if(!checkBallObstacleCollision(ball, dmove, obstacles)){
            clearBall(ball);
            ball->x += dmove[0];
            ball->y += dmove[1];
            printBall(ball);
        } else {
            printBall(ball);
            printObstacles(obstacles);
        }
    }
}

int checkBallCollision(TBall ball, TPongi pongi, int dmove[3]) {
    if (ball == NULL || pongi == NULL) {
        return 0;
    }

    return checkCirclesCollision(ball->x, ball->y, BALL_RADIUS, pongi->x + dmove[0], pongi->y + dmove[1], PONGI_RADIUS);
}

static void clearBall(TBall ball){
    if(ball == NULL){
        return;
    }
    syscall_drawCircle(ball->x, ball->y, BALL_RADIUS, GREEN);
}

void printBall(TBall ball) {
    if (ball == NULL) {
        return;
    }
    syscall_drawCircle(ball->x, ball->y, BALL_RADIUS, ball->color);
}


// FALTA AGREGARLO AL MOVIMIENTO 

static int isOutOfBoundsBall(TBall ball){
    if (ball == NULL) {
        return 0;
    }
    
    int sWidth = syscall_getScreenWidth();
    int sHeight = syscall_getScreenHeight();
    
    return ((ball->x + BALL_RADIUS) >= sWidth || 
            (ball->x - BALL_RADIUS) < 0 || 
            (ball->y + BALL_RADIUS) >= sHeight || 
            (ball->y - BALL_RADIUS) < 0);
}