#ifndef KERNEL_H
#define KERNEL_H

/**
 * @brief Obtiene la dirección base de la pila (stack) del sistema.
 * @return void* Puntero a la base de la pila.
 */
void * getStackBase();

/**
 * @brief Devuelve el control al espacio de usuario (userland).
 * @return void* Puntero de retorno al userland.
 */
void * retUserland();

#endif // KERNEL_H