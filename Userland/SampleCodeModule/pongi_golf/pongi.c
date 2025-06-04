#include "../include/pongi_golf/pongi.h"
#include "../include/syscalls.h"

#define NULL 0
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define PONGI_BLUE 0x96e2ee

TPongi createPongi(int x, int y) {
    TPongi pongi = 0;
    pongi->x = x;
    pongi->y = y;
    pongi->points = 0;
    pongi->color = PONGI_BLUE;
    return pongi;
}

static void movePongi(TPongi pongi, int dmove[3]) {

    pongi->x += dmove[0];
    pongi->y += dmove[1];

    checkCollision(pongi, obstacles);
}

void movePongis(TPongi pongis[], dmove[3]) {

    if(dmove[2] == 1){
        movePongi(pongis[0];)
    }
    if(dmove[2] == 2){
        movePongi(pongis[1]);
    }
}

void printPongi(TPongi pongi) {
    if (pongi == NULL) {
        return;
    }
    syscall_drawCircle(pongi->x, pongi->y, 10, pongi->color);
}

void printPongis(TPongi pongis[]) {
    printPongi(pongis[0]);
    printPongi(pongis[1]);
}

