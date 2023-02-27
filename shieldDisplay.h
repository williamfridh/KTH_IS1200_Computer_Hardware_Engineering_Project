#include <pic32mx.h>

void delay(int cyc) ;

uint8_t sendToBuf(uint8_t data);

void initDisplay();

void initPins();

void sendDisplayData(const uint8_t *data);

void initShield();

