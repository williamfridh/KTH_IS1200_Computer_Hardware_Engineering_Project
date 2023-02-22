extern int screen_code;



/**
 * Render Menu
 * 
 * Render menu based on the global variable screen_code.
*/
void renderMenu(void) {

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
    if (screen_code == 0 && buttonData > 0) {           // If landing screen and button is pressed
        screen_code = 1;                                // Jump to screen #1
        return;                                         // Stop function
    }

    switch (buttonData) {
    case (8):                                           // Button #4 (firt from the left)
        setScreenCode(screen_code-1);                   // Navigate backward
        break;

    case (4):                                           // Button #3 (second from the left)
        setScreenCode(screen_code+1);                   // Navigate forward
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



/**
 * Trigger OK click
 * 
 * The OK click is the action when the used selects something in the menu.
 * The action will be based on the current screen code.
*/
void triggerOk(void) {
    switch (screen_code) {
    case (1):
        /* code */
        break;
    
    default:
        break;
    }
}

