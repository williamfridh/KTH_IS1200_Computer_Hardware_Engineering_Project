/**
 * @author Åhlin, Pontus
*/
void moveBall(double *ballX, double *ballY, double ballAngle);

void checkEdgeHit(double ballCordY, double* ballAngle);

void checkLeftPaddleHit(double ballCordX, double ballCordY, double* ballAngle, int paddleCordX, int paddleCordY);

void checkRightPaddleHit(double ballCordX, double ballCordY, double* ballAngle, int paddleCordX, int paddleCordY);

void checkPlayerScore(int *playerOneScore, int* playerTwoScore, double ballCordX);

