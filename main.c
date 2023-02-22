#include <stdint.h>								// Declarations of uint_32 and the like.
#include <pic32mx.h>							// Declarations of system-specific addresses etc.



/*
Settings & Data

This section should hold the global settings and data
that is'nt directly connected to either the game or menu.
*/
int screenCode = 1;
int inGame = 1;



/*
Main Function

The main function is called on startup and will continue
running infinite thanks to the while-loop.
*/
int main(void) {

	// Debugging code
	volatile int * trise = (volatile int *) 0xbf886100;					// Defined pointer to TRISE
	*trise = *trise & 0xffffff00;										// Set ports 0-7 as outputs

	timerInit();														// Initilize timer
	while(1) {															// Inifinite loop for listening
		updateScreen();
		listenForTick();						
		listenForInput();
	}
	return 0;															// Won't be reached due to inifinite loop
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

void updateScreen(void) {
	if (inGame) {
		renderGame();
	} else {
		//renderMenu();
	}
}

/*
*/
void listenForInput() {

}