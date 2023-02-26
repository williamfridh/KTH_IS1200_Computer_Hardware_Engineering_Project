#include <pic32mx.h>
#include <stdint.h>
#include "model/startscreen"
#include <stdbool.h>



/*
Global values
Global values that will be used to determine where 
ther player(s) and ball ism aswell as the current score
*/
int player_one_y_axis = 0;
int player_two_y_axis = 0;
int player_one_score = 0;
int player_two_score = 0;
int ball_y_axis = 0;
int ball_x_axis = 0;


/*

Checks which button is pressed and if it is pressed
trigger a certain action, in this case either make the 
player go down or up
*/

void gameButtonTriggerd(int b) {

	if(b & 0x8){
		playerUp(/*THE ADRESS OF PLAYER 1 */);
	}

	if(b & 0x4){
		playerDown(/*THE ADRESS OF PLAYER 1 */);
	}

	if(b & 0x2){
		playerUp(/*THE ADRESS OF PLAYER 2 */);
	}

	if(b & 0x1){
		playerDown(/*THE ADRESS OF PLAYER 2 */);
	}
}



/*
Player up and down
These function will determine whether the player
will move up or down. By using pointers it will see
what player is pressing their button. 
*/
void playerUp(int *player_adress) {					
	/*SOMETHING THAT MOVES THE PLAYER UP*/
}

void playerDown(int *player_adress) {
	/*SOMETHING THAT MOVES THE PLAYER DOWN*/
}





/*
Initilize Game Timer
The game timer is used for keeping the game running at a certain speed.
This timer will cause an interupt flag efter 100ms.
*/
void gameTimerInit(void) {
	T2CON = 0x70;											 			// Stopping timer and setting the prescaler to 1/256
	PR2 = ((80000000 / 256)/ 10);			 							// Set the period for the timer
	TMR2 = 0;													 		// Tick to PR2
}



/*
Start Game Timer
*/
void gameTimerStart(void) {
	T2CONSET = 0x8000;													// Start timer
}



/*
Stop Game Timer
*/
void gameTimerStop(void) {
	T2CON = 0x70;											 			// Stopping timer and setting the prescaler to 1/256
}



/*
Listen For Game Timer Tick
This function is called repeatedly from
the function main inside a inifinite loop.
*/
volatile int * porte = (volatile int *) 0xbf886110;						// Used for debugging ticks
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
		}
	}
}




