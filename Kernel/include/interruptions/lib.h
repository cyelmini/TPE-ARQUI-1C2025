#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

char * cpuVendor(char *result);

/**
 * @brief Obtiene los segundos actuales del reloj del sistema
 * @return int Segundos actuales (0-59)
 */
extern int getSeconds();

/**
 * @brief Obtiene los minutos actuales del reloj del sistema
 * @return int Minutos actuales (0-59)
 */
extern int getMinutes();

/**
 * @brief Obtiene las horas actuales del reloj del sistema
 * @return int Horas actuales (0-23)
 */
extern int getHours();

/**
 * @brief Genera un sonido de la frecuencia especificada
 * @param frequency Frecuencia en Hz
 * @return void
 */
extern void makeSound(int64_t frequency);

/**
 * @brief Detiene cualquier sonido que se esté reproduciendo
 * @return void
 */
extern void stopSound();

#endif