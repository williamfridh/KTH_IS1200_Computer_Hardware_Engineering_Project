#include <stdbool.h>							// Support for boolean
#include "model/startscreen.c"
#include "model/paddle.c"
#include "canvas.h"
#include "shieldDisplay.h"


extern int menuScreencode;



/**
 * Settings
*/
int menuScreencode = 0;



/**
 * Set Menu Screen Code
 * 
 * This function checks the target screen code before setting it.
 */
void setMenuScreenCode(int code) {
	if (code < 1) {														// Make sure target code is positive.
		return;
	} else {
		menuScreencode = code;
	}
}



/**
 * Render Menu
 * 
 * Render menu based on the global variable menuScreencode.
*/
void renderMenu(void) {
    switch (menuScreencode) {
        case (0):
            canvasInsertModel(0, 0, 128, 32, model_startscreen, false);
            break;

        case (1):
            canvasClear();
            canvasInsertModel(0, 0, 4, 2, model_paddle, false);
            break;

        case (2):
            canvasClear();
            canvasInsertModel(10, 0, 4, 2, model_paddle, false);
            break;
        
        default:
            break;
    }
    const uint8_t* canvas_data = canvasGetData();
    sendDisplayData(canvas_data);
}



/**
 * Trigger OK click
 * 
 * The OK click is the action when the used selects something in the menu.
 * The action will be based on the current screen code.
*/
void triggerOk(void) {
    switch (menuScreencode) {
        case (1):
            break;
        
        default:
            break;
    }
}



/**
 * Menu Buttone Triggered Handler
 * 
 * Handle button triggers when in menu.
 * 
 * Button 4: Navigate left
 * Button 3: Navigate right
 * Button 2: OK
*/
void menuButtonTriggered(int buttonData) {
    if (menuScreencode == 0 && buttonData > 0) {           // If landing screen and button is pressed
        menuScreencode = 1;                                // Jump to screen #1
        return;                                         // Stop function
    }

    switch (buttonData) {
    case (8):                                           // Button #4 (firt from the left)
        setMenuScreenCode(menuScreencode-1);                   // Navigate backward
        break;

    case (4):                                           // Button #3 (second from the left)
        setMenuScreenCode(menuScreencode+1);                   // Navigate forward
        break;

    case (2):                                           // Button #2 (third from the left)
        triggerOk();                                    // Trigger ok-click.
        break;

    case (1):                                           // Button #1 (fourth from the left)
        /* code */
        break;
    
    default:
        // Can be removed.
        break;
    }
}

