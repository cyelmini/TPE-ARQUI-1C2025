#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>

#define STDIN 0
#define STDOUT 1
#define STERR 2

/**
 * @brief Despachador principal de llamadas al sistema
 * @param syscallNumber Número identificador de la llamada al sistema a ejecutar
 * @param arg1 Primer argumento de la llamada al sistema
 * @param arg2 Segundo argumento de la llamada al sistema
 * @param arg3 Tercer argumento de la llamada al sistema
 * @param arg4 Cuarto argumento de la llamada al sistema
 * @param arg5 Quinto argumento de la llamada al sistema
 * @param arg6 Sexto argumento de la llamada al sistema
 * @return uint64_t Resultado de la llamada al sistema ejecutada
 */
uint64_t sysCallDispatcher(uint64_t syscallNumber, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5, uint64_t arg6);

/**
 * @brief Lee datos desde un descriptor de archivo hacia un buffer
 * @param fd Descriptor de archivo desde donde leer (STDIN, STDOUT, STERR)
 * @param buffer Puntero al buffer donde se almacenarán los datos leídos
 * @param count Cantidad máxima de bytes a leer
 * @return void
 */
void sys_read(uint64_t fd, char * buffer, uint64_t count);

/**
 * @brief Escribe datos desde un buffer hacia un descriptor de archivo
 * @param fd Descriptor de archivo donde escribir (STDIN, STDOUT, STERR)
 * @param buffer Puntero al buffer que contiene los datos a escribir
 * @param count Cantidad de bytes a escribir
 * @return void
 */
void sys_write(uint64_t fd, char * buffer, uint64_t count);

/**
 * @brief Obtiene el valor actual de los segundos del reloj del sistema
 * @param seconds Puntero donde se almacenará el valor de los segundos
 * @return void
 */
void sys_seconds(uint64_t *seconds);

/**
 * @brief Obtiene el valor actual de los minutos del reloj del sistema
 * @param minutes Puntero donde se almacenará el valor de los minutos
 * @return void
 */
void sys_minutes(uint64_t *minutes);

/**
 * @brief Obtiene el valor actual de las horas del reloj del sistema
 * @param hours Puntero donde se almacenará el valor de las horas
 * @return void
 */
void sys_hours(uint64_t *hours);

/**
 * @brief Reproduce un sonido a través del altavoz del sistema
 * @param time Duración del sonido en milisegundos
 * @param frequency Frecuencia del sonido en hertz
 * @return void
 */
void sys_sound(uint64_t time, uint64_t frequency);

#endif