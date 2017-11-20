#include "AT91SAM9263.h"
#include "DBGU.h"

int initializeDGBU() {
	initInterrupts();
	
	resetTransmitter();
	turnTransmitterOff();
	resetReceiver();
	turnReceiverOff();
	configureBaudRate();
	configureMode();
	configurePIO();
	
	// TURN OFF ??
	turnReceiverOn();
	turnTransmitterOn();
	return 0;
}

void DGBUInterruptHandler() {
  int interruptStatus;
  interruptStatus = AT91C_BASE_DBGU->DBGU_CSR;
  if(interruptStatus & AT91C_BASE_DBGU->DBGU_IMR) { // interrupt from DBGU device
    if(interruptStatus & AT91C_US_TXRDY) { // transmitter interrupt
      
    } else if(interruptStatus & AT91C_US_RXRDY) { // receiver interrupt
      
    }
}

void spuriousInterruptHandler() {
  
}

void initInterrupts() {
	DBGUDisableInterrupts();
  
	AT91C_BASE_AIC->AIC_IDCR = 1 << AT91C_ID_SYS; // DISABLE SYSTEM INTERRUPT IN AIC
	
	
	AT91C_BASE_AIC->AIC_SVR[AT91C_ID_SYS]  = (unsigned int) DGBUInterruptHandler;  // STORE ADDRESS OF CORRESPONDING INTERRUPT HANDLER
	
	
	// CONFIGURE MODE
	AT91C_BASE_AIC->AIC_SMR[AT91C_ID_SYS]  = AT91C_AIC_SRCTYPE_INT_EDGE_TRIGGERED;	//INTERRUPT DETECT ON EDGE
	AT91C_BASE_AIC->AIC_SMR[AT91C_ID_SYS]  |=  AT91C_AIC_PRIOR_HIGHEST;	// HIGH PRIORITY
	
	
	AT91C_BASE_AIC->AIC_ICCR = 1 << AT91C_ID_SYS;  //INTERRUPT CLEAR COMMAND


	AT91C_BASE_AIC->AIC_IECR = 1 << AT91C_ID_SYS;
	
	DBGUEnableInterrupts();

}

void DBGUDisableInterrupts() {
  	AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_RXRDY;
	AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_TXRDY;
	AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_ENDRX;
	AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_ENDTX;
	AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_OVRE;
	AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_FRAME;
	AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_PARE;
	AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_TXEMPTY;
	AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_TXBUFE;
	AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_RXBUFF;
	AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_COMM_TX;
	AT91C_BASE_DBGU->DBGU_IDR=AT91C_US_COMM_RX;
}

void DBGUEnableInterrupts() {
  	AT91C_BASE_DBGU->DBGU_IER |= AT91C_US_RXRDY;
	
	AT91C_BASE_DBGU->DBGU_IER |= AT91C_US_TXRDY;
	
	AT91C_BASE_DBGU->DBGU_IER |= AT91C_US_ENDRX;
	
	AT91C_BASE_DBGU->DBGU_IER |= AT91C_US_ENDTX;
	
	AT91C_BASE_DBGU->DBGU_IER |= AT91C_US_OVRE;
	
	AT91C_BASE_DBGU->DBGU_IER |= AT91C_US_FRAME;
	
	AT91C_BASE_DBGU->DBGU_IER |= AT91C_US_PARE;
	
	AT91C_BASE_DBGU->DBGU_IER |= AT91C_US_TXEMPTY;
	
	AT91C_BASE_DBGU->DBGU_IER |= AT91C_US_TXBUFE;
	
	AT91C_BASE_DBGU->DBGU_IER |= AT91C_US_RXBUFF;
	
	AT91C_BASE_DBGU->DBGU_IER |= AT91C_US_COMM_TX;
	
	AT91C_BASE_DBGU->DBGU_IER |= AT91C_US_COMM_RX;
}

void resetTransmitter() {
	AT91C_BASE_DBGU->DBGU_CR=AT91C_US_RSTTX;
}

void resetReceiver() {
	AT91C_BASE_DBGU->DBGU_CR=AT91C_US_RSTRX;
}

void turnReceiverOff() {
  AT91C_BASE_DBGU->DBGU_CR = AT91C_US_RXDIS;
}

void turnTransmitterOff() {
 AT91C_BASE_DBGU->DBGU_CR = AT91C_US_TXDIS; 
}

void turnTransmitterOn() {
	AT91C_BASE_DBGU->DBGU_CR = AT91C_US_TXEN;
}

int checkIfReceiverReady() {
  return (AT91C_BASE_DBGU->DBGU_CSR & AT91C_US_RXRDY); 
}

int checkIfTransmitterReady() {
  return (AT91C_BASE_DBGU->DBGU_CSR & AT91C_US_TXRDY);
}

void turnReceiverOn() {
	AT91C_BASE_DBGU->DBGU_CR = AT91C_US_RXEN; 
}

void configureBaudRate() {
	AT91C_BASE_DBGU->DBGU_BRGR = CLOCK_DIVISOR;
}

void configureMode() {
	AT91C_BASE_DBGU->DBGU_MR = AT91C_US_CHMODE_NORMAL;
	AT91C_BASE_DBGU->DBGU_MR = AT91C_US_PAR_NONE;
}

void printAlphabet() {
 // capital letters
 int letter = 'A';
 while( letter <= 'Z' ) {
   sendCharacter((char)letter);
   letter++;
 }
 
 // small letters
 letter = 'a';
 while( letter <= 'z' ) {
   sendCharacter((char)letter);
   letter++;
 }
}

int printString(char *string) {
  int count_letters = 0;

  while(*string != '\0') {
    sendCharacter(*string);
    count_letters++;
    string++;
  }
  return count_letters;
}

char readCharacter(char* character_pointer) {
 while(!checkIfReceiverReady());
 *character_pointer = AT91C_BASE_DBGU->DBGU_RHR;
 return *character_pointer;
}

void reverseLetterCase() {
 char letter;
 readCharacter(&letter);
 
 if(letter >= 'a' && letter <= 'z') {
  letter -= CHARACTERS_OFFSET;
 } else if(letter >= 'A' && letter <= 'Z') {
  letter += CHARACTERS_OFFSET; 
 }
 sendCharacter(letter);
}

void sendCharacter(char letter) {
  while(!checkIfTransmitterReady());
  AT91C_BASE_DBGU->DBGU_THR = (unsigned int)letter;
}

void configurePIO() {
  AT91C_BASE_PIOC->PIO_PDR = AT91C_PC30_DRXD;
  AT91C_BASE_PIOC->PIO_PDR = AT91C_PC31_DTXD;
  
  AT91C_BASE_PIOC->PIO_ASR = AT91C_PC30_DRXD;
  AT91C_BASE_PIOC->PIO_ASR = AT91C_PC31_DTXD;
}

