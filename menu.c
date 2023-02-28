/**
 * Include Libraries & Models
*/
#include <stdbool.h>
#include "canvas.h"
#include "shieldDisplay.h"
#include "main.h"
#include "highscore.h"

#include "model/startscreen.c"
#include "model/paddle.c"
#include "model/menu_navigation.c"



/**
 * Settings
*/
int menuScreencode = 0;
int screenCodes[] = {0,1,2,3,10,11,20,30};



/**
 * Set Menu Screen Code
 * 
 * This function checks the target screen code before setting it.
 * 
 * @param {int}     - target screen code
 * @param {bool}    - allow screen code to be changed to startscreen (0)
 * 
 * @author Fridh, William
 */
void setMenuScreenCode(int code) {
    if (code == 0) return;
    for (int i = 0; i < sizeof(screenCodes); i++) {
        if (screenCodes[i] == code) {
            menuScreencode = code;
            return;
        }
    }
}



/**
 * Render Menu
 * 
 * Render menu based on the global variable menuScreencode.
 * 
 * @author Fridh, William
*/
void renderMenu(void) {
    canvasClear();
    canvasInsertModel(0, 123, 128, 5, model_menu_navigation, false);
    switch (menuScreencode) {
        /* ======================================== START SCREEN ======================================== */
        case (0):
            canvasInsertModel(0, 0, 128, 32, model_startscreen, false);
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
            canvasWrite("1:", 0, 0, false, false);
            canvasWrite(getHighscoreInitials(0), 12, 0, false, false);

            canvasWrite("2:", 0, 8, false, false);
            canvasWrite(getHighscoreInitials(1), 12, 8, false, false);

            canvasWrite("3:", 0, 16, false, false);
            canvasWrite(getHighscoreInitials(2), 12, 16, false, false);

            canvasPaint(33, 0, 1, 21);
            
            canvasWrite("4:", 36, 0, false, false);
            canvasWrite(getHighscoreInitials(3), 48, 0, false, false);

            canvasWrite("5:", 36, 8, false, false);
            canvasWrite(getHighscoreInitials(4), 48, 8, false, false);

            canvasWrite("6:", 36, 16, false, false);
            canvasWrite(getHighscoreInitials(5), 48, 16, false, false);

            canvasPaint(72, 0, 1, 21);
            
            canvasWrite("7:", 78, 0, false, false);
            canvasWrite(getHighscoreInitials(6), 90, 0, false, false);

            canvasWrite("8:", 78, 8, false, false);
            canvasWrite(getHighscoreInitials(7), 90, 8, false, false);

            canvasWrite("9:", 78, 16, false, false);
            canvasWrite(getHighscoreInitials(8), 90, 16, false, false);

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
 * 
 * @author Fridh, William
*/
void triggerOk(void) {
    switch (menuScreencode) {
        case (1):
            setMenuScreenCode(10);
            break;
            
        case (2):
            setMenuScreenCode(20);
            break;

        case (3):
            setMenuScreenCode(30);
            break;

        case (11):
        case (20):
            setInGame(true);
            break;
        
        default:
            break;
    }
}



/**
 * Trigger Back Action
 * 
 * Navigates the user back one step in the menu.
 * 
 * @author Fridh, William
*/
void triggerBack(void) {
    switch (menuScreencode) {
        case (10):
        case (11):
            setMenuScreenCode(1);
            break;
            
        case (20):
        case (21):
            setMenuScreenCode(2);
            break;

        case (30):
            setMenuScreenCode(3);
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
 * Button 2: 
 * 
 * @param {int} - button data (lower 4 bits)
 * 
 * @author Fridh, William
*/
void menuButtonTriggered(int buttonData) {
    if (menuScreencode == 0 && buttonData > 0) {        // If landing screen and button is pressed
        menuScreencode = 1;                             // Jump to screen #1
        return;                                         // Stop function
    }

    switch (buttonData) {
        case (8):                                           // Button #4 (firt from the left)
            setMenuScreenCode(menuScreencode-1);     // Navigate backward
            break;

        case (4):                                           // Button #3 (second from the left)
            setMenuScreenCode(menuScreencode+1);     // Navigate forward
            break;

        case (2):                                           // Button #2 (third from the left)
            triggerOk();                                    // Trigger ok-click.
            break;

        case (1):                                           // Button #1 (fourth from the left)
            triggerBack();                                  // Trigger back-click.
            break;
        
        default:
            break;
    }
}

