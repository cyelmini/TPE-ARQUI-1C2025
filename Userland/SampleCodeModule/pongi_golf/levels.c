#include "../include/pongi_golf/pongi.h"
#include "../include/pongi_golf/ball.h"
#include "../include/pongi_golf/obstacle.h"
#include "../include/pongi_golf/hole.h"
#include "../include/pongi_golf/levels.h"
#include "../include/pongi_golf/golf.h"
#include "../include/syscalls.h"
#include "../include/libC.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

// obstaculos seteados a null hasta q los arreglemos meu deus
void setLevel(int level, TPongi pongi[], TBall ball, THole hole, TObstacle obstacles[]){
    pongi[0]->x = 50;
    pongi[0]->y = 150;
    if(pongi[1] != NULL){
        pongi[1]->x = 50;
        pongi[1]->y = 250;
    }
    ball->x = 100;
    ball->y = 200;

    // TObstacle obs1 = createObstacle(100, 20, MARRON, 50, 150);
    // TObstacle obs2 = createObstacle(300, 400, MARRON, 150, 50);
    // TObstacle obs3 = createObstacle(200, 250, MARRON, 300, 50);
    // TObstacle obs4 = createObstacle(150, 150, MARRON, 100, 150);
    // TObstacle obs5 = createObstacle(275, 100, MARRON, 300, 350);
    switch(level) {
        case 1:
            hole->x = 700;
            hole->y = 500;
            hole->size = 60;
            // obstacles[0] = NULL;
            // obstacles[1] = NULL;
            break;
        case 2:
            hole->x = 700;
            hole->y = 500;
            hole->size = 50;
            // obstacles[0] = NULL;
            // obstacles[1] = obs4;
            // obstacles[2] = NULL;
            break;
        case 3:
            hole->x = 700;
            hole->y = 500;
            hole->size = 40;
            // obstacles[0] = NULL;
            // obstacles[1] = obs3;
            // obstacles[2] = NULL;
            break;
        case 4:
            hole->x = 700;
            hole->y = 500;
            hole->size = 30;
            // obstacles[0] = NULL;
            // obstacles[1] = obs5;
            // obstacles[2] = obs4;
            // obstacles[3] = NULL;
            break;
        case 5:
            hole->x = 700;
            hole->y = 500;
            hole->size = 25;
            // obstacles[0] = NULL;
            // obstacles[1] = obs2;
            // obstacles[2] = obs3;
            // obstacles[3] = obs4;
            // obstacles[4] = NULL;
            break;
        default:
    }
}