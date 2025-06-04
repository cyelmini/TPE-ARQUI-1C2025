#ifndef OBSTACLE_H
#define OBSTACLE_H

typedef struct Obstacle {
    int x;
    int y;
    int color;
    int height;
    int width;
}Obstacle;

typedef Obstacle* TObstacle;

#endif // OBSTACLE_H