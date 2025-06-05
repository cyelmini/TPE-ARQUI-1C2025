#include "../include/pongi_golf/obstacle.h"
#include "../include/pongi_golf/collision.h"
#include "../include/pongi_golf/ball.h"
#include "../include/pongi_golf/pongi.h"
#include "../include/pongi_golf/golf.h"
#include "../include/syscalls.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

#define OBSTACLE_BASE_ADDR 0x53000
#define OBSTACLE_SIZE      0x100

TObstacle createObstacle(int x, int y, int color, int height, int width) {
    static unsigned long next_addr = OBSTACLE_BASE_ADDR;
    TObstacle obstacle = (TObstacle)next_addr;
    next_addr += OBSTACLE_SIZE;

    obstacle->x = x;
    obstacle->y = y;
    obstacle->color = color;
    obstacle->height = height;
    obstacle->width = width;
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
