/**
 * @author Fridh, William
*/

#ifndef HIGHSCORE
#define HIGHSCORE

void initHighscore(void);

char* getHighscoreInitials(int i);

int* getHighscorePoints(int i);

char getInputData(void);

char inputData[5];

void addHighscore(
    char letter_one,
    char letter_two,
    char letter_three,
    int player_one,
    int player_two
);

#endif

