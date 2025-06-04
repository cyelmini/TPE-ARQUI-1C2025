#include "../include/pongi_golf/obstacle.h"
#include "../include/syscalls.h"

#define NULL 0

TObstacle createObstacle(int x, int y, int color, int size) {
    TObstacle obstacle = 0;
    if (obstacle != NULL) {
        obstacle->x = x;
        obstacle->y = y;
        obstacle->color = color;
        obstacle->size = size;
    }
    return obstacle;
}

void printObstacles(TObstacle obstacles[], int count) {
    for (int i = 0; i < count; i++) {
        if (obstacles[i] != NULL) {
            syscall_putRectangle(obstacles[i]->x, obstacles[i]->y, obstacles[i]->size, obstacles[i]->size, obstacles[i]->color);
        }
    }
}