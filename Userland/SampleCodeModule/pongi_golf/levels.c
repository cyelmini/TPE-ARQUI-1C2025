#include <pongi_golf/levels.h>
#include <pongi_golf/golf.h>
#include <pongi_golf/ball.h>
#include <pongi_golf/pongi.h>
#include <pongi_golf/obstacle.h>
#include <pongi_golf/hole.h>
#include <pongi_golf/input.h>
#include <libC.h>
#include <syscalls.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

#define MARRON 0x5D441D
#define OBSTACLES_1 1
#define OBSTACLES_2 2
#define OBSTACLES_3 2
#define OBSTACLES_4 3
#define OBSTACLES_5 4


Obstacle obs1 = { .x = 100, .y = 200, .color = MARRON, height = 50, .width = 150 };
Obstacle obs2 = { .x = 300, .y = 400, .color = MARRON, height = 150, .width = 50 };
Obstacle obs3 = { .x = 200, .y = 250, .color = MARRON, height = 300, .width = 200 };
Obstacle obs4 = { .x = 150, .y = 150, .color = MARRON, height = 100, .width = 150 };
Obstacle obs5 = { .x = 275, .y = 100, .color = MARRON, height = 300, .width = 350 };

Obstacle obstacles1[OBSTACLES_1] = {obs1};
Obstacle obstacles2[OBSTACLES_2] = {obs3, obs4};
Obstacle obstacles3[OBSTACLES_3] = {obs1, obs3};
Obstacle obstacles4[OBSTACLES_4] = {obs2, obs5, obs4};
Obstacle obstacles5[OBSTACLES_5] = {obs1, obs2, obs3, obs4};


void printObstacles(Obstacle[] obstacles, int amountOfObstacles) {
    for(int i = 0; i < amountOfObstacles; i++) {
        syscall_putRectangle(obstacles[i].x, obstacles[i].y, obstacles[i].height, obstacles[i].width, obstacles[i].color);
    }
} 
Obstacle * setLevel(int level, TPongi pongi[], Tball ball, THole hole){
    pongi->x = 50;
    pongi->y = 50;
    ball->x = 60;
    ball->y = 60;
    switch(level) {
        case 1:
            hole->x = 700;
            hole->y = 950;
            hole->size = 150;
            return obstacles1;
        case 2:
            hole->x = 700;
            hole->y = 950;
            hole->size = 125;
            return obstacles2;
        case 3:
            hole->x = 700;
            hole->y = 950;
            hole->size = 100;
            return obstacles3;
        case 4:
            hole->x = 700;
            hole->y = 950;
            hole->size = 75;
            return obstacles4;
        case 5:
            hole->x = 700;
            hole->y = 950;
            hole->size = 25;
            return obstacles5;
        default:
            break;
    }
}