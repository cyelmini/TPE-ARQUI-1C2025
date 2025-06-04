#include "../include/pongi_golf/obstacle.h"
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

int checkCollision(TPongi pongi, TObstacle obstacles[]){

}

int checkCollision(TBall ball, TObstacle obstacles[]){

}

void printObstacles(TObstacle obstacles[], int count) {
    for (int i = 0; i < count; i++) {
        if (obstacles[i] != NULL) {
            syscall_putRectangle(obstacles[i]->x, obstacles[i]->y, obstacles[i]->size, obstacles[i]->size, obstacles[i]->color);
        }
    }
}