/**
 * @brief Estructura que representa un jugador (Pongi) en el juego
 * @details Contiene las coordenadas, puntuación y color del jugador
 */
typedef struct Pongi {
    int x;      /**< Coordenada x del pongi */
    int y;      /**< Coordenada y del pongi */
    int points; /**< Puntuación del jugador */
    int color;  /**< Color del pongi en formato RGB */
}Pongi;

#define PONGI_SPEED 7     /**< Velocidad de movimiento del pongi */
#define PONGI_RADIUS 18   /**< Radio del pongi (tamaño) */

typedef struct Ball * TBall;
typedef struct Obstacle * TObstacle;
typedef struct Hole * THole;
typedef struct Pongi * TPongi;

/**
 * @brief Crea un nuevo pongi (jugador)
 * @param x Coordenada x inicial del pongi
 * @param y Coordenada y inicial del pongi
 * @param color Color del pongi en formato RGB
 * @return TPongi Puntero al nuevo pongi creado
 */
TPongi createPongi(int x, int y, int color);

/**
 * @brief Mueve los pongis según la dirección especificada
 * @param pongis Arreglo de pongis a mover
 * @param dmove Arreglo con el desplazamiento [dx, dy, jugador]
 * @param obstacles Arreglo de obstáculos del nivel
 * @param ball Pelota del juego
 * @param hole Hoyo objetivo del nivel
 * @return void
 */
void movePongis(TPongi pongis[], int dmove[3], TObstacle obstacles[], TBall ball, THole hole);

/**
 * @brief Dibuja todos los pongis en la pantalla
 * @param pongis Arreglo de pongis a dibujar
 * @return void
 */
void printPongis(TPongi pongis[]);