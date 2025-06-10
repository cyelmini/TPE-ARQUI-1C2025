#define BALL_RADIUS 10

/**
 * @brief Estructura que representa una pelota en el juego
 * @details Contiene las coordenadas, velocidad y color de la pelota
 */
typedef struct Ball {
    int x;          /**< Coordenada x de la pelota */
    int y;          /**< Coordenada y de la pelota */
    int moveSpeed;  /**< Velocidad de movimiento de la pelota */
    int color;      /**< Color de la pelota en formato RGB */
}Ball;

typedef struct Ball * TBall;
typedef struct Obstacle * TObstacle;
typedef struct Hole * THole;
typedef struct Pongi * TPongi;

/**
 * @brief Crea una nueva pelota
 * @param x Coordenada x inicial de la pelota
 * @param y Coordenada y inicial de la pelota
 * @param color Color de la pelota en formato RGB
 * @return TBall Puntero a la nueva pelota creada
 */
TBall createBall(int x, int y, int color);

/**
 * @brief Mueve la pelota en la dirección especificada
 * @param ball Puntero a la pelota a mover
 * @param dmove Arreglo con el desplazamiento [dx, dy, jugador]
 * @param obstacles Arreglo de obstáculos del nivel
 * @param pongis Arreglo de jugadores
 * @param hole Hoyo objetivo del nivel
 * @return void
 */
void moveBall(TBall ball, int dmove[3], TObstacle obstacles[], TPongi pongis[], THole hole);

/**
 * @brief Verifica si hay colisión entre la pelota y un pongi
 * @param ball Puntero a la pelota
 * @param pongi Puntero al pongi
 * @param dmove Arreglo con el desplazamiento [dx, dy, jugador]
 * @return int 1 si hay colisión, 0 en caso contrario
 */
int checkBallCollision(TBall ball, TPongi pongi, int dmove[3]);

/**
 * @brief Dibuja la pelota en la pantalla
 * @param ball Puntero a la pelota a dibujar
 * @return void
 */
void printBall(TBall ball);