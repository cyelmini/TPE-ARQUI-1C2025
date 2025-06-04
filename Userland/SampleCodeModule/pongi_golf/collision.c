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
    // Find the closest point on the rectangle to the circle's center
    int closestX = x2;
    int closestY = y2;

    if (x2 < x1) closestX = x1;
    else if (x2 > x1 + width1) closestX = x1 + width1;

    if (y2 < y1) closestY = y1;
    else if (y2 > y1 + height1) closestY = y1 + height1;

    // Calculate the distance between the circle's center and this closest point
    int dx = x2 - closestX;
    int dy = y2 - closestY;

    // If the distance is less than the circle's radius, there's a collision
    return (dx * dx + dy * dy) <= (r1 * r1);
}