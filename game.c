/**
 * Include Libraries & Models & Declare Global Variables
*/
#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "canvas.h"
#include "shieldDisplay.h"
#include "ballMath.h"

#include "model/ball.c"
#include "model/map.c"
#include "model/paddle.c"

#define PI 3.141592654
#define PADDLE_HEIGHT 8.0



/*
Global values
Global values that holds data of the players and the balls position.
Aswell as the score of the player. 
*/
int paddleX1;			//The initial positions of the padels. and the ball
int paddleY1;
int paddleX2;
int paddleY2;

double ballX;
double ballY;
double ballAngle = PI;		//Made with RADS

int playerOneScore;
int playerTwoScore;

int difficulty = 0;				//The difficulty will range from 0-2, where 0 is easiest.



/*
Checks which button is pressed and if it is pressed
trigger a certain action, in this case either make the 
player go down or up
*/
void paintArena() {
	canvasInsertModel(paddleX1, paddleY1, 2, 8, model_paddle, false);		//The left side padel 
	canvasInsertModel(paddleX2, paddleY2, 2, 8, model_paddle, false);		//The right side padel 

	canvasInsertModel(0, 0, 128, 32, model_map, true);					//The map
	canvasInsertModel(ballX, ballY, 2, 2, model_ball, true);			//The ball
}



/**
 * This function determines if the paddle will move up or down.
 * The function also makes bounderies for the padels.
 * @param pos			- Current position of padel 
 * @param direction 	- The direction where the padel is going 
 * 
*/

bool upOrDown(int pos, int direction) {
	int newPos = pos + direction;
		if(newPos < 24 & newPos > 0){
			return true; 
		}
	return false;
}



/**
 * This function is called from main, continuously, that checks 
 * whether a button is pressed or not. 
 * @param buttonData	- 
*/

void gameButtonTriggered(int buttonData) {

	if(buttonData & 0x8 && upOrDown(paddleY1, 1)){
		paddleY1++;
	}

	if(buttonData & 0x4 && upOrDown(paddleY1, -1)){
		paddleY1--;
	}
	
	if(buttonData & 0x2 && upOrDown(paddleY2, 1)){
		paddleY2++;
	}

	if(buttonData & 0x1 && upOrDown(paddleY2, -1)){
		paddleY2--;
	}
}



/**
 * Functions from ball_math.h is called to here
*/

void playingGame() {

	//ballHit(ballX, ballY, ballAngle, paddleX1, paddleY1);		//Check player 1 paddle hit 
	//ballHit(ballX, ballY, ballAngle, paddleX2, paddleY2);		//Check player 2 paddle hit
	//checkPlayerOneScore(playerOneScore, ballX);
	//checkPlayerTwoScore(playerTwoScore, ballX);


}



/** 
* Resets the arena
*
* Resets the ball and paddles
* to thier starting positions
* 
* @author Åhlin, Pontus
*/

void resetArena() {
    ballY = 16;
    ballX = 64;
    paddleX1 = 4;			//The initial positions of the padels. and the ball
    paddleY1 = 16;
    paddleX2 = 122;
    paddleY2 = 16;
}


/**
 * initializes the paddles, arena when
 * starting the game 
 * 
 * @author Åhlin, Pontus
*/

void initArena() {
	resetArena();
	playerOneScore = 0;
	playerTwoScore = 0;
	
}


/**
 * The function that main calls when we want to load in
 * the game state.
*/
void renderGame(){
		canvasClear();															//Clear the menu 
		moveBall(&ballX, &ballY, ballAngle);
		paintArena();															//Paint the arena 	
		checkEdgeHit(ballY, &ballAngle);		
		checkLeftPaddleHit(ballX, ballY, &ballAngle, paddleX1, paddleY1);		//Check player 1 paddle hit 
		checkRightPaddleHit(ballX, ballY, &ballAngle, paddleX2, paddleY2);		//Check player 2 paddle hit 
		checkPlayerScore(&playerOneScore, &playerTwoScore, ballX);


		const uint8_t* canvas_data = canvasGetData();				//Get the data from the canvas
  		sendDisplayData(canvas_data);								//Sending that data to the OLED display
}


/**
 * Get Player One Score
 * 
 * @return {int} score
 * 
 * @author Åhlin, Pontus
*/
int getPlayerOneScore(void) {
	return playerOneScore;
}



/**
 * Get Player Two Score
 * 
 * @return {int} score
 * 
 * @author Åhlin, Pontus
*/
int getPlayerTwoScore(void) {
	return playerOneScore;
}



/**
 * Get Difficulty Level
 * 
 * @return {int} difficulty level
 * 
 * @author Åhlin, Pontus
*/
int getDifficultySetting(void) {
	return difficulty; 
}



/**
 * Toggle Difficulty Settings
 * 
 * @author Fridh, William
*/
void toggleDifficultySetting() {
	difficulty++;
	if (difficulty==3) difficulty = 0;
}

