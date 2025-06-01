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

// Set screen size to a reasonable fixed value
#define SCREEN_HEIGHT 30
#define SCREEN_WIDTH 80

typedef struct Pongi{
    int x;
    int y;
    int points;
    int color;
}Pongi;

typedef struct Pongi * TPongi;

static int screenMatrix[SCREEN_HEIGHT][SCREEN_WIDTH] = {0}; // 0: fondo, 1: pongi, 2: pelota, 3: hoyo, 4: obstaculo


void playGolf(void);
void play(int players);
void startLevel(Pongi pongis[], int level);
void setObstacles(int level);
void setGoal(int level);
void setPongis(Pongi pongis[]);
void putPongi(int x, int y);
void movePongi(void);
void moveBall(void);

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
    int level = 0;
    Pongi pongis[MAX_PLAYERS] = {0}; // Fixed-size array
    syscall_changeCharSize(25, 25);
    while(level < MAX_LEVELS){
        startLevel(pongis, level);
        level++;
    }
    syscall_defaultCharSize();
}

void startLevel(Pongi pongis[], int level) {
    setObstacles(level);
    setGoal(level);
    setPongis(pongis);
}

void setObstacles(int level){
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

void putPongi(int x, int y){
    
}

void movePongi(){

}

void moveBall(){

}