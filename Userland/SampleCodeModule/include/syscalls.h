#include <stdint.h>

/**
 * @brief Lee bytes de un descriptor de archivo.
 * @param fd Descriptor de archivo de donde leer.
 * @param buffer Buffer donde se almacenan los datos leídos.
 * @param count Cantidad de bytes a leer.
 */
extern void syscall_read(int fd, char * buffer, int count);

/**
 * @brief Escribe bytes en un descriptor de archivo.
 * @param fd Descriptor de archivo donde escribir.
 * @param buffer Buffer con los datos a escribir.
 * @param count Cantidad de bytes a escribir.
 */
extern void syscall_write(int fd, const char * buffer, int count);

/**
 * @brief Obtiene la cantidad de segundos transcurridos desde el inicio.
 * @param seconds Puntero donde se almacena el resultado.
 */
extern void syscall_seconds(uint64_t * seconds);

/**
 * @brief Obtiene la cantidad de minutos transcurridos desde el inicio.
 * @param minutes Puntero donde se almacena el resultado.
 */
extern void syscall_minutes(uint64_t * minutes);

/**
 * @brief Obtiene la cantidad de horas transcurridas desde el inicio.
 * @param hours Puntero donde se almacena el resultado.
 */
extern void syscall_hours(uint64_t * hours);

/**
 * @brief Reproduce un sonido durante un tiempo y frecuencia determinados.
 * @param time Duración del sonido en milisegundos.
 * @param frequency Frecuencia del sonido en Hz.
 */
extern void syscall_sound(int time, int frequency);

/**
 * @brief Establece la posición del cursor en la pantalla.
 * @param x Posición horizontal.
 * @param y Posición vertical.
 */
extern void syscall_setCursor(int x, int y);

/**
 * @brief Devuelve la posición X actual del cursor.
 * @return Posición horizontal del cursor.
 */
extern int syscall_getCursorX();

/**
 * @brief Devuelve la posición Y actual del cursor.
 * @return Posición vertical del cursor.
 */
extern int syscall_getCursorY();

/**
 * @brief Dibuja el cursor en la pantalla.
 * @return Valor de estado de la operación.
 */
extern int syscall_drawCursor();

/**
 * @brief Devuelve la altura de la pantalla en píxeles o caracteres.
 * @return Altura de la pantalla.
 */
extern int syscall_getScreenHeight();

/**
 * @brief Devuelve el ancho de la pantalla en píxeles o caracteres.
 * @return Ancho de la pantalla.
 */
extern int syscall_getScreenWidth();

/**
 * @brief Devuelve el estado de los registros del sistema (útil para debug).
 * @return Estado de los registros.
 */
extern int syscall_getRegisters();

/**
 * @brief Limpia la pantalla.
 */
extern void syscall_clearScreen();

/**
 * @brief Cambia el tamaño de los caracteres.
 * @param size Nuevo tamaño de los caracteres.
 */
extern void syscall_changeCharSize(int size);

/**
 * @brief Restaura el tamaño de los caracteres al valor por defecto.
 */
extern void syscall_defaultCharSize();

/**
 * @brief Cambia el color de fondo de la pantalla.
 * @param color Nuevo color de fondo.
 */
extern void syscall_changeBackgroundColor(int color);

/**
 * @brief Escribe el carácter 'c' en pantalla con el color especificado.
 * @param c Carácter a escribir.
 * @param color Color del carácter.
 */
extern void syscall_colorWrite(char * c, int color);

/**
 * @brief Dibuja un rectángulo en la pantalla.
 * @param x Posición horizontal.
 * @param y Posición vertical.
 * @param height Altura del rectángulo.
 * @param width Ancho del rectángulo.
 * @param color Color del rectángulo.
 */
extern void syscall_putRectangle(int x, int y, int height, int width, int color);

/**
 * @brief Dibuja un círculo en la pantalla.
 * @param x Posición horizontal del centro.
 * @param y Posición vertical del centro.
 * @param radius Radio del círculo.
 * @param color Color del círculo.
 */
extern void syscall_drawCircle(int x, int y, int radius, int color);

/**
 * @brief Detiene la ejecución durante una cantidad de milisegundos.
 * @param miliseconds Cantidad de milisegundos a esperar.
 */
extern void syscall_sleep(int miliseconds);

/**
 * @brief Obtiene la tecla presionada y la almacena en el buffer.
 * @param buffer Buffer donde se almacena la tecla presionada.
 */
extern void syscall_getKeyPressed(char *buffer);

/**
 * @brief Activa o desactiva el modo de juego.
 * @param enabled 1 para activar, 0 para desactivar.
 */
extern void syscall_setGameMode(int enabled);