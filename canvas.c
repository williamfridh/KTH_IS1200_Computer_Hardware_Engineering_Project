#include <stdint.h>								// Declarations of uint_32 and the like.
#include <stdbool.h>							// Support for boolean
#include <stdio.h>                              // Used for debugging
#include "basicFunctions.h"
#include "model/paddle.c"
#include "model/ball.c"
#include "model/font_big.c"
#include "model/font_small.c"
#include "model/menu_navigation.c"



/**
 * Data & Settings For The Canvas
*/
#define DISPLAY_HEIGHT 32
#define DISPLAY_WIDTH 128
#define DISPLAY_BYTES (DISPLAY_HEIGHT/8)*DISPLAY_WIDTH
#define LETTER_SPACING 1

static uint8_t canvas[DISPLAY_WIDTH][DISPLAY_HEIGHT];



/**
 * Canvas Action
 * 
 * This function is called from simpler functions.
 * It takes in data and modifies the canvas.
 * 
 * Warning: No not call this method if not via
 * a simpler function such as paint and erase.
*/
void canvasAction(int x, int y, int width, int height, int val) {
	for (int xx = 0; xx < width; xx++) {
		for (int yy = 0; yy < height; yy++) {
			canvas[x+xx][y+yy] = val;
		}
	}
}



/**
 * Canvas Paint
 * 
 * Paints to the canvas trough a call to canvasAction().
 * This function can paint at a certain location and draw shapes.
*/
void canvasPaint(int x, int y, int width, int height) {
	canvasAction(x, y, width, height, 1);
}



/**
 * Canvas Erase
 * 
 * Removes from the canvas via a call tol canvasAction().
 * This function removed from the canvas at a given location
 * and can do so in shapes.
*/
void canvasErase(int x, int y, int width, int height) {
	canvasAction(x, y, width, height, 0);
}



/**
 * Clear Canvas
 * 
 * Clear all values in the canvas. This can be used for quickly
 * clearing the display data before sending it to the display.
*/
void canvasClear() {
	for (int x = 0; x < DISPLAY_WIDTH; x++) {
		for (int y = 0; y < DISPLAY_HEIGHT; y++) {
			canvas[x][y] = 255;
		}
	}
}



/**
 * Check If Pixel In Location
*/
bool ifPixelIsFilled(int x, int y) {
    if (canvas[x][y] == 1) {
        return true;
    } else {
        return false;
    }
}



/**
 * Insert Model
 * 
 * Inserting a model onto the canvas required the following arugments:
 * @param x             - x offset
 * @param y             - y offset
 * @param modelWidth    - width of the model
 * @param modelHeight   - height of the model
 * @param modelData     - two-dimensional array of the model
 * @param merge         - boolean for deciding merging
 * 
 * Note: Flipping the modelWidth and moderlHeight arguments results in a flipped model.
*/
void canvasInsertModel(
    int x,
    int y,
    int modelWidth,
    int modelHeight,
    uint8_t modelData[][modelHeight], 
    bool merge
) {
    for (int xx = 0; xx < modelWidth; xx++) {
        for (int yy = 0; yy < modelHeight; yy++) {
            if (merge) {
                if (canvas[x+xx][y+yy] == 1 || modelData[xx][yy] == 1) {
                    canvas[x+xx][y+yy] = 1;
                }
            } else {
                canvas[x+xx][y+yy] = modelData[xx][yy];
            }
        }
    }
}



/**
 * Write On Canvas
 * 
 * @param txt           - String to be printed on canvas
 * @param x             - X position
 * @param y             - Y position
 * @param merge         - Determin if it should merge or not.
 * @param big           - Print big letters if true, otherwise small
 * 
 * Note: font models are stores in a 1D array.
 * 
 * This function takes in a string an prints it to the screen.
 * It loads a font model and converts the correct data from it
 * into a 2D array which is sent to canvasInsertModel.
 * 
 * Appart from this, it also cleares the area to be printed
 * beforehand, if merge is set to false.
*/
void canvasWrite(char *txt, int x, int y, bool merge, bool big) {

    uint8_t *model_font = big ? model_font_big : model_font_small;                          // Determin font model
    const int size = big ? 8 : 5;                                                           // Determin size
    const int txt_len = getCharLen(txt);                                                    // get text length

    if (!merge) {
        const int textAreaWidth = size*txt_len+(txt_len-1)*LETTER_SPACING;                  // Calculate text area width
        canvasErase(x, y, textAreaWidth, size);                                             // Clear text area
    }

    for (int i = 0; i < txt_len; i++) {                                                     // Loop characters
        uint8_t char_model[size][size];                                                     // Create small model
        for (int x = 0; x < size; x++) {
            const int x_offset = (txt[i]-32)*size+x;                                        // Calculate x offset for reading font
            for (int i = (size-1), j = 1; i >= 0; i--, j = j*2) {
                char_model[x][i] = model_font[x_offset] & j ? 1 : 0;
            }
        }
        canvasInsertModel(x+i*size+LETTER_SPACING*i, y, size, size, char_model, merge);      // Send data to canvasInsertmodel
    }
}



/**
 * Get Encoded Canvas Data
 * 
 * Return: An encoded version of the canvas that can be read by the display.
*/
uint8_t* canvasGetData(void) {

    static uint8_t canvas_encoded[DISPLAY_BYTES];

    for (int i = 0; i < DISPLAY_BYTES; i++) canvas_encoded[i] = 255;
                
    for (int i = 0, val = 1, byte_row = 0, col = 0; i < DISPLAY_BYTES; i++, val = 1, col++) {   // Loop that also sets values to be used

        if (col == DISPLAY_WIDTH) {                                                             // If last column is reached
            col = 0;                                                                            // Jump to first column again
            byte_row++;
        }

        for (int bit = 0; bit < 8; bit++) {                                                     // Loop 8 bits to be in byte
            if (canvas[col][bit+byte_row*8] == 1) canvas_encoded[i] -= val;                     // Decrese byte value if the canvas cell is painted (=1)
            val += val;                                                                         // Double val (1, 2, 4, 8, 16...)
        }
        
    }

    return canvas_encoded;

}



/**
 * Main - For Debugging & Example
*/
/*
int main(void) {

    canvasInsertModel(0, 123, 128, 5, model_menu_navigation, false);
    canvasWrite("BOARD", 40, 9, false, true);

    //canvasWrite("qwertyuiop", 0,0, false, true);
    //canvasWrite("QWERTYUIOP", 0,0, false, true);

    //canvasInsertModel(0, 0, 2, 4, model_paddle, false);
    //canvasInsertModel(63, 0, 2, 2, model_ball, false);

    for (int i = 0; i < DISPLAY_HEIGHT; i++) {
        for (int j = 0; j < DISPLAY_WIDTH; j++) {
            if (canvas[j][i] == 0) {
                printf("%s", "-");
            } else {
                printf("%s", "X");
            }
        }
        printf("\n");
    }

    printf("\n");

    uint8_t* canvas_data = canvasGetData();

    for (int i = 0, t = 0; i < DISPLAY_BYTES; i++) {
        printf("%d, ", canvas_data[i]);
        t++;
        if (t == DISPLAY_WIDTH) {
            printf("\n");
            t = 0;
        }
    }

}
*/

