#define BALL_RADIUS 10

typedef struct Ball {
    int x;         
    int y;          
    int moveSpeed;  
    int color;      
}Ball;


typedef struct Ball * TBall;
typedef struct Obstacle * TObstacle;
typedef struct Hole * THole;
typedef struct Pongi * TPongi;

TBall createBall(int x, int y, int color);
void moveBall(TBall ball, int dmove[3], TObstacle obstacles[]);
int checkBallCollision(TBall ball, TPongi pongi, int dmove[3]);
void printBall(TBall ball);