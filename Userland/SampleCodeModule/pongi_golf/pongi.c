#include "../include/pongi_golf/pongi.h"
#include "../include/pongi_golf/obstacle.h"
#include "../include/syscalls.h"
#include "../include/pongi_golf/golf.h"

#define PONGI_BASE_ADDR 0x51000
#define PONGI_SIZE 0x100

static void movePongi(TPongi pongi, int dmove[3], TObstacle obstacles[]);
static void clearPongi(TPongi pongi);
static void printPongi(TPongi pongi);

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

static void movePongi(TPongi pongi, int dmove[3], TObstacle obstacles[]) {

    if(pongi == NULL){
        return;
    }

    if(!checkPongiObstacleCollision(pongi, dmove, obstacles)){
        clearPongi(pongi);
        pongi->x += dmove[0];
        pongi->y += dmove[1];
        printPongi(pongi);
    }
}

void movePongis(TPongi pongis[], int dmove[3], TObstacle obstacles[]) {
    if(dmove[2] == 1){
        movePongi(pongis[0], dmove, obstacles);
    } else if(dmove[2] == 2){
        movePongi(pongis[1], dmove, obstacles);
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

