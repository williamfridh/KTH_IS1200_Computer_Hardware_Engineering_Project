/**
 * @author Åhlins, Pontus
*/

#ifndef GAME
#define GAME

bool pvpMode;

int difficulty;

void pvpModeOnOff(bool trueOrFalse);

int getWinner(void);

void playAi(int difficulty);

void renderGame();

void gameButtonTriggered(int buttonData);

void paintArena();

void resetArena();

void initArena();

int getDifficultySetting(void);

void toggleDifficultySetting();

int getPlayerOneScore(void);

int getPlayerTwoScore(void);

#endif

