#include "../include/pongi_golf/golf.h"
#include "../include/pongi_golf/pongi.h"
#include "../include/pongi_golf/ball.h"
#include "../include/pongi_golf/obstacle.h"
#include "../include/pongi_golf/hole.h"
#include "../include/pongi_golf/levels.h"
#include "../include/syscalls.h"
#include "../include/libC.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define MAX_PLAYERS 2
#define MAX_LEVELS 5

static void gameLoop(int players);
static void quitGame(int * end);
static void processInput(char input, int dmove[]);
static void renderGame(TBall ball, TPongi pongis[], TObstacle obstacles[], THole hole, int players);
static void changeBackscreen(int color);
static void displayScores(TPongi pongis[], int players);
static void playShortWinSound();

void initializeGolf() {
    printf("Bienvenido a Pongi Golf\nIngrese cantidad de jugadores (1 o 2)\n");

    char buffer[4];
    scanf(buffer);

    while(buffer[0] != '1' && buffer[0] != '2'){
        printf("1 O 2 JUGADORES. INGRESE NUEVAMENTE:\n");
        scanf(buffer);
    }
    int players = atoi(buffer);
    changeBackscreen(GREEN);
    gameLoop(players);

    printf("Ganaste! Nos vemos en la proxima version\n");
}

static void gameLoop(int players) {

    TPongi pongis[MAX_PLAYERS] = {0};
    pongis[0] = createPongi(50, 50);
    if(players == 2){
        pongis[1] = createPongi(50, 100);
    }
    
    TBall ball = createBall(60, 50, WHITE);

    THole hole = createHole(1000, 700, 20);

    TObstacle obstacles[MAX_OBSTACLES];

    int dmove[3] = {0,0,0};            

    char input;

    int end = 0;
    
    for(int level = 1 ; level <= MAX_LEVELS && !end; ) {

        setLevel(level, pongis, ball, hole, obstacles);
    
        renderGame(ball, pongis, obstacles, hole, players);

        while (!end) {
            input = readChar();
            if (input == 'q') {
                quitGame(&end);
                break;
            }
            processInput(input, dmove);

            movePongis(pongis, dmove, obstacles, ball, hole);       // movePongis moves the ball if theres a collision
        
            if(wonLevel(ball, hole)){
                playShortWinSound();
                // Increment score for the player who last hit the ball
                if(dmove[2] > 0 && dmove[2] <= players) {
                    pongis[dmove[2]-1]->points++;
                }
                level++;
                break;
            }
        }
    }
}

static void quitGame(int * end) {
    *end = 1;
    printf("Juego finalizado\n");
    changeBackscreen(BLACK);
}

static void processInput(char input, int * dmove){
    dmove[0] = 0;
    dmove[1] = 0;
    dmove[2] = 0;
    switch(input){
        // up
        case 'w':
            dmove[1] = -1;
            dmove[2] = 1;
            break;
        case 'i':
            dmove[1] = -1;
            dmove[2] = 2;
            break;
        // down
        case 's':
            dmove[1] = 1;
            dmove[2] = 1;
            break;
        case 'k':
            dmove[1] = 1;
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

static void renderGame(TBall ball, TPongi pongis[], TObstacle obstacles[], THole hole, int players){
    changeBackscreen(GREEN);
    printPongis(pongis);
    printBall(ball);
    printObstacles(obstacles);
    printHole(hole);
    displayScores(pongis, players);
}

static void changeBackscreen(int color){
    syscall_changeBackgroundColor(color);
}

static void playShortWinSound(){
    syscall_sound(100, 587);  // D5
    syscall_sound(100, 698);  // F5
    syscall_sound(200, 880);  // A5
    syscall_sound(400, 1175); // D6
}

static void displayScores(TPongi pongis[], int players) {
    int leftX = 10;
    int rightX = SCREEN_WIDTH - 180; 
    int y = 10;
    
    // Player 1:
    syscall_setCursor(leftX, y);
    printColor("Player 1: ", WHITE); 
    char* score1Str = numToString(pongis[0]->points);
    printColor(score1Str, WHITE);
    
    // Player 2: 
    if(players == 2) {
        syscall_setCursor(rightX, y);
        printColor("Player 2: ", WHITE); 
        char* score2Str = numToString(pongis[1]->points);
        printColor(score2Str, WHITE);
    }
}
