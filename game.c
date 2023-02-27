#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include "canvas.h"
#include "model/ball.c"
#include "model/map.c"
#include "model/paddle.c"
#include "shieldDisplay.h"

/*
Global values
Global values that holds data of the players and the balls position.
Aswell as the score of the player. 
*/

int x1 = 0;			//The initial positions of the padels. and the ball
int y1 = 16;
int x2 = 126;
int y2 = 16;
int bX = 64;
int bY = 16;
int p1Score = 0;
int p2Score = 0;


/*
Checks which button is pressed and if it is pressed
trigger a certain action, in this case either make the 
player go down or up
*/
void paintArena(){
	canvasInsertModel(x1, y1, 2, 8, model_paddle, false);		//The left side padel 
	canvasInsertModel(x2, y2, 2, 8, model_paddle, false);		//The right side padel 

	canvasInsertModel(0, 0, 128, 32, model_map, true);			//The map
	canvasInsertModel(bX, bY, 2, 2, model_ball, true);			//The ball
}


/**
 * This function determines if the paddle will move up or down.
 * The function also makes bounderies for the padels.
 * @param pos			- Current position of padel 
 * @param direction 	- The direction where the padel is going 
 * @return bool			- Whether the paddle is allowed to move or not. 
 * 
*/

bool upOrDown(int pos, int direction){
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

	if(buttonData & 0x8 && upOrDown(y1, 1)){
		y1++;
	}

	if(buttonData & 0x4 && upOrDown(y1, -1)){
		y1--;
	}
	
	if(buttonData & 0x2 && upOrDown(y2, 1)){
		y2++;
	}

	if(buttonData & 0x1 && upOrDown(y2, -1)){
		y2--;
	}
}



/*
Initilize Game Timer
The game timer is used for keeping the game running at a certain speed.
This timer will cause an interupt flag efter 100ms.
*/
/*void gameTimerInit(void) {
	T2CON = 0x70;											 			// Stopping timer and setting the prescaler to 1/256
	PR2 = ((80000000 / 256)/ 10);			 							// Set the period for the timer
	TMR2 = 0;													 		// Tick to PR2
}



/*
Start Game Timer
*/
/*void gameTimerStart(void) {
	T2CONSET = 0x8000;													// Start timer
}



/*
Stop Game Timer
*/
/*void gameTimerStop(void) {
	T2CON = 0x70;											 			// Stopping timer and setting the prescaler to 1/256
}



/*
Listen For Game Timer Tick
This function is called repeatedly from
the function main inside a inifinite loop.
*/
/*volatile int * porte = (volatile int *) 0xbf886110;						// Used for debugging ticks
int timeoutCount = 0;													// A global counter used for slowing down the ticks
int ledTime = 0;														// Used for debugging ticks 
void listenForGameTimerTick(void) {
	if (IFS(0) & 0x100) {												// Detect and interrupt flag
		timeoutCount++;													// Increment global counter 
		IFS(0) = 0;														// Clear flags
		if (timeoutCount == 10) {										// If there as been 10 timeout event flags
			timeoutCount = 0;
			*porte = ledTime;											// Used for debugging ticks
			ledTime++;													// Used for debugging ticks
			/* ACTION STARTS */
			// Add a function call here.
			/* ACTION ENDS*/


/**
 * The function that main calls when we want to load in
 * the game state.
*/

void renderGame(){
		canvasClear();									//Clear the menu 
		paintArena();									//
		const uint8_t* canvas_data = canvasGetData();	//Get the data from the canvas
  		sendDisplayData(canvas_data);					//Sending that data to the OLED display

}





