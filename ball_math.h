void moveBall(double *ballX, double *ballY, double ballAngle);

void ballCalcMapAngle(double *ballAngle);

bool ballHit(double ballCordX, double ballCordY, int paddleCordX, int paddleCordY, int paddleHeight);

void ballHitCalc(double ballCordX, double ballCordY, double* ballAngle, int paddleCordX, int paddleCordY, int paddleHeight);

void checkBallHit(double ballCordX, double ballCordY, double* ballAngle, int paddleCordX, int paddleCordY);

void playerScore(int player, int ballCordX);