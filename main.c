#include <stdint.h>								// Declarations of uint_32 and the like.
#include <pic32mx.h>							// Declarations of system-specific addresses etc.
#include <stdbool.h>							// Support for boolean
#include "menu.h"
#include "shieldDisplay.h"



/**
 * Settings & Data
 * 
 * This section should hold the global settings and data
 * that is'nt directly connected to either the game or menu.
*/
bool in_game = false;



/**
 * Update Screen
 * 
 * Check if a game is running or not and call
 * correct render function based on that.
*/
void updateScreen(void) {
	if (in_game) {
		//renderGame();
	} else {
		renderMenu();
	}
}



/**
 * Get Buttons
*/
int getButtons(void){
    return ((PORTD & 0xe0) >> 4) | ((PORTF & 0x2) >> 1);
}



/**
 * Listen For Inputs
 * 
 * This function calls getButtons, sorts
 * this data and takes relevant action.
*/
void listenForInput() {

	int button_data = getButtons();

	// Debugging code
	volatile int * trise = (volatile int *) 0xbf886100;					// Defined pointer to TRISE
	*trise = *trise & 0xffffff00;										// Set ports 0-7 as outputs
	PORTE = button_data;

	if (in_game) {
		//gameButtonTriggered(button_data);								// Send button data to the game button handler
	} else {
		menuButtonTriggered(button_data);								// Send button data to the menu button handler
	}
}



/**
 * Main Function
 * 
 * The main function is called on startup and will continue
 * running infinite thanks to the while-loop.
*/
int main(void) {

	// Debugging code
	volatile int * trise = (volatile int *) 0xbf886100;					// Defined pointer to TRISE
	*trise = *trise & 0xffffff00;										// Set ports 0-7 as outputs
	PORTE = 0xf;

  	TRISDSET = 0xe0;  	                 								// Set buttons 2-4 as inputs 
  	TRISFSET = 0x2;  	                 								// Set button 1 as inputs 

	initShield();														// Initilize display
	//timerInit();														// Initilize timer
	while(1) {															// Inifinite loop for listening
		updateScreen();
		//listenForTick();						
		listenForInput();
	}
	return 0;															// Won't be reached due to inifinite loop
}

