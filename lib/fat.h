#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* Function Prototypes Here */

#ifndef ROOT_H
#define ROOT_H

extern char* WORKING_DIRECTORY;
extern int BYTES_PER_SECTOR;

unsigned char* readRootSectors();
void enterDir(char *dirName);
void exitDir();
void pwd();
int existingDirectory(string* directoryName);

#endif
