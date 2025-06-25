#ifndef KERNELLIB_H
#define KERNELLIB_H

#include <stdint.h>

/**
 * @brief Bandera que indica si se debe realizar una captura del estado actual del sistema
 * @details Esta variable se activa cuando el usuario presiona ctrl+r, provocando que el sistema
 *          genere un volcado de los registros y del estado actual
 */
extern char snapShotFlag;

/**
 * @brief Imprime en pantalla el contenido de los registros del procesador
 * @param registers Puntero a un arreglo que contiene los valores de los registros a imprimir
 * @details Muestra en formato legible los valores de los registros del procesador,
 *          incluyendo registros de propósito general, flags y registros especiales
 * @return void
 */
void printRegisters(uint64_t * registers);

#endif // KERNELLIB_H