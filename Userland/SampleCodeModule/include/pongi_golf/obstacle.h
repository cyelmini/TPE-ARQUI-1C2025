#define MAX_OBSTACLES 13   /**< Número máximo de obstáculos por nivel */

/**
 * @brief Estructura que representa un obstáculo en el juego
 * @details Contiene las coordenadas, color, altura y ancho del obstáculo
 */
typedef struct Obstacle {
    int x;      /**< Coordenada x del obstáculo */
    int y;      /**< Coordenada y del obstáculo */
    int color;  /**< Color del obstáculo en formato RGB */
    int height; /**< Altura del obstáculo */
    int width;  /**< Ancho del obstáculo */
}Obstacle;

typedef struct Ball * TBall;
typedef struct Obstacle * TObstacle;
typedef struct Hole * THole;
typedef struct Pongi * TPongi;

/**
 * @brief Crea un nuevo obstáculo
 * @param x Coordenada x del obstáculo
 * @param y Coordenada y del obstáculo
 * @param color Color del obstáculo en formato RGB
 * @param height Altura del obstáculo
 * @param width Ancho del obstáculo
 * @return TObstacle Puntero al nuevo obstáculo creado
 */
TObstacle createObstacle(int x, int y, int color, int height, int width);

/**
 * @brief Verifica si hay colisión entre un pongi y los obstáculos
 * @param pongi Puntero al pongi
 * @param dmove Arreglo con el desplazamiento [dx, dy, jugador]
 * @param obstacles Arreglo de obstáculos a verificar
 * @return int 1 si hay colisión, 0 en caso contrario
 */
int checkPongiObstacleCollision(TPongi pongi, int dmove[3], TObstacle obstacles[]);

/**
 * @brief Verifica si hay colisión entre la pelota y los obstáculos
 * @param ball Puntero a la pelota
 * @param dmove Arreglo con el desplazamiento [dx, dy, jugador]
 * @param obstacles Arreglo de obstáculos a verificar
 * @return int 1 si hay colisión, 0 en caso contrario
 */
int checkBallObstacleCollision(TBall ball, int dmove[3], TObstacle obstacles[]);

/**
 * @brief Dibuja todos los obstáculos en la pantalla
 * @param obstacles Arreglo de obstáculos a dibujar
 * @return void
 */
void printObstacles(TObstacle obstacles[]);