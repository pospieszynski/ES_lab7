#include "AT91SAM9263.h"
#define CLOCK_DIVISOR 54
#define CHARACTERS_OFFSET 32

int initializeDGBU();

void initInterrupts();
void DBGUDisableInterrupts();
void DBGUEnableInterrupts();


void configurePIO();
void resetTransmitter();
void resetReceiver();
void turnTransmitterOn();
void turnReceiverOn();
void configureBaudRate();
void configureMode();
void configurePIO();
void turnReceiverOff();
void turnTransmitterOff();

void printAlphabet();
int printString(char *string);
void reverseLetterCase();
char readCharacter(char* character_pointer);
int checkIfReceiverReady();
int checkIfTransmitterReady();
void sendCharacter(char);