#include <stdint.h>								// Declarations of uint_32 and the like.
#include <pic32mx.h>							// Declarations of system-specific addresses etc.
#include <stdbool.h>							// Support for boolean



/**
 * Settings & Data
 * 
 * This section should hold the global settings and data
 * that is'nt directly connected to either the game or menu.
*/
int screen_code = 0;
bool in_game = false;



/**
 * Set Screen Code
 * 
 * This function checks the target screen code before setting it.
 */
void setScreenCode(int code) {
	if (code < 1) {														// Make sure target code is positive.
		return;
	} else {
		screen_code = code;
	}
}



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
 * Get Buttons
*/
int getButtons(void){
    return (PORTD & 0xe0) >> 4; 
}



/**
 * Listen For Inputs
 * 
 * This function calls getButtons, sorts
 * this data and takes relevant action.
*/
void listenForInput() {
	int button_data = getButtons();
	if (in_game) {
		gameButtonTriggered(button_data);								// Send button data to the game button handler
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

  	TRISDSET = 0xf0;  	                 								// Set Buttons 1-4 as inputs 
	timerInit();														// Initilize timer
	while(1) {															// Inifinite loop for listening
		updateScreen();
		listenForTick();						
		listenForInput();
	}
	return 0;															// Won't be reached due to inifinite loop
}

