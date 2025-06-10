#include <stdint.h>

/**
 * @brief Lee bytes de un descriptor de archivo.
 * 
 * @param fd Descriptor de archivo de donde leer.
 * @param buffer Buffer donde se almacenan los datos leídos.
 * @param count Cantidad de bytes a leer.
 */
extern void syscall_read(int fd, char * buffer, int count);

/**
 * @brief Escribe bytes en un descriptor de archivo.
 * 
 * @param fd Descriptor de archivo donde escribir.
 * @param buffer Buffer con los datos a escribir.
 * @param count Cantidad de bytes a escribir.
 */
extern void syscall_write(int fd, const char * buffer, int count);

/**
 * @brief Obtiene la cantidad de segundos transcurridos desde el inicio.
 * 
 * @param seconds Puntero donde se almacena el resultado.
 */
extern void syscall_seconds(uint64_t * seconds);

/**
 * @brief Obtiene la cantidad de minutos transcurridos desde el inicio.
 * 
 * @param minutes Puntero donde se almacena el resultado.
 */
extern void syscall_minutes(uint64_t * minutes);

/**
 * @brief Obtiene la cantidad de horas transcurridas desde el inicio.
 * 
 * @param hours Puntero donde se almacena el resultado.
 */
extern void syscall_hours(uint64_t * hours);

/**
 * @brief Reproduce un sonido durante un tiempo y frecuencia determinados.
 * 
 * @param time Duración del sonido en milisegundos.
 * @param frequency Frecuencia del sonido en Hz.
 */
extern void syscall_sound(int time, int frequency);

/*
 * Establece la posición del cursor en la pantalla en (x, y).
 * Parámetros:
 *   x - Posición horizontal.
 *   y - Posición vertical.
 */
extern void syscall_setCursor(int x, int y);

/*
 * Devuelve la posición X actual del cursor.
 * Retorna:
 *   Posición horizontal del cursor.
 */
extern int syscall_getCursorX();

/*
 * Devuelve la posición Y actual del cursor.
 * Retorna:
 *   Posición vertical del cursor.
 */
extern int syscall_getCursorY();

/*
 * Dibuja el cursor en la pantalla.
 * Retorna:
 *   Valor de estado de la operación.
 */
extern int syscall_drawCursor();

/*
 * Devuelve la altura de la pantalla en píxeles o caracteres.
 * Retorna:
 *   Altura de la pantalla.
 */
extern int syscall_getScreenHeight();

/*
 * Devuelve el ancho de la pantalla en píxeles o caracteres.
 * Retorna:
 *   Ancho de la pantalla.
 */
extern int syscall_getScreenWidth();

/*
 * Devuelve el estado de los registros del sistema (útil para debug).
 * Retorna:
 *   Estado de los registros.
 */
extern int syscall_getRegisters();

/*
 * Limpia la pantalla.
 */
extern void syscall_clearScreen();

/*
 * Cambia el tamaño de los caracteres a 'size'.
 * Parámetros:
 *   size - Nuevo tamaño de los caracteres.
 */
extern void syscall_changeCharSize(int size);

/*
 * Restaura el tamaño de los caracteres al valor por defecto.
 */
extern void syscall_defaultCharSize();

/*
 * Cambia el color de fondo de la pantalla a 'color'.
 * Parámetros:
 *   color - Nuevo color de fondo.
 */
extern void syscall_changeBackgroundColor(int color);

/*
 * Escribe el carácter 'c' en pantalla con el color 'color'.
 * Parámetros:
 *   c     - Carácter a escribir.
 *   color - Color del carácter.
 */
extern void syscall_colorWrite(char * c, int color);

/*
 * Dibuja un rectángulo en la posición (x, y) con dimensiones y color especificados.
 * Parámetros:
 *   x      - Posición horizontal.
 *   y      - Posición vertical.
 *   height - Altura del rectángulo.
 *   width  - Ancho del rectángulo.
 *   color  - Color del rectángulo.
 */
extern void syscall_putRectangle(int x, int y, int height, int width, int color);

/*
 * Dibuja un círculo en la posición (x, y) con radio y color especificados.
 * Parámetros:
 *   x      - Posición horizontal del centro.
 *   y      - Posición vertical del centro.
 *   radius - Radio del círculo.
 *   color  - Color del círculo.
 */
extern void syscall_drawCircle(int x, int y, int radius, int color);

/*
 * Detiene la ejecución durante 'seconds' segundos.
 * Parámetros:
 *   seconds - Cantidad de segundos a esperar.
 */
extern void syscall_sleep(int seconds);

/*
 * Obtiene la tecla presionada y la almacena en 'buffer'.
 * Parámetros:
 *   buffer - Buffer donde se almacena la tecla presionada.
 */
extern void syscall_getKeyPressed(char *buffer);

/*
 * Activa o desactiva el modo de juego según el valor de 'enabled'.
 * Parámetros:
 *   enabled - 1 para activar, 0 para desactivar.
 */
extern void syscall_setGameMode(int enabled);