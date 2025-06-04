#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

#include <stdint.h>
#include <stdarg.h>

// Manejo de píxeles y pantalla
void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
void putRectangle(uint64_t x, uint64_t y, uint64_t height, uint64_t width, uint32_t hexColor);
void drawCircle(uint64_t x0, uint64_t y0, uint64_t radius, uint64_t color) 
void clearRectangle(uint64_t x, uint64_t y, uint64_t height, uint64_t width);
void clearScreen();
void changeBackgroundColor(uint32_t hexColor);

// Manejo del cursor
uint64_t getCursorX();
uint64_t getCursorY();
void setCursor(uint64_t x, uint64_t y);
void drawCursor();

// Dimensiones de pantalla y caracteres
uint64_t getScreenHeight();
uint64_t getScreenWidth();
void changeCharSize(int size);
void defaultCharSize();
uint64_t getCharHeight();

// Funciones de impresión
void putChar(char c, uint32_t hexcode);
void printf(char * str, uint32_t hexcode);
void puts(char * string);
void print(const char * string, va_list list);

// Funciones auxiliares
char * numToString(uint64_t num);

// Control de caracteres especiales
void drawChar(char c, uint32_t hexcode);
void putBackspace();
void putNewLine();
void putTab();


#endif // VIDEODRIVER_H