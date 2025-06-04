#include "../include/pongi_golf/pongi.h"
#include "../include/pongi_golf/ball.h"
#include "../include/pongi_golf/obstacle.h"
#include "../include/pongi_golf/hole.h"
#include "../include/pongi_golf/levels.h"
#include "../include/syscalls.h"
#include "../include/libC.h"


#define MAX_PLAYERS 2
#define MAX_LEVELS 5

#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define RED 0xFF0000
#define GREEN 0x00FF00  
#define BLUE 0x0000FF
#define YELLOW 0xFFFF00

void gameLoop();
void cleanup();
void quitGame();

void initializeGolf() {

    printf("Bienvenido a Pongi Golf\nIngrese cantidad de jugadores (1 o 2)\n");
    char buffer = readChar();
    while(buffer != '1' || buffer != '2'){
        printf("1 O DOS JUGADORES. INGRESE NUEVAMENTE:\n");
        buffer = readChar();
    }
    int players = atoi(buffer);
    changeBackscreen(GREEN);
    gameLoop(players);
}

void gameLoop() {

    TPongi pongis[MAX_PLAYERS] = {0};
    pongis[0] = createPongi(50, 50);
    if(players == 2){
        pongis[1] = createPongi(50, 100);
    }
    
    TBall ball = createBall(60, 50, WHITE);

    THole hole = createHole(1000, 700);

    int dmove[3] = {0,0,0};            

    char input;
    
    for(int level = 1 ; level <= MAX_LEVELS ; ) {
        
        changeBackscreen(GREEN);

        Obstacle obstacles[] = setLevel(level, pongis, ball, hole);
        renderGame(ball, pongi, obstacles, hole);

        while (1) {
            input = readChar();
            if (input == 'q') {
            quitGame();
                break;
            }
            processInput(input, &dmove);

            movePongis(pongis, dmove);   // movePongi tiene un checkObstacleCollision y printPongi
            if(checkBallCollision(ball, pongi)){
                moveBall(ball, dmove);      // moveBall tiene un checkObstacleCollision y printBall
            }
            if(wonLevel()){
                level++;
                break;
            }
        }
    }
}

static void quitGame() {
    printf("Juego finalizado\n");
    changeBackscreen(BLACK);
}

static void processInput(char input, int * dmove){
    switch(input){
        // up
        case 'w':
            dmove[1] = 1;
            dmove[2] = 1;
            break;
        case 'i':
            dmove[1] = 1;
            dmove[2] = 2;
            break;
        // down
        case 's':
            dmove[1] = -1;
            dmove[2] = 1;
            break;
        case 'k':
            dmove[1] = -1;
            dmove[2] = 2;
            break;
        // left
        case 'a':
            dmove[0] = -1;
            dmove[2] = 1;
            break;
        case 'j':
            dmove[0] = -1;
            dmove[2] = 2;
            break;
        // right
        case 'd':
            dmove[0] = 1;
            dmove[2] = 1;
            break;
        case 'l':
            dmove[0] = 1;
            dmove[2] = 2;
            break;
        default:
            break;
    }

}

static void renderGame(TBall ball, TPongi pongi, TObstacle obstacles[], THole hole){
    printBall(ball);
    printPongi(pongi);
    printObstacles(obstacles);
    printHole(hole);
}

static void changeBackscreen(int color){
    syscall_putRectangle(0, 0, syscall_getScreenHeight, syscall_getScreenWidth, color);
}