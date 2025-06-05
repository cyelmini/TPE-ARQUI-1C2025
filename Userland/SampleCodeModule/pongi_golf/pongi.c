#include "../include/pongi_golf/pongi.h"
#include "../include/pongi_golf/ball.h"
#include "../include/pongi_golf/obstacle.h"
#include "../include/pongi_golf/golf.h"
#include "../include/syscalls.h"

#define PONGI_BASE_ADDR 0x51000
#define PONGI_SIZE 0x100

static void movePongi(TPongi pongi, int dmove[3], TObstacle obstacles[], TBall ball);
static void clearPongi(TPongi pongi);
static void printPongi(TPongi pongi);
static int isOutOfBoundsPongi(TPongi pongi);

TPongi createPongi(int x, int y){
    static unsigned long next_addr = PONGI_BASE_ADDR;
    TPongi pongi = (TPongi)next_addr;
    next_addr += PONGI_SIZE;

    pongi->x = x;
    pongi->y = y;
    pongi->points = 0;
    pongi->color = PONGI_BLUE;
    return pongi;
}

static void movePongi(TPongi pongi, int dmove[3], TObstacle obstacles[], TBall ball) {

    if(pongi == NULL){
        return;
    }

    if(checkBallCollision(ball, pongi, dmove)){
        moveBall(ball, dmove, obstacles);
        return;
    }

    if(!checkPongiObstacleCollision(pongi, dmove, obstacles)){
        clearPongi(pongi);
        pongi->x += dmove[0] * PONGI_SPEED;
        pongi->y += dmove[1] * PONGI_SPEED;
        printPongi(pongi);
    } else {
        printPongi(pongi);
        printObstacles(obstacles);
    }
}

void movePongis(TPongi pongis[], int dmove[3], TObstacle obstacles[], TBall ball) {
    if(dmove[2] == 1){
        movePongi(pongis[0], dmove, obstacles, ball);
    } else if(dmove[2] == 2){
        movePongi(pongis[1], dmove, obstacles, ball);
    }
}

static void clearPongi(TPongi pongi){
    if(pongi == NULL){
        return;
    }
    syscall_drawCircle(pongi->x, pongi->y, PONGI_RADIUS, GREEN);
}

static void printPongi(TPongi pongi) {
    if (pongi == NULL) {
        return;
    }
    syscall_drawCircle(pongi->x, pongi->y, PONGI_RADIUS, pongi->color);
}

void printPongis(TPongi pongis[]) {
    printPongi(pongis[0]);
    printPongi(pongis[1]);
}


// FALTA AGREGARLO AL MOVIMIENTO 

static int isOutOfBoundsPongi(TPongi pongi){
    if (pongi == NULL) {
        return 0;
    }
    
    int sWidth = syscall_getScreenWidth();
    int sHeight = syscall_getScreenHeight();
    
    return ((pongi->x + PONGI_RADIUS) >= sWidth || 
            (pongi->x - PONGI_RADIUS) < 0 || 
            (pongi->y + PONGI_RADIUS) >= sHeight || 
            (pongi->y - PONGI_RADIUS) < 0);
}

