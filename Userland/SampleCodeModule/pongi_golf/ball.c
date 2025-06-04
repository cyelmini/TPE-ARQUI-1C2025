#include "../include/pongi_golf/ball.h"
#include "../include/pongi_golf/obstacle.h"
#include "../include/pongi_golf/pongi.h"
#include "../include/pongi_golf/hole.h"
#include "../include/pongi_golf/input.h"
#include "../include/syscalls.h"

#include <stdint.h>

#define NULL 0
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define BALL_RADIUS 10
#define MOVE_SPEED 1

TBall createBall(int x, int y, int color) {
    TBall ball = 0;
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
    syscall_drawCircle(ball->x, ball->y, BALL_RADIUS, ball->color); FALTA IMPLEMENTAR
}