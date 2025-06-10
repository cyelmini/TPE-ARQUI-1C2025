#ifndef SHELL_H
#define SHELL_H

/**
 * @brief Inicializa la shell del sistema
 * @details Muestra un mensaje de bienvenida y comienza a recibir comandos del usuario
 * @return void
 */
void initializeShell();

/**
 * @brief Escanea continuamente la entrada del usuario
 * @details Muestra el prompt del sistema y lee los comandos ingresados por el usuario
 * @return void
 */
void scanEntry();

/**
 * @brief Procesa la entrada del usuario y ejecuta el comando correspondiente
 * @param entry Cadena de texto con el comando ingresado por el usuario
 * @details Separa el comando de sus argumentos y llama a la función apropiada
 * @return void
 */
void entryHandler(char * entry);

/**
 * @brief Muestra los valores actuales de los registros del procesador
 * @details Realiza una llamada al sistema para obtener y mostrar el estado
 *          de todos los registros del CPU en formato legible
 * @return void
 */
void printRegisters();

/**
 * @brief Muestra información sobre los comandos disponibles
 * @details Si se llama sin argumentos, muestra la lista de todos los comandos.
 *          Si se proporciona un comando como argumento, muestra información
 *          detallada sobre ese comando específico
 * @param command Comando opcional sobre el cual mostrar información detallada
 * @return void
 */
void help(char *command);

/**
 * @brief Muestra la hora actual del sistema
 * @details Obtiene la hora, minutos y segundos del reloj del sistema
 *          y los muestra en formato HH:MM:SS
 * @return void
 */
void time();

/**
 * @brief Inicia el juego de golf
 * @details Lanza la aplicación de golf, cambiando el modo de pantalla
 *          y transfiriendo el control al juego
 * @return void
 */
void playGolf();

/**
 * @brief Ejecuta un comando con sus argumentos
 * @param command Comando a ejecutar
 * @param arg Argumentos para el comando
 * @details Identifica el comando solicitado y llama a la función correspondiente
 * @return void
 */
void executeCommand(char * command, char * arg);

/**
 * @brief Limpia la pantalla de la terminal
 * @details Realiza una llamada al sistema para borrar todo el contenido de la pantalla
 *          y reposicionar el cursor en la parte superior
 * @return void
 */
void clearScreen();

#endif // SHELL_H