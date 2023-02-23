#include <stdio.h>



/**
 * Data & Settings For The Canvas
*/
#define DISPLAY_HEIGHT 16
#define DISPLAY_WIDTH 64
#define DISPLAY_BYTES (DISPLAY_HEIGHT/8)*DISPLAY_WIDTH

unsigned int canvas[DISPLAY_HEIGHT][DISPLAY_WIDTH];
unsigned int canvas_encoded[DISPLAY_BYTES];



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
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			canvas[y+j][x+i] = val;
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
 * Clear Encoded Canvas
 * 
 * Clear all values in the encoded canvas.
*/
void clearEncodedCanvas() {
    for (int i = 0; i < DISPLAY_BYTES; i++) canvas_encoded[i] = 255;
}



/**
 * Clear Canvas
 * 
 * Clear all values in the canvas. This can be used for quickly
 * clearing the display data before sending it to the display.
*/
void clearCanvas() {
	for (int i = 0; i < DISPLAY_WIDTH; i++) {
		for (int j = 0; j < DISPLAY_HEIGHT; j++) {
			canvas[j][i] = 255;
		}
	}
}



/**
 * Encode Canvas
 * 
 * This function encodes the canvas into a format recognized by
 * the display. It's stores in the global variable canvas_encoded.
 * 
 * Reminder: Call this function before sending the new data to the display.
*/
int* encodeCanvas() {

    clearEncodedCanvas();                                                                   // Clear encoded canvas
                
    for (int i = 0, val = 1, row = 0, col = 0; i < DISPLAY_BYTES; i++, val = 1, col++) {    // Loop that also sets values to be used

        if (col == DISPLAY_WIDTH) {                                                         // If last column is reached
            col = 0;                                                                        // Jump to first column again
            row++;
        }

        for (int j = 0; j < 8; j++) {                                                       // Loop 8 bits to be in byte
            if (canvas[j+row*8][col] == 1) canvas_encoded[i] -= val;                        // Decrese byte value if the canvas cell is painted (=1)
            val += val;                                                                     // Double val (1, 2, 4, 8, 16...)
        }
        
    }

}

/*int main(void) {
    canvasPaint(0, 0, 64, 1);
    canvasPaint(0, 3, 64, 1);
    canvasPaint(0, 8, 64, 1);
    //paint(0, 3, 64, 1);
    for (int i = 0; i < DISPLAY_HEIGHT; i++) {
        for (int j = 0; j < DISPLAY_WIDTH; j++) {
            printf("%d", canvas[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    encodeCanvas();
    int t = 0;
    for (int i = 0; i < DISPLAY_BYTES; i++) {
        printf("%d, ", canvas_encoded[i]);
        t++;
        if (t == DISPLAY_WIDTH) {
            printf("\n");
            t = 0;
        }
    }
}*/

