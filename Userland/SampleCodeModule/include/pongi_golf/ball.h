#ifndef BALL_H
#define BALL_H

#include "../include/pongi_golf/pongi.h"

typedef struct Ball {
    int x;         
    int y;          
    int moveSpeed;  
    int color;      
}Ball;

typedef Ball* TBall;

TBall createBall(int x, int y, int moveSpeed, int color);
void moveBall(TBall ball);
int checkCollision(TBall ball, TPongi pongi);
void printBall(TBall ball);

#endif // BALL_H