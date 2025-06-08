#include "../include/pongi_golf/pongi.h"
#include "../include/pongi_golf/ball.h"
#include "../include/pongi_golf/obstacle.h"
#include "../include/pongi_golf/hole.h"
#include "../include/pongi_golf/levels.h"
#include "../include/pongi_golf/golf.h"
#include "../include/syscalls.h"
#include "../include/libC.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

// obstaculos seteados a null hasta q los arreglemos meu deus
void setLevel(int level, TPongi pongi[], TBall ball, THole hole, TObstacle obstacles[]) {
    // Posiciones por defecto
    pongi[0]->x = 50;
    pongi[0]->y = 350;
    if(pongi[1] != NULL){
        pongi[1]->x = 50;
        pongi[1]->y = 450;
    }
    ball->x = 100;
    ball->y = 400;

    switch(level) {
        case 1: {
            // Un gran obstáculo vertical en el centro
            TObstacle obs1 = createObstacle(400, 200, MARRON, 400, 120); // vertical grande
            hole->x = 900;
            hole->y = 400;
            hole->size = 60;
            obstacles[0] = obs1;
            obstacles[1] = NULL;
            break;
        }
        case 2: {
            // Dos obstáculos horizontales, dejando un pasillo central
            TObstacle obs1 = createObstacle(250, 150, MARRON, 80, 600); // arriba
            TObstacle obs2 = createObstacle(250, 500, MARRON, 80, 600); // abajo
            hole->x = 900;
            hole->y = 350;
            hole->size = 50;
            obstacles[0] = obs1;
            obstacles[1] = obs2;
            obstacles[2] = NULL;
            break;
        }
        case 3: {
            // Obstáculo en cruz grande en el centro, otro abajo
            TObstacle obs1 = createObstacle(400, 200, MARRON, 400, 120); // vertical
            TObstacle obs2 = createObstacle(300, 350, MARRON, 120, 400); // horizontal
            TObstacle obs3 = createObstacle(100, 650, MARRON, 80, 800);  // horizontal abajo
            pongi[0]->x = 80;
            pongi[0]->y = 80;
            ball->x = 120;
            ball->y = 120;
            hole->x = 900;
            hole->y = 100;
            hole->size = 40;
            obstacles[0] = obs1;
            obstacles[1] = obs2;
            obstacles[2] = obs3;
            obstacles[3] = NULL;
            break;
        }
        case 4: {
            // Laberinto: varios obstáculos grandes y pequeños
            TObstacle obs1 = createObstacle(200, 200, MARRON, 80, 600);   // horizontal arriba
            TObstacle obs2 = createObstacle(600, 200, MARRON, 400, 80);   // vertical derecha
            TObstacle obs3 = createObstacle(200, 500, MARRON, 80, 600);   // horizontal abajo
            TObstacle obs4 = createObstacle(400, 350, MARRON, 120, 200);  // horizontal centro
            pongi[0]->x = 80;
            pongi[0]->y = 700;
            ball->x = 120;
            ball->y = 650;
            hole->x = 900;
            hole->y = 700;
            hole->size = 30;
            obstacles[0] = obs1;
            obstacles[1] = obs2;
            obstacles[2] = obs3;
            obstacles[3] = obs4;
            obstacles[4] = NULL;
            break;
        }
        case 5: {
            // Gran obstáculo en espiral/camino
            TObstacle obs1 = createObstacle(200, 100, MARRON, 600, 80);   // vertical izquierda
            TObstacle obs2 = createObstacle(200, 100, MARRON, 80, 600);   // horizontal arriba
            TObstacle obs3 = createObstacle(720, 100, MARRON, 600, 80);   // vertical derecha
            TObstacle obs4 = createObstacle(200, 620, MARRON, 80, 600);   // horizontal abajo
            pongi[0]->x = 100;
            pongi[0]->y = 120;
            ball->x = 150;
            ball->y = 180;
            hole->x = 900;
            hole->y = 700;
            hole->size = 25;
            obstacles[0] = obs1;
            obstacles[1] = obs2;
            obstacles[2] = obs3;
            obstacles[3] = obs4;
            obstacles[4] = NULL;
            break;
        }
        default:
            break;
    }
}