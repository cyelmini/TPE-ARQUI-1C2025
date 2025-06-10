#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

/**
 * @brief Genera intencionalmente una excepción de división por cero
 * @details Esta función provoca una división por cero para probar el manejo
 *          de excepciones del sistema. Cuando se llama, el procesador
 *          generará una excepción de tipo #DE (Divide Error).
 * @return void
 */
extern void divisionByZero(void);

/**
 * @brief Genera intencionalmente una excepción de código de operación inválido
 * @details Esta función ejecuta una instrucción inválida para probar el manejo
 *          de excepciones del sistema. Cuando se llama, el procesador
 *          generará una excepción de tipo #UD (Invalid Opcode).
 * @return void
 */
extern void invalidOpCode(void);

#endif // EXCEPTIONS_H