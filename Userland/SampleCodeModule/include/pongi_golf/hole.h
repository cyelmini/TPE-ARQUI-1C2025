/**
 * @brief Estructura que representa el hoyo (objetivo) en el juego
 * @details Contiene las coordenadas y tamaño del hoyo
 */
typedef struct Hole {
    int x;      /**< Coordenada x del hoyo */
    int y;      /**< Coordenada y del hoyo */
    int size;   /**< Tamaño (radio) del hoyo */
}Hole;

typedef struct Ball * TBall;
typedef struct Obstacle * TObstacle;
typedef struct Hole * THole;
typedef struct Pongi * TPongi;

#define HOLE_COLOR 0x000000   /**< Color negro para el hoyo */

/**
 * @brief Crea un nuevo hoyo
 * @param x Coordenada x del hoyo
 * @param y Coordenada y del hoyo
 * @param size Tamaño (radio) del hoyo
 * @return THole Puntero al nuevo hoyo creado
 */
THole createHole(int x, int y, int size);

/**
 * @brief Verifica si la pelota ha entrado en el hoyo (nivel completado)
 * @param ball Puntero a la pelota
 * @param hole Puntero al hoyo
 * @return int 1 si la pelota está en el hoyo, 0 en caso contrario
 */
int wonLevel(TBall ball, THole hole);

/**
 * @brief Dibuja el hoyo en la pantalla
 * @param hole Puntero al hoyo a dibujar
 * @return void
 */
void printHole(THole hole);