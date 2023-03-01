void moveBall(double *ballX, double *ballY, double ballAngle);

void ballCalcMapAngle(double *ballAngle);

bool ifVerticalPaddleHit(double ballCordY, int paddleCordY);

bool leftPaddleHit(double ballCordX, double ballCordY, int paddleCordX, int paddleCordY);

bool rightPaddleHit(double ballCordX, double ballCordY, int paddleCordX, int paddleCordY);

void checkEdgeHit(double ballCordY, double* ballAngle);

void checkLeftPaddleHit(double ballCordX, double ballCordY, double* ballAngle, int paddleCordX, int paddleCordY);

void checkRightPaddleHit(double ballCordX, double ballCordY, double* ballAngle, int paddleCordX, int paddleCordY);

void checkPlayerOneScore(int *playerScore, double baCordX, double ballCordY);

void checkPlayerTwoScore(int *playerScore, double baCordX, double ballCordY);