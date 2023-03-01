/**
 * Include Libraries & Declare Values
*/
#include <stdio.h>
#include <stdint.h>
#include <pic32mx.h>
#include <math.h>
#include <stdbool.h>

#define PI 3.141592654
#define PADDLE_HEIGHT 8.0
#define NEAR_PI (17*PI)/18



/**
 * Determining the speed of the ball
 
 * @author Åhlin, Pontus
*/
void moveBall(double *ballX, double *ballY, double ballAngle){
    *ballX += cos(ballAngle);
    *ballY -= sin(ballAngle);                   //-(negative) because of the coordinate system   
}



/**
 * If the ball hits the map it will bounce 
 * with 45 degrees
 *
 * @author Åhlin, Pontus
*/
void ballCalcMapAngle(double *ballAngle){
    *ballAngle = (2*PI) - *ballAngle;
}



/**
 * If Ball Hits Paddle In Y Axis
 * @param {double}  - ball angle in rads
 * @param {double}  - ball paddle y cordinate
 *
 * @author Åhlin, Pontus
*/
bool ifVerticalPaddleHit(double ballCordY, int paddleCordY) {
    return (nearbyint(ballCordY) >= paddleCordY-1) && nearbyint(ballCordY) <= (paddleCordY + PADDLE_HEIGHT+1);
}



/**
 * Determining what the ball hits, either
 * the map, paddle or score. And if it hits, 
 * call on function that calucates the outcome
 * 
 * @param ballCordX - The current x-coordinate of the ball
 * @param ballCordY - The current y-coordinate of the ball
 * @param ballAngle - Pointer that points to the angle of the ball
 * @param paddleCordX - The current paddle x-coordinate
 * @param paddleCordY - The current paddle y-coordinate
 *
 * @authot Åhlins, Pontus 
*/
void checkEdgeHit(double ballCordY, double *ballAngle) {
    if (ballCordY <= 2 || ballCordY >= 28) {                                                   //Boundaries for the arena
        ballCalcMapAngle(ballAngle);
    }
}   
// 0-1
double calcHitY(double ballCordY, int paddleCordY) {
    double t = (ballCordY - paddleCordY)/PADDLE_HEIGHT;
    return 4*t*t-4*t+1;
}

void checkLeftPaddleHit(double ballCordX, double ballCordY, double* ballAngle, int paddleCordX, int paddleCordY){  
    if (ifVerticalPaddleHit(ballCordY, paddleCordY) && (ballCordX < (paddleCordX + 2))) { 
        double hitY = calcHitY(ballCordY, paddleCordY);                          //Checks where the ball hits the paddle 
        if (hitY == 0.5) {                                                      //Center hit 
            *ballAngle += PI;    
        } else if (hitY < 0.5) {                                                //Upper hit 
            *ballAngle = NEAR_PI * (0.5-hitY);
        } else if (hitY > 0.5) {                                                //Lower hit   
            *ballAngle = 2*PI + (0.5-hitY)*NEAR_PI;
        }        
    }
}

void checkRightPaddleHit(double ballCordX, double ballCordY, double* ballAngle, int paddleCordX, int paddleCordY){  
    if(ifVerticalPaddleHit(ballCordY, paddleCordY) && (ballCordX >= (paddleCordX - 1))){                              
        double hitY = calcHitY(ballCordY, paddleCordY);                  //Checks where the ball hits the paddle 
        if (hitY == 0.5){                                            //Center hit 
            *ballAngle += PI;    
        } else if(hitY < 0.5){                                        //Upper hit 
            *ballAngle = PI - NEAR_PI * (0.5-hitY);
        } else if(hitY > 0.5){                                        //Lower hit   
            *ballAngle = PI + (hitY)*NEAR_PI;
        }        
    }
}




/*


void checkPlayerOneScore(int *playerScore, double ballCordX, double ballCordY){
    if(ballCordX == 0){
        (*playerScore)++;
        ballCordY = 16;
        ballCordX = 64;
    }
}



void checkPlayerTwoScore(int *playerScore, double ballCordX, double ballCordY){
    if(ballCordX == 128){
        (*playerScore)++;
        ballCordY = 16;
        ballCordX = 64;

    }
}
*/