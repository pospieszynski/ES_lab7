#include "FIFO.h"
#include "DBGU.h"

void dbgu_print_ascii(const char *buffer) {}

int main() {
  char letter; 
  
  initializeDGBU();
  initFIFO();
  
  while(1);
}
