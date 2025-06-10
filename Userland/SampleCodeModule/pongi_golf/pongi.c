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

/**
 * @brief Mueve un pongi según el vector de desplazamiento, verificando colisiones y límites del campo.
 * 
 * @param pongi Puntero al pongi que se quiere mover.
 * @param dmove Vector de movimiento [dx, dy, número de jugador].
 * @param obstacles Arreglo de obstáculos presentes en el campo.
 * @param ball Puntero a la pelota (para comprobar colisiones o eventos).
 * @param hole Puntero al hoyo (objetivo del nivel).
 * @param pongis Arreglo con todos los pongis activos (para detectar colisiones entre jugadores).
 */
static void movePongi(TPongi pongi, int dmove[3], TObstacle obstacles[], TBall ball, THole hole, TPongi pongis[]);

/**
 * @brief Borra visualmente el pongi de su posición actual en pantalla.
 * 
 * @param pongi Puntero al pongi a borrar.
 */
static void clearPongi(TPongi pongi);

/**
 * @brief Dibuja un pongi en pantalla en su posición actual.
 * 
 * @param pongi Puntero al pongi a dibujar.
 */
static void printPongi(TPongi pongi);

/**
 * @brief Verifica si dos pongis colisionarían al aplicar el movimiento.
 * 
 * @param pongi1 Primer pongi.
 * @param pongi2 Segundo pongi.
 * @param dmove Vector de desplazamiento que se aplicaría al pongi1.
 * @return int 1 si habría colisión, 0 si no.
 */
static int checkPongisCollision(TPongi pongi1, TPongi pongi2, int dmove[3]);

/**
 * @brief Verifica si un pongi se movería fuera de los límites de la pantalla.
 * 
 * @param x Nueva coordenada X del pongi.
 * @param y Nueva coordenada Y del pongi.
 * @return int 1 si se sale de los límites, 0 si no.
 */
static int isOutOfBoundsPongi(int x, int y);

/**
 * @brief Verifica si la coordenada X del pongi está dentro de las áreas reservadas para mostrar puntaje.
 * 
 * @param x Coordenada X del pongi.
 * @return int 1 si está dentro del área de puntaje, 0 si no.
 */
static int isInScoreSignArea(int x);


// ---- Funciones principales ----
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

void printPongis(TPongi pongis[]) {
    printPongi(pongis[0]);
    printPongi(pongis[1]);
}

// ---- Helpers de movimiento ----
static void movePongi(TPongi pongi, int dmove[3], TObstacle obstacles[], TBall ball, THole hole, TPongi pongis[]) {
    if(pongi == NULL){
        return;
    }

    int nextX;
    int nextY;

    // Calcular la posición final
    nextX = pongi->x + dmove[0] * PONGI_SPEED;
    nextY = pongi->y + dmove[1] * PONGI_SPEED;

    if (isOutOfBoundsPongi(nextX, nextY)) {
        return;
    }

    if(!checkPongiObstacleCollision(pongi, dmove, obstacles)){
        if(checkBallCollision(ball, pongi, dmove)){
            moveBall(ball, dmove, obstacles, pongis, hole);
            return;
        }

        // Evitar que el pongi entre en el hoyo
        if(checkCirclesCollision(hole->x, hole->y, hole->size, nextX, nextY, PONGI_RADIUS)){
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

// ---- Helpers de renderizado ----
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

// ---- Helpers de colisión ----
static int checkPongisCollision(TPongi pongi1, TPongi pongi2, int dmove[3]){
    return checkCirclesCollision(pongi1->x + dmove[0]*PONGI_SPEED, pongi1->y + dmove[1]*PONGI_SPEED, PONGI_RADIUS, pongi2->x, pongi2->y, PONGI_RADIUS);
}

// ---- Helpers de límites ----
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

