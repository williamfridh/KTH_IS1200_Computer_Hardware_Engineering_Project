/**
 * @author Åhlins, Pontus
*/

#ifndef SHIELD_DISPLAY
#define SHIELD_DISPLAY

#include <pic32mx.h>

uint8_t sendToBuf(uint8_t data);

void initDisplay();

void initPins();

void sendDisplayData(const uint8_t *data);

void initShield();

#endif

