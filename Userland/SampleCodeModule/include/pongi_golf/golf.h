/**
 * @brief Definición de colores básicos para el juego
 */
#define WHITE 0xFFFFFF     /**< Color blanco */
#define BLACK 0x000000     /**< Color negro */
#define RED   0xFF0000     /**< Color rojo */
#define GREEN 0x62bc2f     /**< Color verde (césped) */
#define BLUE  0x0000FF     /**< Color azul */
#define PONGI_BLUE 0x1b72ae /**< Color azul para el pongi */
#define PONGI_RED 0xFF0000  /**< Color rojo para el pongi */
#define BROWN 0x5d441d    /**< Color marrón para obstáculos */
#define HOLE_COLOR 0x000000 /**< Color negro para el hoyo */

#define NULL 0             /**< Valor nulo para punteros */

/**
 * @brief Inicializa y ejecuta el juego de golf
 * @details Muestra el menú principal, configura los jugadores y comienza el bucle principal del juego
 * @return void
 */
void initializeGolf();