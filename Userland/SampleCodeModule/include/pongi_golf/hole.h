
typedef struct Hole {
    int x; 
    int y; 
    int size; 
}Hole;


typedef struct Ball * TBall;
typedef struct Obstacle * TObstacle;
typedef struct Hole * THole;
typedef struct Pongi * TPongi;

#define HOLE_COLOR 0x000000


THole createHole(int x, int y, int size);
int wonLevel(TBall ball, THole hole);
void printHole(THole hole);
