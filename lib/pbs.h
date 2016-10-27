#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* Create new structure bootSector to hold data */
typedef struct bootSector {
	int bytesPerSector;
	int sectorsPerCluster;
	int numFATs;
	int numReservedSectors;
	int numRootEntries;
	int totalSectorCount;
	int sectorsPerFAT;
	int sectorsPerTrack;
	int numHeads;
	int bootSignature;
	int volumeID;
	char volumeLabel[12];
	char fileSystemType[9];
} bootSector;

#ifndef PBS_H
#define PBS_H

bootSector bootSectorData = {0,0,0,0,0,0,0,0,0,0,0,'\0','\0','\0'};
extern int BYTES_PER_SECTOR;

int pbs(); /* Reads the boot sector information for file, arg1, and prints the results */
int readBootSector(); /* Read the data in the boot sector to the bootSectorData struct */
int printBootSector(); /* Print the data in boostSectorData struct */
int pbs_help(); /* Print help for Print Boot Sector */

#endif
