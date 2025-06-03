/*
    empezar haciendo q sea plano, despues si nos queda tiempo agregar obstaculos
    agregar rebote a los obstaculos

    hacer q pongi tenga velocidad, y segun la velocidad con la que le pega a la pelota, esta sale disparada mas lejos
    -> tener niveles de velcidad, trackeando cuanto se mueve sin frenar (cuando frena se resetea) y cada nivel de velocidad tiene un numero de casillas que hace q se mueva la pelota
    -> tener 8 direcciones: NO  N  NE
                            O   C   E
                            SO  S  SE

*/
#include "include/libC.h"
#include "include/syscalls.h"

#define BUFFER_SIZE 10
#define MAX_LEVELS 5
#define MAX_PLAYERS 2

// Colors
#define BLACK 0x000000
#define WHITE
#define LIGHT_GRASS_GREEN 0xc0ff6d
#define GRASS_GREEN 0x62bc2f
#define EARTH_BROWN 0x5d441d
#define PONGI_BLUE 0x96e2ee
#define SEA_BLUE 0x1b72ae

typedef struct Pongi{
    float x;
    float y;
    int points;
    int color;
    int moveSpeed;
}Pongi;

typedef struct Pongi * TPongi;

typedef struct Ball{
    int x;
    int y;
    int color;
    int moveSpeed;
}Ball;

typedef Ball * TBall;

typedef struct Obstacle{
    float x;
    float y;
    int color;
}Obstacle;

typedef struct Obstacle * TObstacle;

typedef struct Screen{
    int ** matrix;
    TObstacle * obstacles;
}Screen;

typedef struct Screen * TScreen;

// Declaraciones, en .h playGolf
void playGolf(void);
void play(int players);
void startLevel(Pongi pongis[], int level);
void setBackground();
void setObstacles(int level);
void setGoal(int level);
void setPongis(Pongi pongis[]);
TObstacle createObstacle(int x, int y, int color);
void createPongi(int x, int y);
void movePongi(void);
void moveBall(void);

static TScreen screen;

void playGolf(){
    printf("Bienvenido al Pongi Golf. Ingrese la cantidad de jugadores (1 o 2):\n");
    char buffer[BUFFER_SIZE];
    scanf(buffer);
    int players = 0;
    if(strcmp(buffer, "1") == 0){
        players = 1;
    } else if(strcmp(buffer, "2") == 0){
        players = 2;
    } else {
        printf("esto no seria posible sin vos fede\n");
        return;
    }
    play(players);
}

// por cada nivel cambia: tamaño del hoyo y cantidad de obstaculos

void play(int players){
    Pongi pongis[MAX_PLAYERS] = {0}; // Fixed-size array

    syscall_changeCharSize(15, 15);
    
    int level = 0;
    while(level < MAX_LEVELS){
        startLevel(pongis, level);
        level++;
    }

    // Fin del juego
    syscall_defaultCharSize();
    syscall_changeBackgroundColor(BLACK);
    printf("Ganaste\nQue mas queres? Andate.\n");
}

void startLevel(Pongi pongis[], int level) {
    setBackground();
    setObstacles(level);
    setGoal(level);
    setPongis(pongis);
    //printLevel();
}

void setBackground(){
    syscall_changeBackgroundColor(GRASS_GREEN);
}

// Seteo
void setObstacles(int level){
    switch(level){
        case 0:
            screen->obstacles[0] = createObstacle(15, 0, EARTH_BROWN);
        return;
        case 1:

        return;
        case 2:

        return;
        case 3:

        return;
        case 4:

        return;
    }
}


void setGoal(int level){
    switch(level){
        case 0:

        return;
        case 1:

        return;
        case 2:

        return;
        case 3:

        return;
        case 4:

        return;
    }
}


void setPongis(Pongi pongis[]){
    
}

void createPongi(int x, int y){
    
}
// Creacion
TObstacle createObstacle(int x, int y, int color){
    TObstacle obstacle = 0;
    obstacle->x = x;
    obstacle->y = y;
    obstacle->color = color;
    return obstacle;
}

// Impresion
void printLevel(){
    //printPongis();
    //printBall();
    //printObstacles();
}

// Movimiento
void movePongi(){

    //printPongi();
}

void moveBall(){

    //printBall();
}