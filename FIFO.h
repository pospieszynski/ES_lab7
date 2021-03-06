#define BUFFER_SIZE 3
#define SUCCESS 1
#define FAILURE -1

struct FIFO {
 char buffer[BUFFER_SIZE+1];
 unsigned int head; 
 unsigned int tail;
}Fifo;

int initFIFO ();
int pushToFIFO (char data);
int popFromFIFO (char *data);
