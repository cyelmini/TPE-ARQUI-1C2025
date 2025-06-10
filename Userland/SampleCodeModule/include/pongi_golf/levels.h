typedef struct Ball * TBall;
typedef struct Obstacle * TObstacle;
typedef struct Hole * THole;
typedef struct Pongi * TPongi;

/**
 * @brief Configura un nivel específico del juego
 * @param level Número de nivel a configurar
 * @param pongi Arreglo de pongis a posicionar
 * @param ball Pelota a posicionar
 * @param hole Hoyo a posicionar
 * @param obstacles Arreglo de obstáculos a configurar
 * @details Establece las posiciones iniciales de todos los elementos del juego según el nivel
 * @return void
 */
void setLevel(int level, TPongi pongi[], TBall ball, THole hole, TObstacle obstacles[]);