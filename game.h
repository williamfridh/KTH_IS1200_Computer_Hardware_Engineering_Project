/**
 * @author Åhlins, Pontus
*/

#ifndef GAME
#define GAME

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

