#define MAX_OBSTACLES 5

typedef struct Obstacle {
    int x;
    int y;
    int color;
    int height;
    int width;
}Obstacle;

typedef struct Ball * TBall;
typedef struct Obstacle * TObstacle;
typedef struct Hole * THole;
typedef struct Pongi * TPongi;


TObstacle createObstacle(int x, int y, int color, int height, int width) ;
int checkPongiObstacleCollision(TPongi pongi, int dmove[3], TObstacle obstacles[]);
int checkBallObstacleCollision(TBall ball, int dmove[3], TObstacle obstacles[]);
void printObstacles(TObstacle obstacles[]);

