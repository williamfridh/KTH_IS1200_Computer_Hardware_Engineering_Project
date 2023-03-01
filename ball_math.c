#include <stdint.h>
#include <pic32mx.h>
#include <math.h>
#include <stdbool.h>

#define PI 3.141592654



/**
 * Determining the speed of the ball
*/


void moveBall(double *ballX, double *ballY, double ballAngle){
    *ballX += cos(ballAngle);
    *ballY -= sin(ballAngle);                   //-(negative) because of the coordinate system 
    
}





/**
 * If the ball hits the map it will bounce 
 * with 45 degrees
*/

void ballCalcMapAngle(double *ballAngle){
    *ballAngle = (2*PI) - *ballAngle;
}



/**
 * The calculation part of the ball,
 * where it will move when it hits the paddle 
*/



bool leftPaddleHit(double ballCordX, double ballCordY, int paddleCordX, int paddleCordY, int paddleHeight){
    if(ballCordX <= (paddleCordX + 1)){                                                 //Checking if the paddle should hit 
        if((ballCordY >= paddleCordY) && (ballCordY <= (paddleCordY + 8))){
            return true;
        }
    }
    else{
        return false;
    }
}



bool rightPaddleHit(double ballCordX, double ballCordY, int paddleCordX, int paddleCordY, int paddleHeight){
    if(ballCordX >= (paddleCordX - 1)){                                                  //Checking if the paddle should hit 
        if((ballCordY <= paddleCordY) && ballCordY >= (paddleCordY + paddleHeight)){     //Checks if the ball hits the paddle on the height
            return true;
        }
    }
    else{
        return false;
    }
}

/**
 * 
*/

void ballHitCalc(double ballCordX, double ballCordY, double* ballAngle, int paddleCordX, int paddleCordY, int paddleHeight){

    double hitY = (ballCordY - paddleCordY)/paddleHeight;     //Checks where the ball hits the paddle 

    if (hitY = 0){                                            //Center hit 
        *ballAngle += PI;    
    }

    else if(hitY < 0){                                        //Upper hit 
        *ballAngle = PI * (-hitY);
    }             

    else if(hitY > 0){                                        //Lower hit
        *ballAngle = 2*PI - PI*hitY;
    }            
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
*/


void checkBallHit(double ballCordX, double ballCordY, double* ballAngle, int paddleCordX, int paddleCordY){  
    /*
    if(ballCordY <= 2 || ballCordY >= 28){                                                   //Boundaries for the arena
        ballCalcMapAngle(ballAngle);
    }
    */
    
   if(leftPaddleHit(ballCordX, ballCordY, paddleCordX, paddleCordY, 8)){               // 8 = the paddle pixel height         
        //ballHitCalc(ballCordX, ballCordY, ballAngle, paddleCordX, paddleCordY, 8);
            *ballAngle = (2*PI);

    }

     

/*
    else if(rightPaddleHit(ballCordX, ballCordY, paddleCordX, paddleCordY, 8)){             
        ballHitCalc(ballCordX, ballCordY, ballAngle, paddleCordX, paddleCordY, 8);
    }
*/
}




void checkPlayerOneScore(int *playerScore, int ballCordX){
    if(ballCordX == 0){
        (*playerScore)++;
    }
}



void checkPlayerTwoScore(int *playerScore, int ballCordX){
    if(ballCordX == 128){
        (*playerScore)++;
    }
}
