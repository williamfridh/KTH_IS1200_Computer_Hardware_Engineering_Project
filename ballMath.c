/**
 * Include Libraries & Declare Values
*/
#include <stdio.h>
#include <stdint.h>
#include <pic32mx.h>
#include <math.h>
#include <stdbool.h>
#include "game.h"
#include "basicFunctions.h"
#include "config.h"




/**
 * Determining the speed of the ball
 *
 * @param {double} ballX The x-coordinate of the ball
 * @param {double} ballY The y-coordinate of the ball
 * @param {double} ballAngle The angle of the ball

 * @author Åhlin, Pontus
*/
void moveBall(double *ballX, double *ballY, double ballAngle){
    *ballX += cos(ballAngle);
    *ballY -= sin(ballAngle);                                    //-(negative) because of the coordinate system   
}




/**
 * Caclculate new Angle Of Edge Hit
 * 
 * If the ball hits the map it will bounce 
 * with 45 degrees.
 * 
 * @param {double} ball angle
 *
 * @author Åhlin, Pontus
*/
void ballCalcMapAngle(double *ballAngle){
    *ballAngle = (2*PI) - *ballAngle;
}



/**
 * If Ball Hits Paddle In Y Axis
 * @param {double} - ball angle in rads
 * @param {double} - ball paddle y cordinate
 *
 * @author Åhlin, Pontus
*/
bool ifVerticalPaddleHit(double ballCordY, int paddleCordY) {
    return (nearbyint(ballCordY) >= paddleCordY-1) && nearbyint(ballCordY) <= (paddleCordY + PADDLE_HEIGHT);
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
    if (ballCordY <= 2 || ballCordY >= 28) {                // Boundaries for the arena
        ballCalcMapAngle(ballAngle);
    }
}



/**
 * Calculate A Hit Y
 * 
 * A Hit Y is a value [0, 1] that is represents where
 * on the paddle the ball hit. The value is used for
 * determining what type of calculations to take next
 * and will later be sent to scaleHitY or similar function.
 * 
 * @param {double} ball y cordinate
 * @param {int} paddle y cordinate
 * 
 * @return {double} calculated value
 * 
 * @author Fridh, William
*/
double calcHitY(double ballCordY, int paddleCordY) {
    return (ballCordY - paddleCordY+1)/PADDLE_HEIGHT;
}



/**
 * Calculate Scaled Hit Y
 * 
 * Returns a scaled value from the formula 2t^2-2t+0.5
 * This is used for a exponentail angle change
 * towards the edges of the paddles.
 * 
 * @param {double} value to recalculate
 * 
 * @return {double} recalculated value [0, 0.5]
 * 
 * @author Fridh, William
*/
double scaleHitY(double t) {
    return 2*t*t-2*t+0.5;
}


/**
 * This function checks whether the left paddle is hit,
 * and if it is it calls on other functions that 
 * calculates the trajectory of the ball
 * 
 * @param {double} ballCordX - The current x-coordinate of the ball
 * @param {double} ballCordY - The current y-coordinate of the ball
 * @param {double} ballAngle - Pointer that points to the angle of the ball
 * @param {int} paddleCordX - The current paddle x-coordinate
 * @param {int} paddleCordY - The current paddle y-coordinate
 *
 * @authors Åhlin, Pontus & Fridh, William
*/

void checkLeftPaddleHit(double ballCordX, double ballCordY, double* ballAngle, int paddleCordX, int paddleCordY){  
    if (ifVerticalPaddleHit(ballCordY, paddleCordY) && (ballCordX < (paddleCordX + 2))) { 
        double hitY = calcHitY(ballCordY, paddleCordY);                          //Checks where the ball hits the paddle 
        if (hitY == 0.5) {                                                      //Center hit 
            *ballAngle = 0;    
        } else if (hitY < 0.5) {                                                //Upper hit 
            *ballAngle = NEAR_PI * scaleHitY(hitY);
        } else if (hitY > 0.5) {                                                //Lower hit   
            *ballAngle = 2*PI - scaleHitY(hitY)*NEAR_PI;
        }        
    }   
}



/**
 * This function checks whether the right paddle is hit,
 * and if it is it calls on other functions that 
 * calculates the trajectory of the ball
 * 
 * @param ballCordX - The current x-coordinate of the ball
 * @param ballCordY - The current y-coordinate of the ball
 * @param ballAngle - Pointer that points to the angle of the ball
 * @param paddleCordX - The current paddle x-coordinate
 * @param paddleCordY - The current paddle y-coordinate
 *
 * @authors Åhlin, Pontus & Fridh, William
*/

void checkRightPaddleHit(double ballCordX, double ballCordY, double* ballAngle, int paddleCordX, int paddleCordY){  
    if(ifVerticalPaddleHit(ballCordY, paddleCordY) && (ballCordX >= (paddleCordX - 1))){                              
        double hitY = calcHitY(ballCordY, paddleCordY);                  //Checks where the ball hits the paddle 
        if (hitY == 0.5){                                             //Center hit 
            *ballAngle = PI;    
        } else if(hitY < 0.5){                                        //Upper hit 
            *ballAngle = PI - NEAR_PI * scaleHitY(hitY);
        } else if(hitY > 0.5){                                        //Lower hit   
            *ballAngle = PI + scaleHitY(hitY)*NEAR_PI;
        }        
    }
}



/**
 * Check Player Score
 * 
 * Checks if the ball is in any of the players goal.
 * If so, it increases the correct players score
 * and calls for a reset of the arena.
 * 
 * @param {int} player one score
 * @param {int} player two score
 * @param {doube} ball x cordinate
 * 
 * @author Åhlin, Pontus
*/
void checkPlayerScore(int *playerOneScore, int* playerTwoScore, double ballCordX) {
    if (ballCordX > 127.0) {                //127.0 = Goal boundary
        (*playerOneScore)++;                //Points to the player score, increments the value where it is pointing 
        resetArena();
    }
    if (ballCordX < 0.0) {
        (*playerTwoScore)++;
        resetArena();
    }
}




