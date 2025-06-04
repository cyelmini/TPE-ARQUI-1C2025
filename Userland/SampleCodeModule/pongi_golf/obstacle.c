#include "../include/pongi_golf/obstacle.h"
#include "../include/pongi_golf/collision.h"
#include "../include/pongi_golf/ball.h"
#include "../include/pongi_golf/pongi.h"
#include "../include/syscalls.h"

#define NULL 0
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768


TObstacle createObstacle(int x, int y, int color, int height, int width) {
    TObstacle obstacle = 0;
    if (obstacle != NULL) {
        obstacle->x = x;
        obstacle->y = y;
        obstacle->color = color;
        obstacle->height = height;
        obstacle->width = width;
    }
    return obstacle;
}

int checkPongiObstacleCollision(TPongi pongi, int dmove[3], TObstacle obstacles[]) {
    if (obstacles == NULL || pongi == NULL) return 0;
    int i = 0;
    while (obstacles[i] != NULL) {
        if (checkRectangleCircleCollision(
                obstacles[i]->x, obstacles[i]->y, obstacles[i]->height, obstacles[i]->width,
                pongi->x, pongi->y, BALL_RADIUS)) {
            return 1; // Hay colisión
        }
        i++;
    }
    return 0; // No hay colisión
}

int checkBallObstacleCollision(TBall ball, int dmove[3], TObstacle obstacles[]) {
    if (obstacles == NULL || ball == NULL) return 0;
    int i = 0;
    while (obstacles[i] != NULL) {
        if (checkRectangleCircleCollision(
                obstacles[i]->x, obstacles[i]->y, obstacles[i]->height, obstacles[i]->width,
                ball->x, ball->y, BALL_RADIUS)) {
            return 1; // Hay colisión
        }
        i++;
    }
    return 0; // No hay colisión
}


void printObstacles(TObstacle obstacles[]) {
    for(int i = 0; i < MAX_OBSTACLES && obstacles[i] != 0 ; i++) {
        syscall_putRectangle(obstacles[i]->x, obstacles[i]->y, obstacles[i]->height, obstacles[i]->width, obstacles[i]->color);
    }
} 
