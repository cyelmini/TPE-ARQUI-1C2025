#include "../include/pongi_golf/collision.h"
#include "../include/pongi_golf/pongi.h"
#include "../include/pongi_golf/ball.h"
#include "../include/pongi_golf/obstacle.h"
#include "../include/pongi_golf/hole.h"

int checkCirclesCollision(int x1, int y1, int r1, int x2, int y2, int r2){
    int dx = x1 - x2;
    int dy = y1 - y2;
    int distanceSquared = dx * dx + dy * dy;
    int radiusSum = r1 + r2;
    return distanceSquared <= (radiusSum * radiusSum);
}

int checkRectangleCircleCollision(int x1, int y1, int height1, int width1, int x2, int y2, int r1 ){
// Encontrar el punto más cercano en el rectángulo al centro del círculo
    int closestX = x2;
    int closestY = y2;

    if (x2 < x1) closestX = x1;
    else if (x2 > x1 + width1) closestX = x1 + width1;

    if (y2 < y1) closestY = y1;
    else if (y2 > y1 + height1) closestY = y1 + height1;

// Calcular la distancia entre el centro del círculo y este punto más cercano
    int dx = x2 - closestX;
    int dy = y2 - closestY;

// Si la distancia es menor que el radio del círculo, hay colisión
    return (dx * dx + dy * dy) <= (r1 * r1);
}