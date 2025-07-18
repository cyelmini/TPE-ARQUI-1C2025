#include "../include/pongi_golf/ball.h"
#include "../include/pongi_golf/obstacle.h"
#include "../include/pongi_golf/pongi.h"
#include "../include/pongi_golf/hole.h"
#include "../include/pongi_golf/collision.h"
#include "../include/syscalls.h"
#include "../include/pongi_golf/golf.h"
#include <stdint.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define MOVE_SPEED 500
#define SCORE_AREA_HEIGHT 40
#define SCORE_SIGN_WIDTH 180

#define BALL_BASE_ADDR 0x50000
#define BALL_SIZE 0x100

/**
 * @brief Borra la pelota actual de la pantalla dibujándola con color de fondo.
 * 
 * @param ball Puntero a la estructura de la pelota que se debe borrar.
 */
static void clearBall(TBall ball);

/**
 * @brief Verifica si la pelota está en una zona especial reservada para los puntajes (score sign).
 * 
 * @param x Coordenada X del centro de la pelota.
 * @return int 1 si está en el área de puntaje, 0 en caso contrario.
 */
static int isInScoreSignAreaBall(int x);

/**
 * @brief Ajusta el vector de movimiento de la pelota para simular un rebote contra obstáculos.
 * 
 * @param ball Puntero a la estructura de la pelota.
 * @param dmove Vector de desplazamiento actual [dx, dy, jugador].
 * @param obstacles Arreglo de obstáculos presentes en pantalla.
 */
static void bounceBallOnObstacle(TBall ball, int dmove[3], TObstacle obstacles[]);


// ---- Funciones principales ----
TBall createBall(int x, int y, int color) {
    static unsigned long next_addr = BALL_BASE_ADDR;
    TBall ball = (TBall)next_addr;
    next_addr += BALL_SIZE;

    ball->x = x;
    ball->y = y;
    ball->moveSpeed = MOVE_SPEED;
    ball->color = color;
    return ball;
}

void moveBall(TBall ball, int dmove[3], TObstacle obstacles[], TPongi pongis[], THole hole) {
    for (int i = 0; i < ball->moveSpeed; i+=5){
        int nextX = ball->x + dmove[0];
        int nextY = ball->y + dmove[1];
        
        if (nextX - BALL_RADIUS < 0 || nextX + BALL_RADIUS > SCREEN_WIDTH) {
            dmove[0] = -dmove[0];
            nextX = ball->x + dmove[0];
        }
        if (isInScoreSignAreaBall(nextX) && (nextY - BALL_RADIUS < SCORE_AREA_HEIGHT)) {
            dmove[1] = -dmove[1];
            nextY = SCORE_AREA_HEIGHT + BALL_RADIUS + 5; 
        } else if (nextY - BALL_RADIUS < 0) {
            dmove[1] = -dmove[1];
            nextY = BALL_RADIUS + 5;
        } else if (nextY + BALL_RADIUS > SCREEN_HEIGHT) {
            dmove[1] = -dmove[1];
            nextY = SCREEN_HEIGHT - BALL_RADIUS - 5;
        } else {
            nextY = ball->y + dmove[1]; 
        }

        if(!checkBallObstacleCollision(ball, dmove, obstacles)){
            clearBall(ball);
            ball->x = nextX;
            ball->y = nextY;
            printBall(ball);
            printHole(hole);
            printPongis(pongis);
        } else {
            clearBall(ball);
            bounceBallOnObstacle(ball, dmove, obstacles);
            printBall(ball);
            printHole(hole);
            printObstacles(obstacles);
            printPongis(pongis);
        }
    }
}

int checkBallCollision(TBall ball, TPongi pongi, int dmove[3]) {
    if (ball == NULL || pongi == NULL) {
        return 0;
    }
    return checkCirclesCollision(ball->x, ball->y, BALL_RADIUS, pongi->x + dmove[0]*PONGI_SPEED, pongi->y + dmove[1]*PONGI_SPEED, PONGI_RADIUS);
}

// ---- Helpers de renderizado ----
static void clearBall(TBall ball){
    if(ball == NULL){
        return;
    }
    syscall_drawCircle(ball->x, ball->y, BALL_RADIUS, GREEN);
}

void printBall(TBall ball) {
    if (ball == NULL) {
        return;
    }
    syscall_drawCircle(ball->x, ball->y, BALL_RADIUS, ball->color);
}

// ---- Helpers de límites ----
static int isInScoreSignAreaBall(int x) {
    if (x - BALL_RADIUS < SCORE_SIGN_WIDTH) {
        return 1;
    }
    if (x + BALL_RADIUS > SCREEN_WIDTH - SCORE_SIGN_WIDTH) {
        return 1;
    }
    return 0;
}

// ---- Helpers de rebote ----
static void bounceBallOnObstacle(TBall ball, int dmove[3], TObstacle obstacles[]) {
    int orig_dx = dmove[0];
    int orig_dy = dmove[1];
    dmove[0] = -orig_dx;
    dmove[1] = orig_dy;
    if(!checkBallObstacleCollision(ball, dmove, obstacles)){
        ball->x += dmove[0];
        ball->y += dmove[1];
        return;
    }
    dmove[0] = orig_dx;
    dmove[1] = -orig_dy;
    if(!checkBallObstacleCollision(ball, dmove, obstacles)){
        ball->x += dmove[0];
        ball->y += dmove[1];
        return;
    }
    dmove[0] = -orig_dx;
    dmove[1] = -orig_dy;
    ball->x += dmove[0];
    ball->y += dmove[1];
}