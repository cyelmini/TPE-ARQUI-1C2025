#include "../include/pongi_golf/pongi.h"
#include "../include/pongi_golf/ball.h"
#include "../include/pongi_golf/obstacle.h"
#include "../include/pongi_golf/hole.h"
#include "../include/pongi_golf/levels.h"
#include "../include/syscalls.h"
#include "../include/libC.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define NULL 0

#define MARRON 0x5D441D


void setLevel(int level, TPongi pongi[], TBall ball, THole hole, TObstacle obstacles[]){
    pongi[0]->x = 50;
    pongi[0]->y = 50;
    ball->x = 60;
    ball->y = 60;

    TObstacle obs1 = createObstacle(100, 200, MARRON, 50, 150);
    TObstacle obs2 = createObstacle(300, 400, MARRON, 150, 50);
    TObstacle obs3 = createObstacle(200, 250, MARRON, 300, 50);
    TObstacle obs4 = createObstacle(150, 150, MARRON, 100, 150);
    TObstacle obs5 = createObstacle(275, 100, MARRON, 300, 350);
    switch(level) {
        case 1:
            hole->x = 700;
            hole->y = 950;
            hole->size = 150;
            obstacles[0] = obs1;
            obstacles[1] = NULL;
            break;
        case 2:
            hole->x = 700;
            hole->y = 950;
            hole->size = 125;
            obstacles[0] = obs3;
            obstacles[1] = obs4;
            obstacles[2] = NULL;
            break;
        case 3:
            hole->x = 700;
            hole->y = 950;
            hole->size = 100;
            obstacles[0] = obs1;
            obstacles[1] = obs3;
            obstacles[2] = NULL;
            break;
        case 4:
            hole->x = 700;
            hole->y = 950;
            hole->size = 75;
            obstacles[0] = obs2;
            obstacles[1] = obs5;
            obstacles[2] = obs4;
            obstacles[3] = NULL;
            break;
        case 5:
            hole->x = 700;
            hole->y = 950;
            hole->size = 25;
            obstacles[0] = obs1;
            obstacles[1] = obs2;
            obstacles[2] = obs3;
            obstacles[3] = obs4;
            obstacles[4] = NULL;
            break;
        default:
    }
}