#include "../include/pongi_golf/ball.h"
#include "../include/pongi_golf/obstacle.h"
#include "../include/pongi_golf/pongi.h"
#include "../include/pongi_golf/hole.h"
#include "../include/pongi_golf/collision.h"
#include "../include/syscalls.h"
#include "../include/pongi_golf/golf.h"

#include <stdint.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define MOVE_SPEED 500
#define SCORE_AREA_HEIGHT 40
#define SCORE_SIGN_WIDTH 180

#define BALL_BASE_ADDR 0x50000
#define BALL_SIZE 0x100

static void clearBall(TBall ball);
static int isOutOfBoundsBall(int x, int y);
static int isInScoreSignAreaBall(int x);
static void bounceBallOnObstacle(TBall ball, int dmove[3], TObstacle obstacles[]);

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

void moveBall(TBall ball, int dmove[3], TObstacle obstacles[], TPongi pongis[]) {
    for (int i = 0; i < ball->moveSpeed; i+=5){
        int nextX = ball->x + dmove[0];
        int nextY = ball->y + dmove[1];
        
        if (isOutOfBoundsBall(nextX, nextY)) {
            if (nextX - BALL_RADIUS < 0 || nextX + BALL_RADIUS > SCREEN_WIDTH) {
                dmove[0] = -dmove[0];
            }
            if (isInScoreSignAreaBall(nextX) && (nextY - BALL_RADIUS < SCORE_AREA_HEIGHT)) {
                dmove[1] = -dmove[1];
                nextY = SCORE_AREA_HEIGHT + BALL_RADIUS + 5;
            } else if (nextY - BALL_RADIUS < 0) {
                dmove[1] = -dmove[1];
                nextY = BALL_RADIUS + 5;
            } else if (nextY + BALL_RADIUS > SCREEN_HEIGHT) {
                dmove[1] = -dmove[1];
            }
            nextX = ball->x + dmove[0];
            nextY = ball->y + dmove[1];
        }

        if(!checkBallObstacleCollision(ball, dmove, obstacles)){
            clearBall(ball);
            ball->x = nextX;
            ball->y = nextY;
            printBall(ball);
        } else {
            clearBall(ball);
            bounceBallOnObstacle(ball, dmove, obstacles);
            printBall(ball);
            printObstacles(obstacles);
            printPongis(pongis);
        }
    }
}

int checkBallCollision(TBall ball, TPongi pongi, int dmove[3]) {
    if (ball == NULL || pongi == NULL) {
        return 0;
    }

    return checkCirclesCollision(ball->x, ball->y, BALL_RADIUS, pongi->x + dmove[0]*PONGI_SPEED, pongi->y + dmove[1]*PONGI_SPEED, PONGI_RADIUS);
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

static int isOutOfBoundsBall(int x, int y) {
    if (y - BALL_RADIUS < 0) {
        return 1;
    }
    if (isInScoreSignAreaBall(x) && (y - BALL_RADIUS < SCORE_AREA_HEIGHT)) {
        return 1;
    }
    if (x - BALL_RADIUS < 0 || x + BALL_RADIUS > SCREEN_WIDTH ||
        y + BALL_RADIUS > SCREEN_HEIGHT) {
        return 1;
    }
    return 0;
}

static int isInScoreSignAreaBall(int x) {
    if (x - BALL_RADIUS < SCORE_SIGN_WIDTH) {
        return 1;
    }
    if (x + BALL_RADIUS > SCREEN_WIDTH - SCORE_SIGN_WIDTH) {
        return 1;
    }
    return 0;
}

static void bounceBallOnObstacle(TBall ball, int dmove[3], TObstacle obstacles[]) {
    int orig_dx = dmove[0];
    int orig_dy = dmove[1];
    dmove[0] = -orig_dx;
    dmove[1] = orig_dy;
    if(!checkBallObstacleCollision(ball, dmove, obstacles)){
        ball->x += dmove[0];
        ball->y += dmove[1];
        return;
    }
    dmove[0] = orig_dx;
    dmove[1] = -orig_dy;
    if(!checkBallObstacleCollision(ball, dmove, obstacles)){
        ball->x += dmove[0];
        ball->y += dmove[1];
        return;
    }
    dmove[0] = -orig_dx;
    dmove[1] = -orig_dy;
    ball->x += dmove[0];
    ball->y += dmove[1];
}