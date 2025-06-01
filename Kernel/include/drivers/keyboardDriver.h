#ifndef KEYBOARDDRIVER_H
#define KEYBOARDDRIVER_H

#include <stdint.h>

extern uint8_t getKey();

void keyboardHandler();
char nextChar();
char * getBuffer();
char isCtrlPressed();

#endif
