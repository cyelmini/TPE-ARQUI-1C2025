
typedef struct Pongi {
    int x;
    int y;
    int points;
    int color;
}Pongi;

typedef struct Ball * TBall;
typedef struct Obstacle * TObstacle;
typedef struct Hole * THole;
typedef struct Pongi * TPongi;

#define PONGI_COLOR 0x96e2ee
#define PONGI_RADIUS 10


TPongi createPongi(int x, int y);
void movePongis(TPongi pongis[], int dmove[3], TObstacle obstacles[]);
void printPongis(TPongi pongis[]);
