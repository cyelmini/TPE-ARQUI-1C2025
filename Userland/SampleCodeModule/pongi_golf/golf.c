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

/**
 * @brief Ejecuta el bucle principal del juego, controlando los niveles, entrada de usuario y lógica de avance.
 * 
 * @param players Número de jugadores (1 o 2).
 */
static void gameLoop(int players);

/**
 * @brief Finaliza el juego estableciendo la variable de control a estado de cierre.
 * 
 * @param end Puntero a la variable que indica si el juego debe terminar.
 */
static void quitGame(int * end);

/**
 * @brief Dibuja en pantalla todos los elementos del juego en su estado actual.
 * 
 * @param ball Puntero a la pelota.
 * @param pongis Arreglo de jugadores.
 * @param obstacles Arreglo de obstáculos.
 * @param hole Puntero al hoyo objetivo del nivel.
 * @param players Cantidad de jugadores activos.
 */
static void renderGame(TBall ball, TPongi pongis[], TObstacle obstacles[], THole hole, int players);

/**
 * @brief Cambia el color de fondo de la pantalla del juego.
 * 
 * @param color Código de color a aplicar como fondo.
 */
static void changeBackscreen(int color);

/**
 * @brief Muestra los puntajes actuales de los jugadores en pantalla.
 * 
 * @param pongis Arreglo de jugadores con su información.
 * @param players Cantidad de jugadores activos.
 */
static void displayScores(TPongi pongis[], int players);

/**
 * @brief Reproduce una secuencia corta de sonidos que indica que se ganó el nivel.
 */
static void playShortWinSound();


// ---- Manejo de input del jugador ----
static void handlePlayerInput(char *keyStates, int players, int dmove1[3], int dmove2[3]) {
    // Player 1: teclas W A S D
    dmove1[0] = dmove1[1] = dmove1[2] = 0;
    if (keyStates[0x11]) { dmove1[1] = -1; dmove1[2] = 1; } // W
    if (keyStates[0x1F]) { dmove1[1] = 1;  dmove1[2] = 1; } // S
    if (keyStates[0x1E]) { dmove1[0] = -1; dmove1[2] = 1; } // A
    if (keyStates[0x20]) { dmove1[0] = 1;  dmove1[2] = 1; } // D

    // Player 2: teclas I J K L
    dmove2[0] = dmove2[1] = dmove2[2] = 0;
    if (players == 2) {
        if (keyStates[0x17]) { dmove2[1] = -1; dmove2[2] = 2; } // I
        if (keyStates[0x25]) { dmove2[1] = 1;  dmove2[2] = 2; } // K
        if (keyStates[0x24]) { dmove2[0] = -1; dmove2[2] = 2; } // J
        if (keyStates[0x26]) { dmove2[0] = 1;  dmove2[2] = 2; } // L
    }
}

// ---- Manejo del movimiento de los jugadores ----
static void handlePlayerMovement(TPongi pongis[], int players, int dmove1[3], int dmove2[3], TObstacle obstacles[], TBall ball, THole hole) {
    if (dmove1[2] != 0) {
        movePongis(pongis, dmove1, obstacles, ball, hole);
    }
    if (players == 2 && dmove2[2] != 0) {
        movePongis(pongis, dmove2, obstacles, ball, hole);
    }
}

// ---- Verificación de victoria de nivel ----
static int handleLevelWin(TBall ball, THole hole, int players, int dmove1[3], int dmove2[3], TPongi pongis[]) {
    if (wonLevel(ball, hole)) {
        playShortWinSound();
        if (dmove1[2] > 0 && dmove1[2] <= players) {
            pongis[dmove1[2]-1]->points++;
        }
        if (dmove2[2] > 0 && dmove2[2] <= players) {
            pongis[dmove2[2]-1]->points++;
        }
        return 1;
    }
    return 0;
}

// ---- Función principal para iniciar el juego ----
void initializeGolf() {
    printf("Bienvenido a Pongi Golf.\nIngrese la cantidad de jugadores (1 o 2)\n");

    char buffer[4];
    scanf(buffer);

    while(buffer[0] != '1' && buffer[0] != '2'){
        printf("Opcion invalida. Por favor, ingrese 1 o 2 jugadores.\n");
        scanf(buffer);
    }

    int players = atoi(buffer);
    printf("Para cerrar el juego tocar la tecla 'Q'.\nEl Jugador 1 se mueve con W, A, S, D.\n");
    if(players == 2){
        printf("El Jugador 2 se mueve con I, J, K, L.\n");
    }
    printf("El juego esta cargando...\n");
    syscall_sleep(2500);
    changeBackscreen(GREEN);
    gameLoop(players);
    syscall_setGameMode(0); // Salida del modo juego
    }

// ---- Bucle principal del juego ----
static void gameLoop(int players) {
    syscall_setGameMode(1); // Modo juego activo

    TPongi pongis[MAX_PLAYERS] = {0};
    pongis[0] = createPongi(50, 50, PONGI_BLUE);

    if(players == 2){
        pongis[1] = createPongi(50, 100, PONGI_RED);
    }

    TBall ball = createBall(60, 50, WHITE);
    THole hole = createHole(1000, 700, 20);
    TObstacle obstacles[MAX_OBSTACLES];

    int dmove1[3] = {0,0,0};
    int dmove2[3] = {0,0,0};

    int end = 0;
    char keyStates[58];

    for(int level = 1 ; level <= MAX_LEVELS && !end; ) {
        setLevel(level, pongis, ball, hole, obstacles);
        renderGame(ball, pongis, obstacles, hole, players);

        while (!end) {
            syscall_getKeyPressed(keyStates);
            handlePlayerInput(keyStates, players, dmove1, dmove2);
            if (keyStates[0x10]) { // Q
                quitGame(&end);
                return;
            }
            handlePlayerMovement(pongis, players, dmove1, dmove2, obstacles, ball, hole);
            if (handleLevelWin(ball, hole, players, dmove1, dmove2, pongis)) {
                level++;
                break;
            }
            syscall_sleep(25); // Delay para control de tiempo de ciclo
        }
    }

    changeBackscreen(BLACK);
    syscall_setCursor(10, 10);
    printf("Ganaste!!!!!! Nos vemos en la proxima version.\n");

}

// ---- Funciones auxiliares de juego ----

// Finaliza el juego
static void quitGame(int * end) {
    *end = 1;
    changeBackscreen(BLACK);
    syscall_setCursor(10, 10);
    printf("Juego finalizado\n");
}

// Dibuja el estado inicial del nivel en pantalla
static void renderGame(TBall ball, TPongi pongis[], TObstacle obstacles[], THole hole, int players){
    changeBackscreen(GREEN);
    printPongis(pongis);
    printBall(ball);
    printObstacles(obstacles);
    printHole(hole);
    displayScores(pongis, players);
}

// Cambia el color de fondo
static void changeBackscreen(int color){
    syscall_changeBackgroundColor(color);
}

// Reproduce una secuencia de sonido corta para victoria
static void playShortWinSound(){
    syscall_sound(100, 587);  // D5
    syscall_sound(100, 698);  // F5
    syscall_sound(200, 880);  // A5
    syscall_sound(400, 1175); // D6
}

// Muestra los puntajes de los jugadores en pantalla
static void displayScores(TPongi pongis[], int players) {
    int leftX = 10;
    int rightX = SCREEN_WIDTH - 180; 
    int y = 10;

    // Puntaje del jugador 1
    syscall_setCursor(leftX, y);
    printColor("Player 1: ", WHITE); 
    char* score1Str = numToString(pongis[0]->points);
    printColor(score1Str, WHITE);
    
    // Puntaje del jugador 2
    if(players == 2) {
        syscall_setCursor(rightX, y);
        printColor("Player 2: ", WHITE); 
        char* score2Str = numToString(pongis[1]->points);
        printColor(score2Str, WHITE);
    }
}
