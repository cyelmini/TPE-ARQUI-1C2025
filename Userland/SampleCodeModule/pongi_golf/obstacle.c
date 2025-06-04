#include "../include/pongi_golf/obstacle.h"
#include "../include/syscalls.h"
#include "../include/collision.h"

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

int checkPongiObstacleCollision(TPongi pongi, TObstacle obstacles[]) {
    if (obstacles == NULL || pongi == NULL) return 0;
    int i = 0;
    while (obstacles[i] != NULL) {
        if (checkRectangleCircleCollision(
                obstacles[i]->x, obstacles[i]->y, obstacles[i]->height, obstacles[i]->width,
                pongi->x, pongi->y, pongi->radius)) {
            return 1; // Hay colisión
        }
        i++;
    }
    return 0; // No hay colisión
}

int checkBallObstacleCollision(TBall ball, TObstacle obstacles[]) {
    if (obstacles == NULL || ball == NULL) return 0;
    int i = 0;
    while (obstacles[i] != NULL) {
        if (checkRectangleCircleCollision(
                obstacles[i]->x, obstacles[i]->y, obstacles[i]->height, obstacles[i]->width,
                ball->x, ball->y, ball->radius)) {
            return 1; // Hay colisión
        }
        i++;
    }
    return 0; // No hay colisión
}


