#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

#include <stdint.h>

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y); 

void putChar(char c, int hexcode);

void putBackspace();

void putNewLine();

void putTab();

void drawChar(char c, uint64_t hexcode);

void putRectangle(int x, int y, int height, int width, uint32_t hexColor);

void clearRectangle(int x, int y, int height, int width);

uint64_t getCursorX();

uint64_t getCursorY();

void setCursor(uint64_t x, uint64_t y);


#endif // VIDEODRIVER_H