#include <stdint.h>
#include <pic32mx.h>
#include <math.h>
#include <stdbool.h>



/**
 * Determining the speed of the ball,
 * will most likely depend on the timers
*/

void xBallSpeed(int ballX){   
    ballX = ballX + 1;                        //Ball will move 1 pixel each tick
}


void yBallSpeed(int ballY){
    ballY = ballY + 1;
}



/**
 * If the ball hits the map
*/

void ballCalcMapTop(int ballY){
    ballY = (270 - ballY) + 270;             //Flip the value of the y direction. 
}

void ballCalcMapBot(int ballY){
    ballY = 360 - ballY;
}



/**
 * The calculation part of the ball,
 * where it will move when it hits the paddle 
*/

void ballCalcPaddle(int ballX){
    if(ballX < 90 & ballX > -90){
        ballX = ballX + 180;
    }
    else{
        ballX = ballX - 180;
    }
}



/**
 * Determining what the ball hits, either
 * the map, paddle or score. 
 * 
 * @param ballCordX
 * 
 * @param ballCordY
 * 
 * @param player - 
*/

void ballHit(int ballCordX, int ballCordY, int ballAngle, int paddleCordX, int paddleCordY){  

    if(ballCordY = 128){
        ballCalcMapTop(ballCordY);
    }

    if(ballCordY = 0){
        ballCalcMapBot(ballCordY);
    }

    if((ballCordX = paddleCordX) & (ballCordY = paddleCordY)){
        ballCalcPaddle(ballAngle);
    }
}




void playerScore(int player, int ballCordX){
    if(ballCordX == 0 | ballCordX == 128){
        player++;
    }
}






