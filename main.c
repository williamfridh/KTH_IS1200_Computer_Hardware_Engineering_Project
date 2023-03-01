/**
 ==================== X-PONG ====================
 * 
 * X-PONG is a game like the classic Pong but with
 * different structure and functionality. It was writtes
 * as a project for the KTH course "IS1200 VT23 Computer
 * Hardware Engineering".
 * 
 * Most code in this project has been written by the
 * group itself. However, some of the code (marked out)
 * was taken from previous labs.
 * 
 * @author Fridh, William & Åhlin Pontus
 * @link https://github.com/williamFridh
 * 
 * @author Åhlin Pontus
 * @link https://github.com/PontusAhlin
*/

/**
 * Include Libraries
*/
#include <stdint.h>								// Declarations of uint_32 and the like.
#include <pic32mx.h>							// Declarations of system-specific addresses etc.
#include <stdbool.h>							// Support for boolean
#include "menu.h"
#include "highscore.h"
#include "shieldDisplay.h"
#include "game.h"
#include "mips.h"



/**
 * Settings
 * 
 * This section holds global settings that
 * itsn't solely related to the game or menu.
*/
bool in_game = false;
volatile int * trise = (volatile int *) 0xbf886100;					// Defined pointer to TRISE (debugging)
int ledVal = 0;														// Debugging
int btn_lock = false;												// Used preventing rapid clicks in the menu
int btn_data;														// Hold button data



/**
 * Set In Game
 * 
 * This function is used for updating the in_game value.
 * It can be called upon for instance when a game should
 * start or when a game should end.
 * 
 * @param {bool} - Target state
 * 
 * @author Fridh, William
*/
void setInGame(bool newState) {
	in_game = newState;
}



/**
 * Update Screen
 * 
 * Check if a game is running or not and call
 * correct render function based on that.
 * 
 * @author Fridh, William
*/
void updateScreen(void) {
	if (in_game) {
		renderGame();
	} else {
		renderMenu();
	}
}



/**
 * Set Button Data
 * 
 * This function handles the button data differently depending
 * on the vale of the boolean in_game. It modifies the bits of
 * btn_data and handles btn_lock if the user isn't in a game.
 * 
 * @author Fridh, William
*/
void setBtnData(void) {
	const int current_btn_data = ((PORTD & 0xe0) >> 4) | ((PORTF & 0x2) >> 1);
	if (in_game) {
		btn_data = btn_data | current_btn_data;
		btn_lock = false;
	} else {
		if (!btn_lock && current_btn_data) {
			btn_data = btn_data | current_btn_data;
			btn_lock = true;
		} else {
			if (!current_btn_data) {
				btn_lock = false;
			}
		}
	}
}



/**
 * Reset Button Data
 * 
 * Resets the button data. Usually called from within handleBtnData.
 * 
 * @author Fridh, William
*/
void resetBtnData(void) {
	btn_data = 0;
}



/**
 * Handle Button Data
 * 
 * Decides what to do with the button data.
 * Passes it forward to the relevant function.
 * 
 * @author Fridh, William
*/
void handleBtnData(void) {
	if (in_game) {
		gameButtonTriggered(btn_data);								// Send button data to the game button handler
	} else {
		menuButtonTriggered(btn_data);								// Send button data to the menu button handler
	}
}



/**
 * Interrupt Service Routine
 * 
 * This function detects and resets intruptflags.
 * 
 * @authors Fridh, William & Åhlin Pontus
*/
void user_isr(void) {
	if(IFS(0) & 0x100){													// Check for relevant flag
		IFS(0) = IFS(0) & 0xfffffeff;									// Reset interrupt flag
		handleBtnData();												// Handle button data
		updateScreen();													// Update screen
		resetBtnData();													// Reset button data
	}
}



/**
 * Initilize Timer
 * 
 * Initilizes and configures the timer.
 * 
 * @author Åhlin Pontus
*/
void initTimer(void) {
	T2CON = 0x70;                       								//Stopping timer and setting the prescaler to 1/256
	PR2 = ((80000000 / 256)/ 10);       								//Setting the period for the timer
	TMR2 = 0;                           								//Ticks to PR2
	IECSET(0) = 0x100;                  								//Enable interrupts
	IPC(2) = 0xC;                       								//Enable a interrupt priority
	T2CONSET = 0x8000;                  								//Starting timer
	enable_interrupt();
}



/**
 * Main Function
 * 
 * The main function is called on startup and will continue
 * running infinite thanks to the while-loop.
 * 
 * @authors Fridh, William & Åhlin Pontus
*/
int main(void) {

	*trise = *trise & 0xffffff00;										// Set ports 0-7 as outputs (debugging)

  	TRISDSET = 0xe0;  	                 								// Set buttons 2-4 as inputs 
  	TRISFSET = 0x2;  	                 								// Set button 1 as inputs

	initShield();														// Initilize display
	initTimer();														// Initilize timer
	initHighscore();													// Initilize highscore

	while(1) setBtnData();												// Inifinite loop for listening	for input

	return 0;
}

