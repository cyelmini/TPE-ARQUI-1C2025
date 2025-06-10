#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

#include <stdint.h>
#include <stdarg.h>

// --- Manejo de píxeles y pantalla ---

/**
 * @brief Dibuja un píxel en la pantalla
 * @param hexColor Color en formato hexadecimal RGB
 * @param x Coordenada x del píxel
 * @param y Coordenada y del píxel
 * @return void
 */
void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);

/**
 * @brief Dibuja un rectángulo en la pantalla
 * @param x Coordenada x de la esquina superior izquierda
 * @param y Coordenada y de la esquina superior izquierda
 * @param height Altura del rectángulo
 * @param width Ancho del rectángulo
 * @param hexColor Color en formato hexadecimal RGB
 * @return void
 */
void putRectangle(uint64_t x, uint64_t y, uint64_t height, uint64_t width, uint32_t hexColor);

/**
 * @brief Dibuja un círculo en la pantalla
 * @param x0 Coordenada x del centro del círculo
 * @param y0 Coordenada y del centro del círculo
 * @param radius Radio del círculo
 * @param color Color en formato hexadecimal RGB
 * @return void
 */
void drawCircle(uint64_t x0, uint64_t y0, uint64_t radius, uint64_t color);

/**
 * @brief Limpia un área rectangular de la pantalla (la colorea de negro)
 * @param x Coordenada x de la esquina superior izquierda
 * @param y Coordenada y de la esquina superior izquierda
 * @param height Altura del rectángulo a limpiar
 * @param width Ancho del rectángulo a limpiar
 * @return void
 */
void clearRectangle(uint64_t x, uint64_t y, uint64_t height, uint64_t width);

/**
 * @brief Limpia toda la pantalla (la colorea de negro) y reinicia la posición del cursor
 * @return void
 */
void clearScreen();

/**
 * @brief Cambia el color de fondo de toda la pantalla
 * @param hexColor Color en formato hexadecimal RGB
 * @return void
 */
void changeBackgroundColor(uint32_t hexColor);

// --- Manejo del cursor ---

/**
 * @brief Obtiene la posición x actual del cursor (en unidades de caracteres)
 * @return uint64_t Posición x del cursor
 */
uint64_t getCursorX();

/**
 * @brief Obtiene la posición y actual del cursor (en unidades de caracteres)
 * @return uint64_t Posición y del cursor
 */
uint64_t getCursorY();

/**
 * @brief Establece la posición del cursor
 * @param x Nueva coordenada x del cursor
 * @param y Nueva coordenada y del cursor
 * @return void
 */
void setCursor(uint64_t x, uint64_t y);

/**
 * @brief Dibuja el cursor en la pantalla (como un rectángulo blanco)
 * @return void
 */
void drawCursor();

// --- Dimensiones de pantalla y caracteres ---

/**
 * @brief Obtiene la altura total de la pantalla en píxeles
 * @return uint64_t Altura de la pantalla
 */
uint64_t getScreenHeight();

/**
 * @brief Obtiene el ancho total de la pantalla en píxeles
 * @return uint64_t Ancho de la pantalla
 */
uint64_t getScreenWidth();

/**
 * @brief Cambia el tamaño de los caracteres
 * @param size Valor a sumar o restar al tamaño actual (positivo para aumentar, negativo para disminuir)
 * @return void
 */
void changeCharSize(int size);

/**
 * @brief Restablece el tamaño de los caracteres a su valor predeterminado
 * @return void
 */
void defaultCharSize();

/**
 * @brief Obtiene la altura actual de los caracteres en píxeles
 * @return uint64_t Altura del carácter
 */
uint64_t getCharHeight();

// --- Funciones de impresión ---

/**
 * @brief Imprime un carácter en la posición actual del cursor
 * @param c Carácter a imprimir
 * @param hexcode Color en formato hexadecimal RGB
 * @return void
 */
void putChar(char c, uint32_t hexcode);

/**
 * @brief Imprime una cadena de texto en la posición actual del cursor
 * @param str Cadena de texto a imprimir
 * @param hexcode Color en formato hexadecimal RGB
 * @return void
 */
void printf(char * str, uint32_t hexcode);

/**
 * @brief Imprime una cadena de texto en color blanco y añade un salto de línea al final
 * @param string Cadena de texto a imprimir
 * @return void
 */
void puts(char * string);

/**
 * @brief Imprime texto con formato similar a printf de C
 * @param string Cadena de formato
 * @param list Lista de argumentos variables
 * @return void
 */
void print(const char * string, va_list list);

// --- Funciones auxiliares ---

/**
 * @brief Convierte un número entero a su representación en cadena de texto
 * @param num Número a convertir
 * @return char* Puntero a la cadena resultante
 */
char * numToString(uint64_t num);

// --- Control de caracteres especiales ---

/**
 * @brief Dibuja un carácter en la posición actual del cursor
 * @param c Carácter a dibujar
 * @param hexcode Color en formato hexadecimal RGB
 * @return void
 */
void drawChar(char c, uint32_t hexcode);

/**
 * @brief Maneja la funcionalidad de la tecla de retroceso (borrar carácter anterior)
 * @return void
 */
void putBackspace();

/**
 * @brief Maneja la funcionalidad de salto de línea
 * @return void
 */
void putNewLine();

/**
 * @brief Maneja la funcionalidad de tabulación
 * @return void
 */
void putTab();

#endif // VIDEODRIVER_H