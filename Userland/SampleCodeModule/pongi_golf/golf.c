#include "../include/pongi_golf/input.h"
#include "../include/pongi_golf/pongi.h"
#include "../include/pongi_golf/ball.h"
#include "../include/pongi_golf/obstacle.h"
#include "../include/pongi_golf/hole.h"
#include "../include/libC.h"

#define MAX_PLAYERS 2
#define MAX_LEVELS 5

void gameLoop();
void cleanup();
void quitGame();

void initializeGolf() {
    // FALTA PREGUNTAR CANTIDAD DE JUGADORES

    printf("Initializing Pongi Golf...\n");
    gameLoop();
}

void gameLoop() {
    TPongi pongi = createPongi(10, 10);
    TBall ball = createBall(20, 20, 1, 0xFFFFFF);
    int pongiDirection = 0;
    int ballDirection = 0;
    char input;

    // FALTA SETEAR LOS NIVELES Y POR ENDE LOS OBSTACULOS, EL COLOR DEL FONO (YA ETSA LA SYSCALL)

    while (1) {
        input = readChar();
        if (input == 'q') {
            quitGame();
            break;
        }
        processInput(input, &pongiDirection, &ballDirection);

        movePongi(pongi, pongiDirection);
        moveBall(ball, ballDirection);

        checkCollision(ball, pongi);
        //renderGame(ball, pongi, obstacles); falta implementar (es un printeo de c/ objeto en el vector de esos objetos (vector de obstaculos))

    }
}

void quitGame() {
    printf("Bye\n");
}
