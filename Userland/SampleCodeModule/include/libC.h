// Lectura

/**
 * @brief Lee un carácter desde la entrada estándar
 * @details Bloquea la ejecución hasta que se ingrese un carácter
 * @return char El carácter leído
 */
char readChar();

/**
 * @brief Lee una cadena de texto desde la entrada estándar
 * @param buffer Puntero al buffer donde se almacenará la cadena leída
 * @details Lee caracteres hasta encontrar un salto de línea y maneja teclas especiales
 *          como retroceso y tabulación
 * @return int Número de caracteres leídos, o -1 en caso de error
 */
int scanf(char * buffer);

/**
 * @brief Convierte una cadena de texto a un número entero
 * @param string Cadena de texto que contiene el número a convertir
 * @details Solo procesa dígitos, no maneja signos ni caracteres no numéricos
 * @return int El valor numérico extraído de la cadena
 */
int atoi(char * string);

// Escritura

/**
 * @brief Escribe un carácter en el descriptor de archivo especificado
 * @param c Carácter a escribir
 * @param fd Descriptor de archivo donde escribir (STDIN, STDOUT, STERR)
 * @return void
 */
void putChar(char c, int fd);

/**
 * @brief Escribe una cadena de texto seguida de un salto de línea en la salida estándar
 * @param string Cadena de texto a escribir
 * @return void
 */
void puts(char * string);

/**
 * @brief Escribe una cadena de texto con formato en la salida estándar
 * @param string Cadena de formato que puede contener especificadores como %d, %s, %c
 * @param ... Argumentos variables correspondientes a los especificadores de formato
 * @details Soporta los formatos %d (entero), %s (cadena) y %c (carácter)
 * @return void
 */
void printf(const char * string, ...);

/**
 * @brief Escribe una cadena de texto con un color específico
 * @param string Cadena de texto a escribir
 * @param color Código de color para la cadena
 * @return void
 */
void printColor(char * string, int color);

// Utilidad

/**
 * @brief Obtiene el valor actual de los segundos del reloj del sistema
 * @return int Valor de los segundos (0-59)
 */
int getSecondsUser();

/**
 * @brief Obtiene el valor actual de los minutos del reloj del sistema
 * @return int Valor de los minutos (0-59)
 */
int getMinutesUser();

/**
 * @brief Obtiene el valor actual de las horas del reloj del sistema
 * @return int Valor de las horas (0-23)
 */
int getHoursUser();

/**
 * @brief Calcula la longitud de una cadena de texto
 * @param s Puntero a la cadena cuya longitud se desea calcular
 * @return int Número de caracteres en la cadena (sin incluir el terminador nulo)
 */
int strlen(char * s);

/**
 * @brief Convierte un número entero a su representación en cadena de texto
 * @param num Número entero a convertir
 * @return char* Puntero a la cadena resultante
 */
char * numToString(int num);

/**
 * @brief Compara dos cadenas de texto lexicográficamente
 * @param s1 Primera cadena a comparar
 * @param s2 Segunda cadena a comparar
 * @return int 0 si son iguales, <0 si s1<s2, >0 si s1>s2
 */
int strcmp(const char * s1, const char * s2);

/**
 * @brief Dibuja el cursor en la posición actual
 * @return void
 */
void printCursor();