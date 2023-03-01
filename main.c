#include <stdint.h>								// Declarations of uint_32 and the like.
#include <pic32mx.h>							// Declarations of system-specific addresses etc.
#include <stdbool.h>							// Support for boolean
#include "menu.h"
#include "shieldDisplay.h"
#include "game.h"
#include "mips.h"


/**
 * Settings & Data
 * 
 * This section should hold the global settings and data
 * that is'nt directly connected to either the game or menu.
*/
bool in_game = true;
volatile int * trise = (volatile int *) 0xbf886100;					// Defined pointer to TRISE (debugging)
int ledVal = 0;														// Debugging
int btn_lock = false;
int btn_data;



/**
 * Update Screen
 * 
 * Check if a game is running or not and call
 * correct render function based on that.
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
			//PORTE = 0x80;
		} else {
			if (!current_btn_data) {
				btn_lock = false;
				//PORTE = 0x00;
			}
		}
	}
}



/**
 * Reset Button Data
 * 
 * Resets the button data. Usually called from within handleBtnData.
*/
void resetBtnData(void) {
	btn_data = 0;
}



/**
 * Handle Button Data
 * 
 * Decides what to do with the button data.
 * Passes it forward to the relevant function.
*/
void handleBtnData() {
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
*/
void user_isr(void) {
	if(IFS(0) & 0x100){													// Check for relevant flag
		IFS(0) = IFS(0) & 0xfffffeff;									// Reset interrupt flag
		handleBtnData();												// Handle button data
		updateScreen();													// Update screen
		resetBtnData();													// Reset button data
		//ledVal++;														// Debugging
		//PORTE = ledVal;												// Debugging
	}
}



/**
 * Initilize Timer
 * 
 * Initilizes and configures the timer.
*/
void initTimer(void) {
	T2CON = 0x70;                       								//Stopping timer and setting the prescaler to 1/256
	PR2 = ((40000000 / 256)/ 10);       								//Setting the period for the timer
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
*/
int main(void) {
    PORTE = 0;

	*trise = *trise & 0xffffff00;										// Set ports 0-7 as outputs (debugging)

  	TRISDSET = 0xe0;  	                 								// Set buttons 2-4 as inputs 
  	TRISFSET = 0x2;  	                 								// Set button 1 as inputs

	initShield();														// Initilize display
	initTimer();														// Initilize timer

	while(1) setBtnData();												// Inifinite loop for listening	for input	
	return 0;															// Won't be reached due to inifinite loop
}

