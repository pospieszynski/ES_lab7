void dbgu_print_ascii(const char *buffer) {}

#include "FIFO.h"
#include "DBGU.h"
#define DBGU_INIT_SUCCESS 0
#define SUCCESS 1
#define FAILURE -1
#define TASK FIFO

int populateFifo(struct FIFO* fifo);
void readFromFifo(struct FIFO* fifo);

int main() {
  if( initializeDGBU() == DBGU_INIT_SUCCESS ) {
    
#if TASK == 1
      printAlphabet();
#endif
      
#if TASK == 2
      printString("\n\rHello world!\r\n");
#endif
      
#if TASK == 3
      while(1)
	reverseLetterCase();
#endif
	
#if TASK == FIFO
      struct FIFO fifo;
      
      if( initFIFO(&fifo) == SUCCESS ) {
	while(1) {
	  populateFifo(&fifo);
	  readFromFifo(&fifo);
	}
      }
#endif 
  }
  while(1);
}

int populateFifo(struct FIFO* fifo) {
  char character;
  
  while(1) {
    readCharacter(&character);
    if( character != '\r') {
      if(pushToFIFO(fifo, character) == FAILURE) {
      	printString("\n\rBuffer overflow error.\r\n");
      	return FAILURE;
      }
    } else {
      return SUCCESS; 
    }
  }
}

void readFromFifo(struct FIFO* fifo) {
  char letter;
  
  while(popFromFIFO(fifo, &letter) == SUCCESS) {
    if(letter >= 'a' && letter <= 'z') {
      letter -= CHARACTERS_OFFSET;
    } else if(letter >= 'A' && letter <= 'Z') {
      letter += CHARACTERS_OFFSET; 
    }
    sendCharacter(letter);
  }
  
  sendCharacter('\n');
  sendCharacter('\r');
}