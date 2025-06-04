#include "../include/pongi_golf/input.h"
#include "../include/libC.h"

void processInput(char input, int *pongiDirection, int *ballDirection) {
    switch (input) {
        case 'w':
            *pongiDirection = 0; // up
            break;
        case 's':
            *pongiDirection = 1; // down
            break;
        case 'a':
            *pongiDirection = 2; // left
            break;
        case 'd':
            *pongiDirection = 3; // right
            break;
        default:
            break;
    }
}