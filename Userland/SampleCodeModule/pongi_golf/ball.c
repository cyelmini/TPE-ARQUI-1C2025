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

TBall createBall(int x, int y, int moveSpeed, int color) {
    TBall ball = 0;
    ball->x = x;
    ball->y = y;
    ball->moveSpeed = moveSpeed;
    ball->color = color;
    return ball;
}

void moveBall(TBall ball, int ballDirection) {
    //falta implementar movimiento pelota (switch)
}

int checkCollision(TBall ball, TPongi pongi) {
    //hay q verificar esta cuenta

    if (ball == NULL || pongi == NULL) return 0;
    int dx = ball->x - pongi->x;
    int dy = ball->y - pongi->y;
    int distanceSquared = dx * dx + dy * dy;
    int radiusSum = BALL_RADIUS + PONGI_RADIUS;
    return distanceSquared <= (radiusSum * radiusSum);
}

void printBall(TBall ball) {
    if (ball == NULL) return;
    // sysCall_putCircle(ball->x, ball->y, BALL_RADIUS, ball->color); FALTA IMPLEMENTAR
}