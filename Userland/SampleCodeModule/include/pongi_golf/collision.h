/**
 * @brief Verifica colisión entre dos círculos
 * @param x1 Coordenada x del centro del primer círculo
 * @param y1 Coordenada y del centro del primer círculo
 * @param r1 Radio del primer círculo
 * @param x2 Coordenada x del centro del segundo círculo
 * @param y2 Coordenada y del centro del segundo círculo
 * @param r2 Radio del segundo círculo
 * @return int 1 si hay colisión, 0 en caso contrario
 */
int checkCirclesCollision(int x1, int y1, int r1, int x2, int y2, int r2);

/**
 * @brief Verifica colisión entre un rectángulo y un círculo
 * @param x1 Coordenada x de la esquina superior izquierda del rectángulo
 * @param y1 Coordenada y de la esquina superior izquierda del rectángulo
 * @param height1 Altura del rectángulo
 * @param width1 Ancho del rectángulo
 * @param x2 Coordenada x del centro del círculo
 * @param y2 Coordenada y del centro del círculo
 * @param r1 Radio del círculo
 * @return int 1 si hay colisión, 0 en caso contrario
 */
int checkRectangleCircleCollision(int x1, int y1, int height1, int width1, int x2, int y2, int r1);