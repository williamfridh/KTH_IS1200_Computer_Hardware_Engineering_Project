#include <stdint.h>								// Declarations of uint_32 and the like.
#include <stdbool.h>							// Support for boolean
#include <stdio.h>                              // Used for debugging
#include "model/paddle.c"
#include "model/ball.c"



/**
 * Data & Settings For The Canvas
*/
#define DISPLAY_HEIGHT 16
#define DISPLAY_WIDTH 64
#define DISPLAY_BYTES (DISPLAY_HEIGHT/8)*DISPLAY_WIDTH

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
 * Get Encoded Canvas Data
 * 
 * Return: An encoded version of the canvas that can be read by the display.
*/
uint8_t* canvasGetData(void) {

    static uint8_t canvas_encoded[DISPLAY_BYTES];

    for (int i = 0; i < DISPLAY_BYTES; i++) canvas_encoded[i] = 255;
                
    for (int i = 0, val = 1, byte_row = 0, col = 0; i < DISPLAY_BYTES; i++, val = 1, col++) {    // Loop that also sets values to be used

        if (col == DISPLAY_WIDTH) {                                                         // If last column is reached
            col = 0;                                                                        // Jump to first column again
            byte_row++;
        }

        for (int bit = 0; bit < 8; bit++) {                                                       // Loop 8 bits to be in byte
            if (canvas[col][bit+byte_row*8] == 1) canvas_encoded[i] -= val;                        // Decrese byte value if the canvas cell is painted (=1)
            val += val;                                                                     // Double val (1, 2, 4, 8, 16...)
        }
        
    }

    return canvas_encoded;

}



/**
 * Main - For Debugging & Example
*/
/*
int main(void) {

    canvasInsertModel(0, 0, 2, 4, model_paddle, false);
    canvasInsertModel(10, 10, 2, 2, model_ball, false);

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

}*/


