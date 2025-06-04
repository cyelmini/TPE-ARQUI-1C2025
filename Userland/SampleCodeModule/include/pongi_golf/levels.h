#include "../include/pongi_golf/pongi.h"
#include "../include/pongi_golf/ball.h"
#include "../include/pongi_golf/obstacle.h"
#include "../include/pongi_golf/hole.h"
#include "../include/pongi_golf/levels.h"
#include "../include/syscalls.h"
#include "../include/libC.h"

void printObstacles(Obstacle obstacles[], int amountOfObstacles);

Obstacle * setLevel(int level, TPongi pongi[], TBall ball, THole hole);