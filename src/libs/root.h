char WORKING_DIRECTORY[200] = "/\0";


/* Function Prototypes Here */
unsigned char* readRootSectors();
void enterDir(char* dirName);
void exitDir();
void pwd();


#include "root.c"
