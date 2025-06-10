#ifndef _TIME_H_
#define _TIME_H_

/**
 * @brief Manejador de la interrupción del temporizador
 * @details Se ejecuta cada vez que ocurre una interrupción del temporizador del sistema,
 *          incrementa un contador interno de ticks y realiza tareas programadas por tiempo.
 *          Esta función es llamada automáticamente por el sistema de interrupciones
 *          aproximadamente 18 veces por segundo.
 * @return void
 */
void timer_handler();

/**
 * @brief Obtiene la cantidad de ticks transcurridos desde el inicio del sistema
 * @details Cada tick representa aproximadamente 1/18 de segundo
 * @return int Número de ticks transcurridos
 */
int ticks_elapsed();

/**
 * @brief Obtiene la cantidad de segundos transcurridos desde el inicio del sistema
 * @details Calcula los segundos dividiendo los ticks entre 18 (frecuencia del timer)
 * @return int Número de segundos transcurridos
 */
int seconds_elapsed();

/**
 * @brief Pausa la ejecución durante un número específico de segundos
 * @param seconds Cantidad de segundos que se debe pausar la ejecución
 * @details Utiliza la función _hlt() para detener el procesador hasta la próxima interrupción
 * @return void
 */
void sleep(int seconds);

/**
 * @brief Pausa la ejecución durante un número específico de milisegundos
 * @param milliseconds Cantidad de milisegundos que se debe pausar la ejecución
 * @details Convierte los milisegundos a ticks (18 ticks/segundo) y pausa la ejecución
 *          utilizando _hlt() hasta que transcurra el tiempo especificado
 * @return void
 */
void sleep_ms(int milliseconds);

#endif