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

void setLevel(int level, TPongi pongi[], TBall ball, THole hole, TObstacle obstacles[]) {
    pongi[0]->x = 50;
    pongi[0]->y = 350;
    if (pongi[1] != NULL) {
        pongi[1]->x = 50;
        pongi[1]->y = 450;
    }
    ball->x = 100;
    ball->y = 400;

    switch (level) {

        case 1: {
            TObstacle obs1 = createObstacle(400, 200, MARRON, 400, 120);
            TObstacle obs2 = createObstacle(460, 125, MARRON, 550, 60);

            hole->x = 900;
            hole->y = 400;
            hole->size = 60;

            obstacles[0] = obs1;
            obstacles[1] = obs2;
            obstacles[2] = NULL;
            break;
        }

        case 2: {
            TObstacle obs1 = createObstacle(150, 150, MARRON, 80, 700);
            TObstacle obs2 = createObstacle(150, 500, MARRON, 80, 700);
            TObstacle obs3 = createObstacle(300, 250, MARRON, 75, 75);
            TObstacle obs4 = createObstacle(600, 400, MARRON, 75, 75);

            hole->x = 900;
            hole->y = 350;
            hole->size = 50;

            obstacles[0] = obs1;
            obstacles[1] = obs2;
            obstacles[2] = obs3;
            obstacles[3] = obs4;
            obstacles[4] = NULL;
            break;
        }

        case 3: {
            TObstacle obs1 = createObstacle(400, 200, MARRON, 400, 120);
            TObstacle obs2 = createObstacle(300, 350, MARRON, 120, 400);
            TObstacle obs3 = createObstacle(100, 650, MARRON, 80, 800);

            pongi[0]->x = 80;
            pongi[0]->y = 580;
            if (pongi[1] != NULL) {
                pongi[1]->x = pongi[0]->x + 40;
                pongi[1]->y = pongi[0]->y + 40;
            }
            ball->x = 120;
            ball->y = 500;

            hole->x = 600;
            hole->y = 600;
            hole->size = 40;

            obstacles[0] = obs1;
            obstacles[1] = obs2;
            obstacles[2] = obs3;
            obstacles[3] = NULL;
            break;
        }

        case 4: {
            TObstacle obs1 = createObstacle(200, 100, MARRON, 600, 80);
            TObstacle obs2 = createObstacle(200, 100, MARRON, 80, 600);
            TObstacle obs4 = createObstacle(200, 620, MARRON, 80, 600);
            TObstacle obs3 = createObstacle(720, 100, MARRON, 450, 80);

            pongi[0]->x = 100;
            pongi[0]->y = 120;
            if (pongi[1] != NULL) {
                pongi[1]->x = pongi[0]->x + 40;
                pongi[1]->y = pongi[0]->y + 40;
            }
            ball->x = 150;
            ball->y = 180;

            hole->x = 475;
            hole->y = 325;
            hole->size = 40;

            obstacles[0] = obs1;
            obstacles[1] = obs2;
            obstacles[2] = obs3;
            obstacles[3] = obs4;
            obstacles[4] = NULL;
            break;
        }

        case 5: {
            TObstacle obs1 = createObstacle(100, 100, MARRON, 20, 600);
            TObstacle obs2 = createObstacle(100, 100, MARRON, 800, 20);
            TObstacle obs3 = createObstacle(900, 100, MARRON, 20, 600);
            TObstacle obs4 = createObstacle(100, 680, MARRON, 800, 20);

            TObstacle obs5 = createObstacle(200, 200, MARRON, 20, 300);
            TObstacle obs6 = createObstacle(200, 200, MARRON, 300, 20);
            TObstacle obs7 = createObstacle(500, 200, MARRON, 20, 200);
            TObstacle obs8 = createObstacle(500, 380, MARRON, 200, 20);
            TObstacle obs9 = createObstacle(700, 380, MARRON, 20, 200);
            TObstacle obs10 = createObstacle(400, 550, MARRON, 300, 20);
            TObstacle obs11 = createObstacle(400, 420, MARRON, 20, 130);
            TObstacle obs12 = createObstacle(650, 420, MARRON, 20, 130);

            pongi[0]->x = 170;
            pongi[0]->y = 70;
            if (pongi[1] != NULL) {
                pongi[1]->x = pongi[0]->x + 40;
                pongi[1]->y = pongi[0]->y;
            }
            ball->x = 160;
            ball->y = 180;

            hole->x = 810;
            hole->y = 630;
            hole->size = 40;

            obstacles[0] = obs1;
            obstacles[1] = obs2;
            obstacles[2] = obs3;
            obstacles[3] = obs4;
            obstacles[4] = obs5;
            obstacles[5] = obs6;
            obstacles[6] = obs7;
            obstacles[7] = obs8;
            obstacles[8] = obs9;
            obstacles[9] = obs10;
            obstacles[10] = obs11;
            obstacles[11] = obs12;
            obstacles[12] = NULL;
            break;
        }

        default:
            break;
    }
}