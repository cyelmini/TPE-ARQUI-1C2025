#define HOLE_COLOR 0x000000

typedef struct Hole {
    int x; 
    int y; 
    int size; 
} Hole;

typedef struct Hole * THole;

THole createHole(int x, int y, int size);
void printHole(THole hole);