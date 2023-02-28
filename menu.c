#include <stdbool.h>							// Support for boolean
#include "model/startscreen.c"
#include "model/paddle.c"
#include "model/menu_navigation.c"
#include "canvas.h"
#include "shieldDisplay.h"



/**
 * Settings
*/
int menuScreencode = 0;
int screenCodes[] = {0,1,2,3,10,11,20,30,31};



/**
 * Set Menu Screen Code
 * 
 * This function checks the target screen code before setting it.
 */
void setMenuScreenCode(int code) {
    if (code == 0) return;
    for (int i = 0; i < sizeof(screenCodes); i++) {
        if (screenCodes[i] == code) {
            menuScreencode = code;
            break;
        }
    }
}



/**
 * Render Menu
 * 
 * Render menu based on the global variable menuScreencode.
*/
void renderMenu(void) {
    canvasClear();
    canvasInsertModel(0, 123, 128, 5, model_menu_navigation, false);
    switch (menuScreencode) {
        /* ======================================== START SCREEN ======================================== */
        case (0):
            canvasInsertModel(0, 0, 128, 32, model_startscreen, true);
            break;
        /* ======================================== PLAYER VS AI ======================================== */
        case (1):
            canvasWrite("PLAY VS. AI", 15, 9, false, true);
            break;
        case (10):
            canvasWrite("DIFFICULTY", 16, 9, false, true);
            break;
        case (11):
            canvasWrite("START", 40, 9, false, true);
            break;  
        /* ======================================== PLAYER VS PLAYER ======================================== */
        case (2):
            canvasWrite("PVP", 50, 9, false, true);
            break;
        case (20):
            canvasWrite("START", 40, 9, false, true);
            break;
        /* ======================================== HIGHSCORE ======================================== */
        case (3):
            canvasWrite("HIGHSCORE", 22, 9, false, true);
            break;
        case (30):
            canvasWrite("BOARD", 40, 9, false, true);
            break;
        case (31):
            canvasWrite("RESET", 40, 9, false, true);
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
            setMenuScreenCode(10);
            break;
            
        case (2):
            setMenuScreenCode(10);
            break;

        case (3):
            setMenuScreenCode(10);
            break;

        case (11):
        case (20):
            setInGame(true);
            break;
        
        default:
            break;
    }
}

void triggerBack(void) {
    if (menuScreencode > 9) {
        setMenuScreenCode(menuScreencode % 10);
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
    if (menuScreencode == 0 && buttonData > 0) {        // If landing screen and button is pressed
        menuScreencode = 1;                             // Jump to screen #1
        return;                                         // Stop function
    }

    switch (buttonData) {
        case (8):                                           // Button #4 (firt from the left)
            setMenuScreenCode(menuScreencode-1);            // Navigate backward
            break;

        case (4):                                           // Button #3 (second from the left)
            setMenuScreenCode(menuScreencode+1);            // Navigate forward
            break;

        case (2):                                           // Button #2 (third from the left)
            triggerOk();                                    // Trigger ok-click.
            break;

        case (1):                                           // Button #1 (fourth from the left)
            triggerBack();                                  // Trigger back-click.
            break;
        
        default:
            // Can be removed.
            break;
    }
}

