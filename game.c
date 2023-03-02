/**
 * Include Libraries & Models & Declare Global Variables
*/
#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "canvas.h"
#include "shieldDisplay.h"
#include "basicFunctions.h"
#include "ballMath.h"
#include "menu.h"
#include "main.h"
#include "config.h"

#include "model/ball.c"
#include "model/map.c"
#include "model/paddle.c"



/**
 * Global values
 * Global values that holds data of the players and the balls position.
 * Aswell as the score of the player. 
*/

int paddleX1;			//The initial positions of the padels. and the ball
int paddleY1;
int paddleX2;
int paddleY2;

double ballX;
double ballY;
double ballAngle = 0;		//Made with RADS

int playerOneScore;
int playerTwoScore;

int difficulty = 0;				//The difficulty will range from 0-2, where 0 is easiest.

bool pvpMode;				// true means it is pvp



/**
 * Prints the current score of the players
 * on the screen 
 *
 * @param {int} playerOneScore	The current score of player one 
 * @param {int} playerTwoScore	The current score of player two 
 *
 * @author Åhlin, Pontus
*/

void printPlayerScore(int playerOneScore, int playerTwoScore){

	int ascii1 = playerOneScore + 48;	//+ 48 because we want the ascii value in decimal (48 = 0)
	int ascii2 = playerTwoScore + 48;	//+ 48 because somehow when 

	char * p1 = (char*)&ascii1;			
	char * p2 = (char*)&ascii2;					//Here, we explicitly tell the compiler that we want the integer address to be treated
												// as an address to a character which is legal in C.
	canvasWrite(p1, 48, 2, false, false);			//Player one score 
	canvasWrite(p2, 80, 2, false, false);			//Player two score 
}



/**
 * Checks which button is pressed and if it is pressed
 * trigger a certain action, in this case either make the 
 * player go down or up
 *
 * @author Åhlin, Pontus
*/

void paintArena() {
	canvasInsertModel(paddleX1, paddleY1, 2, 8, model_paddle, false);		//The left side padel 
	canvasInsertModel(paddleX2, paddleY2, 2, 8, model_paddle, false);		//The right side padel 

	canvasInsertModel(0, 0, 128, 32, model_map, true);					//The map
	canvasInsertModel(ballX, ballY, 2, 2, model_ball, true);			//The ball

	printPlayerScore(playerOneScore, playerTwoScore);
}



/**
 * This function determines if the paddle will move up or down.
 * The function also makes bounderies for the padels.
 * @param pos			- Current position of padel 
 * @param direction 	- The direction where the padel is going 
 * 
 * @author Åhlin, Pontus
*/

bool upOrDown(int pos, int direction) {
	int newPos = pos + direction;
		if(newPos < 24 & newPos > 0){			
			return true; 
		}
	return false;
}



/**
 * This is a very easy Ai that 
 * moves the way of the ball
 *
 * @param {int} offset Where the ai paddle should hit the ball in the Y-axis 
 *
 * @param {int} reaction When the ai reacts to the ball in the X-axis
 *
 * @author Åhlin, Pontus
*/

void playingAi(int offset, int reaction){
    if (ballX > reaction){
		if (paddleY2 == 23){				//Makes the paddle not jump through space and time 
			paddleY2 = 23;
		}
		else if ((paddleY2 + offset) < ballY) {
			paddleY2++;
		}			
		if (paddleY2 == 1){
			paddleY2 = 1;
		}
		
		else if (ballY < (paddleY2 + offset)){
			paddleY2--;
		}
	}
}


/**
 * This function is where the 
 * difficulty is chosen 
 *
 * @param {int} difficulty This  
 * 
 * @author Åhlin, Pontus
 */


void playAi(int difficulty){

	switch(difficulty){
		case(0):
		playingAi(4, 120);
		break;

		case(1):
		playingAi(2,96);
		break;

		case(2):
		playingAi(1,64);
		break;
	}
}



/**
 * Game over 
 * Once player one or player two gets five
 * points the game is over and it will take you
 * to the high-score screen
 *
 * @author Åhlin, Pontus
*/

void gameOver(){
	if(playerOneScore == 5 || playerTwoScore == 5){
		difficulty = 1;									//Init difficulty to medium.
		setInGame(false); 
		setMenuScreenCode(41);							//Jump to set high score
	}
}



/**
 * Serve
 *
 * Deciding who should serve depending 
 * on who has most points
 *
 * @param {int} playerOneScore Score of player one 
 * @param {int} playerTwoScore Score of player two
*/

void serve(int playerOneScore, int playerTwoScore){
	if(playerOneScore > playerTwoScore) ballAngle = 0;
	else ballAngle = PI;
}



/**
 * This function is called from main, continuously, that checks 
 * whether a button is pressed or not. 
 * @param {int} buttonData Takes in the 
 *
 * @author Åhlin, Pontus
*/

void gameButtonTriggered(int buttonData) {

	if (buttonData == 15) {
		setInGame(false);
		setMenuScreenCode(43);
		return;
	}

	if(buttonData & 0x8 && upOrDown(paddleY1, 1)) {
		paddleY1++;
	}

	if(buttonData & 0x4 && upOrDown(paddleY1, -1)) {
		paddleY1--;
	}

	if (pvpMode) {

		PORTE = 0x1;
		
		if( buttonData & 0x2 && upOrDown(paddleY2, 1)) {
			paddleY2++;
			PORTE = 0x2;
		}

		if (buttonData & 0x1 && upOrDown(paddleY2, -1)) {
			paddleY2--;
			PORTE = 0x4;
		}

	}
}



/**
 * Functions that makes the game playable
 * is called into to this function
*/

void playingGame() {
	canvasClear();															//Clear the menu 
	serve(playerOneScore, playerTwoScore);
	moveBall(&ballX, &ballY, ballAngle);									//Moves the ball
	paintArena();															//Paint the arena 	
	if (!pvpMode) playAi(difficulty);
	checkEdgeHit(ballY, &ballAngle);										//Check arena hit 
	checkLeftPaddleHit(ballX, ballY, &ballAngle, paddleX1, paddleY1);		//Check player 1 paddle hit 
	checkRightPaddleHit(ballX, ballY, &ballAngle, paddleX2, paddleY2);		//Check player 2 paddle hit 
	checkPlayerScore(&playerOneScore, &playerTwoScore, ballX);
	gameOver();																//Checks game state 
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
    paddleX1 = 0;			//The initial positions of the padels. and the ball
    paddleY1 = 15;
    paddleX2 = 126;
    paddleY2 = 15;
	ballAngle = PI;
}


/**
 * initializes the paddles, arena 
 * and player score when
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
 * 
 * @author Åhlin, Pontus
*/

void renderGame(){
		playingGame();

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
	return playerTwoScore;
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



/**
 * Turns either the pvp mode on or off
 *
 * @param {bool} trueOrFalse
 *
 * @author Åhlin, Pontus
*/
void pvpModeOnOff(bool trueOrFalse) {
	pvpMode = trueOrFalse;
}



/**
 * Get Winner
 * 
 * Check who won the match
 * 
 * @return {int} 1 = player one, 2 = player two, 3 = ai
 * 
 * @author Fridh, William
*/
int getWinner(void) {
	if (getPlayerOneScore() > getPlayerTwoScore()) { // Player one wins vs
        return 1;
    } else { // Player two wins
        if (pvpMode) { // PVP
            return 2;
        } else {
            return 3;
        }
    }
}

