/**
 * Include Libraries & Models
*/
#include <stdbool.h>
#include "canvas.h"
#include "shieldDisplay.h"
#include "game.h"
#include "main.h"
#include "highscore.h"

#include "model/startscreen.c"
#include "model/paddle.c"

#define SMALL_TEXTLINE_ONE 0
#define SMALL_TEXTLINE_TWO 9
#define SMALL_TEXTLINE_THREE 18
#define SMALL_TEXTLINE_FOUR 27



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
    switch (menuScreencode) {
        /* ======================================== START SCREEN ======================================== */
        case (0):
            canvasInsertModel(0, 0, 128, 32, model_startscreen, false);
            break;
        /* ======================================== PLAYER VS AI ======================================== */
        case (1):
            canvasWrite("PLAY VS. AI", 15, 9, false, true);
            drawButtonDescBar(false, true, true, false);
            break;

        case (10):
            switch(getDifficultySetting()) {
                case(0):
                    canvasWrite("DIFFICULTY: EASY", 15, SMALL_TEXTLINE_TWO, false, false);
                    break;
                case(1):
                    canvasWrite("DIFFICULTY: MEDIUM", 15, SMALL_TEXTLINE_TWO, false, false);
                    break;
                case(2):
                    canvasWrite("DIFFICULTY: HARD", 15, SMALL_TEXTLINE_TWO, false, false);
                    break;
            }
            drawButtonDescBar(true, true, true, true);
            break;

        case (11):
            canvasWrite("START", 40, 9, false, true);
            drawButtonDescBar(true, true, true, true);
            break;  
        /* ======================================== PLAYER VS PLAYER ======================================== */
        case (2):
            canvasWrite("PVP", 50, 9, false, true);
            drawButtonDescBar(true, true, true, false);
            break;
        case (20):
            canvasWrite("START", 40, 9, false, true);
            drawButtonDescBar(true, true, true, true);
            break;
        /* ======================================== HIGHSCORE ======================================== */
        case (3):
            canvasWrite("HIGHSCORE", 22, 9, false, true);
            drawButtonDescBar(true, false, true, false);
            break;
        case (30):
            canvasWrite("1:", 0, SMALL_TEXTLINE_ONE, false, false);
            canvasWrite(getHighscoreInitials(0), 12, SMALL_TEXTLINE_ONE, false, false);

            canvasWrite("2:", 0, SMALL_TEXTLINE_TWO, false, false);
            canvasWrite(getHighscoreInitials(1), 12, SMALL_TEXTLINE_TWO, false, false);

            canvasWrite("3:", 0, SMALL_TEXTLINE_THREE, false, false);
            canvasWrite(getHighscoreInitials(2), 12, SMALL_TEXTLINE_THREE, false, false);

            canvasPaint(33, 0, 1, 21);
            
            canvasWrite("4:", 36, SMALL_TEXTLINE_ONE, false, false);
            canvasWrite(getHighscoreInitials(3), 48, SMALL_TEXTLINE_ONE, false, false);

            canvasWrite("5:", 36, SMALL_TEXTLINE_TWO, false, false);
            canvasWrite(getHighscoreInitials(4), 48, SMALL_TEXTLINE_TWO, false, false);

            canvasWrite("6:", 36, SMALL_TEXTLINE_THREE, false, false);
            canvasWrite(getHighscoreInitials(5), 48, SMALL_TEXTLINE_THREE, false, false);

            canvasPaint(72, 0, 1, 21);
            
            canvasWrite("7:", 78, SMALL_TEXTLINE_ONE, false, false);
            canvasWrite(getHighscoreInitials(6), 90, SMALL_TEXTLINE_ONE, false, false);

            canvasWrite("8:", 78, SMALL_TEXTLINE_TWO, false, false);
            canvasWrite(getHighscoreInitials(7), 90, SMALL_TEXTLINE_TWO, false, false);

            canvasWrite("9:", 78, SMALL_TEXTLINE_THREE, false, false);
            canvasWrite(getHighscoreInitials(8), 90, SMALL_TEXTLINE_THREE, false, false);

            drawButtonDescBar(false, false, false, true);
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

        case(10):
            toggleDifficultySetting();
            break;

        case (11):
            initArena();
            setInGame(true);
            break;

        case (20):
            initArena();
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
            break;
    }
}

