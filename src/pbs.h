#define BYTES_TO_READ_IN_BOOT_SECTOR 62

/* Forward declare a type "bootSector" to be a struct. */
typedef struct bootSector boostSector;
/* Declare the struct with integer members x, y */
struct bootSector {
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
	char* volumeLabel;
	char* fileSystemType;
	char* filename;
};

bootSector bootSectorData;

int pbs(char* arg1); /* Reads the boot sector information for file, arg1, and prints the results */
int readBootSector(); /* Read the data in the boot sector to the bootSectorData struct */
int printBootSector(); /* Print the data in boostSectorData struct */
int pbs_help(); /* Print help for Print Boot Sector */

FILE* FILE_SYSTEM_ID;

#include "pbs.c"