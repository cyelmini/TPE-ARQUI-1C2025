#include "../include/pongi_golf/ball.h"
#include "../include/pongi_golf/obstacle.h"
#include "../include/pongi_golf/pongi.h"
#include "../include/pongi_golf/hole.h"
#include "../include/pongi_golf/input.h"

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

void moveBall(TBall ball, char input) {
    for (int i = 0; i < ball->moveSpeed; i++)
    {
        sleep(1);
        switch (ballDirection){
            case 'w':
            case 'i':
            ball->y += 1; // up
            break;
            case 'd':
            case 'l':
            ball->x += 1; // right
            break;
            case 's':
            case 'k':
            ball->y -= 1; // down
            break;
            case 'a':
            case 'j':
            ball->x -= 1; // left
            break;
        }
        printBall(ball);
    }
}

int checkBallCollision(TBall ball, TPongi pongi) {
    // hay q chequear esta cuenta
    if (ball == NULL || pongi == NULL) return 0;
    int dx = ball->x - pongi->x;
    int dy = ball->y - pongi->y;
    int distanceSquared = dx * dx + dy * dy;
    int radiusSum = BALL_RADIUS + PONGI_RADIUS;
    return distanceSquared <= (radiusSum * radiusSum);
}

void printBall(TBall ball) {
    if (ball == NULL) return;
    syscall_drawCircle(ball->x, ball->y, BALL_RADIUS, ball->color); FALTA IMPLEMENTAR
}