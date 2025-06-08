#include "../include/pongi_golf/pongi.h"
#include "../include/pongi_golf/ball.h"
#include "../include/pongi_golf/obstacle.h"
#include "../include/pongi_golf/golf.h"
#include "../include/pongi_golf/collision.h"
#include "../include/pongi_golf/hole.h"
#include "../include/syscalls.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define SCORE_AREA_HEIGHT 40
#define SCORE_SIGN_WIDTH 180

#define PONGI_BASE_ADDR 0x51000
#define PONGI_SIZE 0x100

static void movePongi(TPongi pongi, int dmove[3], TObstacle obstacles[], TBall ball, THole hole, TPongi pongis[]);
static void clearPongi(TPongi pongi);
static void printPongi(TPongi pongi);
static int checkPongisCollision(TPongi pongi1, TPongi pongi2, int dmove[3]);
static int isOutOfBoundsPongi(int x, int y);
static int isInScoreSignArea(int x);


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

static void movePongi(TPongi pongi, int dmove[3], TObstacle obstacles[], TBall ball, THole hole, TPongi pongis[]) {
    if(pongi == NULL){
        return;
    }

    int nextX;
    int nextY;

    for(int i = 0 ; i < PONGI_SPEED ; i++){
        nextX = pongi->x + dmove[0];
        nextY = pongi->y + dmove[1];

        if (isOutOfBoundsPongi(nextX, nextY)) {
            printPongi(pongi);
            return;
        }

        if(!checkPongiObstacleCollision(pongi, dmove, obstacles)){

            if(checkBallCollision(ball, pongi, dmove)){
                moveBall(ball, dmove, obstacles, pongis);
                return;
            }

            //evitar que el pongi entre en el hoyo
            if(checkCirclesCollision(hole->x, hole->y, hole->size, pongi->x +dmove[0], pongi->y + dmove[1], PONGI_RADIUS)){
                return;
            }


            clearPongi(pongi);
            pongi->x = nextX;
            pongi->y = nextY;
            printPongi(pongi);
        } else {
            printPongi(pongi);
            printObstacles(obstacles);
        }
    }
}

void movePongis(TPongi pongis[], int dmove[3], TObstacle obstacles[], TBall ball, THole hole) {
    if(dmove[2] == 1){
        if(pongis[1] != NULL &&  checkPongisCollision(pongis[0], pongis[1], dmove)){
            return;
        }
        movePongi(pongis[0], dmove, obstacles, ball, hole, pongis);
    } else if(dmove[2] == 2){
        if(checkPongisCollision(pongis[1], pongis[0], dmove)){
            return;
        }
        movePongi(pongis[1], dmove, obstacles, ball, hole, pongis);
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

static int checkPongisCollision(TPongi pongi1, TPongi pongi2, int dmove[3]){
    return checkCirclesCollision(pongi1->x + dmove[0]*PONGI_SPEED, pongi1->y + dmove[1]*PONGI_SPEED, PONGI_RADIUS, pongi2->x, pongi2->y, PONGI_RADIUS);
}

static int isInScoreSignArea(int x) {
    if (x - PONGI_RADIUS < SCORE_SIGN_WIDTH) {
        return 1;
    }
    if (x + PONGI_RADIUS > SCREEN_WIDTH - SCORE_SIGN_WIDTH) {
        return 1;
    }
    return 0;
}

static int isOutOfBoundsPongi(int x, int y) {
    if (y - PONGI_RADIUS < 0){
        return 1;
    }
        
    if (isInScoreSignArea(x) && (y - PONGI_RADIUS < SCORE_AREA_HEIGHT)) {
        return 1;
    }
    if (x - PONGI_RADIUS < 0 || x + PONGI_RADIUS > SCREEN_WIDTH ||
        y + PONGI_RADIUS > SCREEN_HEIGHT) {
        return 1;
    }
    return 0;
}

