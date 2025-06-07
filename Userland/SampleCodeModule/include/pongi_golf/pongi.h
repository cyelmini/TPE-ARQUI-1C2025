typedef struct Pongi {
    int x;
    int y;
    int points;
    int color;
}Pongi;

#define PONGI_SPEED 7
#define PONGI_RADIUS 18


typedef struct Ball * TBall;
typedef struct Obstacle * TObstacle;
typedef struct Hole * THole;
typedef struct Pongi * TPongi;

TPongi createPongi(int x, int y);
void movePongis(TPongi pongis[], int dmove[3], TObstacle obstacles[], TBall ball);
void printPongis(TPongi pongis[]);
