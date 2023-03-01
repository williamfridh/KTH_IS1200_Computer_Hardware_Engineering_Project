/**
 * Import Libraries
*/
#include <stdbool.h>							// Support for boolean
#include <stdio.h>                              // Used for debugging



/**
 * Settings & Data
 * 
 * highscore_data holds a 2D array. The first dimension
 * holds each score, and the second one, holding 5 objects,
 * has three letters, player score, and AI score.
*/
#define HIGHSCORE_AMOUNT 9                      // Max amount of highscores
char initials[HIGHSCORE_AMOUNT][4];             // Holds initials inputed by the player
int points[HIGHSCORE_AMOUNT][3];                // 0: player score & 1: ai score & 2: ratio
char inputData[3] = {'A','B','C'};



/**
 * Add Highscore
 * 
 * Inserts the new highscore with it's calculated ratio
 * into the array "initials" and "points". When doing so,
 * it also moves existing data so it remains sorted
 * (ratio in ascending order).
 * 
 * @param {char}            - Letter to be stored
 * @param {char}            - Letter to be stored
 * @param {char}            - Letter to be stored
 * @param {int}             - Scores by player one
 * @param {int}             - Scores by player two
 * 
 * @author Fridh, William
*/
void addHighscore(
    char letter_one,
    char letter_two,
    char letter_three,
    int player_one,
    int player_two
) {

    int ratio = player_one - player_two;                            // Calculate new score ratio

    for (int i = 0; i < HIGHSCORE_AMOUNT; i++) {                    // Iterate each score ratio
        if (
            ratio >= points[i][2] ||                                // Compare new ratio to target ratio
            (points[i][0] + points[i][0]) == 0                      // Overwrite empty data
        ) {                                                         
            // Make room for new data by shifting content down
            for (int j = HIGHSCORE_AMOUNT-1; j > i; j--) {       
                for (int t = 0; t < 3; t++) {                       // Move the data (loop for less code)
                    initials[j][t] = initials[j-1][t];
                    points[j][t] = points[j-1][t];
                }
            }
            // Insert the new data
            initials[i][0] = letter_one;
            initials[i][1] = letter_two;
            initials[i][2] = letter_three;
            points[i][0] = player_one;
            points[i][1] = player_two;
            points[i][2] = ratio;
            break;
        }
    }
}



/**
 * Initilize Highscore
 *
 * Needs to be called at the start of the program
 * to empty the array of unwanted values.
 * 
 * @author Fridh, William
*/
void initHighscore(void) {
    for (int i = 0; i < HIGHSCORE_AMOUNT; i++) {
        initials[i][0] = '-';
        initials[i][1] = '-';
        initials[i][2] = '-';
        initials[i][3] = '\0';
        points[i][0] = 0;
        points[i][1] = 0;
        points[i][2] = 0;
    }
}



/**
 * Get Highscore Initials
 * 
 * @param {int}         - index in highscorelist
 * 
 * @return {char*}      - array of three initials
 * 
 * @author Fridh, William
*/
char* getHighscoreInitials(int i) {
    return initials[i];
}



/**
 * Get Highscore Points
 * 
 * @param {int}         - index in highscorelist
 * 
 * @return {0}          - array of scores
 * 
 * @author Fridh, William
*/
int* getHighscorePoints(int i) {
    return points[i];
}



/**
 * Main
 *
 * Used for debugging.
 * 
 * @author Fridh, William
*/

/*int main(void) {
    initHighscore();
    /*
    for (int i = 0; i < HIGHSCORE_AMOUNT; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", initials[i][j]);
        }
        printf("|%d ", points[i][0]);
        printf("|%d ", points[i][1]);
        printf("|%d ", points[i][2]);
        printf("\n");
    }
    printf("%s\n", getHighscoreInitials(0));
    printf("%d\n", getHighscorePoints(0)[2]);
    */
   /*printf("%c\n", (char)getInputChar(0));
    return 0;
}*/


