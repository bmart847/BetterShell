#define BYTES_TO_READ_IN_BOOT_SECTOR 62

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
	char volumeLabel[11];
	char fileSystemType[8];
}bootSector;

bootSector bootSectorData = {0,0,0,0,0,0,0,0,0,0,0,'\0','\0','\0'};

int pbs(); /* Reads the boot sector information for file, arg1, and prints the results */
int readBootSector(); /* Read the data in the boot sector to the bootSectorData struct */
int printBootSector(); /* Print the data in boostSectorData struct */
int pbs_help(); /* Print help for Print Boot Sector */

#include "pbs.c"