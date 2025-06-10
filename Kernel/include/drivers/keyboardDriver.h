#ifndef KEYBOARDDRIVER_H
#define KEYBOARDDRIVER_H

#include <stdint.h>

// --- Funciones principales del driver de teclado ---

/**
 * @brief Obtiene el código de escaneo de la última tecla presionada
 * @return uint8_t Código de escaneo de la tecla
 */
extern uint8_t getKey();

/**
 * @brief Maneja las interrupciones del teclado, procesando las teclas presionadas
 * @details Actualiza el estado de teclas especiales (Shift, Ctrl, Alt, Caps) y
 *          almacena los caracteres normales en el buffer de teclado
 * @return void
 */
void keyboardHandler();

/**
 * @brief Obtiene el siguiente carácter disponible en el buffer del teclado
 * @details Consume el carácter del buffer, avanzando el índice de lectura
 * @return char El siguiente carácter del buffer, o -1 si el buffer está vacío
 */
char nextChar();

/**
 * @brief Obtiene un puntero al buffer de teclado completo
 * @return char* Puntero al buffer de caracteres del teclado
 */
char * getBuffer();

/**
 * @brief Verifica si la tecla Ctrl está actualmente presionada
 * @return char 1 si Ctrl está presionado, 0 en caso contrario
 */
char isCtrlPressed();

// --- Funciones y variables auxiliares ---

#define KEYS 58

extern char getKeyPressed[KEYS];
char isKeyPressed(int scancode);

extern int inGameMode;
void setGameMode(int enabled);

#endif