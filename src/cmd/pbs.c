/*
	Author: Bryan Martin and Joseph Listro
	Class:  CSI 385 <Section 02>
	Assignment: Semester Project
	Date Assigned: 6 September 2016
	Due Date: 6 December 2016
	
	Description:  Prints the boot sector of the file.
	
	Certification of Authenticity:
	I certify that this assignment is entirely my own work.
*/

/*
	TODO: Add access to shared memory.
*/

#include <stdio.h>
#include <stdlib.h>

#include "../helper/fatSupport.h"
#include "../helper/fat.h"
#include "../helper/workingDirectory.h"

FILE* FILE_SYSTEM_ID;

int pbs_help();

int main(int argc, char *argv[]) {
	printf("pbs has been called.\n");
	unsigned char* bootIndex;

	int mostSignificantBits;
	int leastSignificantBits;
	int bytesPerSector;
	int sectorsPerCluster;
	int numReservedSectors;
	int numFATS;
	int numRootEntries;
	int totalSectorCount;
	int sectorsPerFAT;
	int sectorsPerTrack;
	int numHeads;
	int bootSignature;
	int volumeID;
	unsigned char volumeLabel[12], fileSystemType[9];
	
	bytesPerSector = 62; // Set to default. Then reset it to the value in the boot sector

	bootIndex = (unsigned char*) malloc(bytesPerSector * sizeof(unsigned char));
	
	if (read_sector(0, bootIndex) == -1)
		printf("Error: Boot Sector could not be read.\n");
	
	// Little endian
	//Read Bytes per Sector
	mostSignificantBits  = ( ( (int) bootIndex[12] ) << 8 ) & 0x0000ff00;
	leastSignificantBits =   ( (int) bootIndex[11] )        & 0x000000ff;
	bytesPerSector = mostSignificantBits | leastSignificantBits;
	
	// Read Sectors per Cluster
	sectorsPerCluster = (unsigned int) bootIndex[13];
	
	// Read Number of reserved sectors
	mostSignificantBits  = ( ( (int) bootIndex[15] ) << 8 ) & 0x0000ff00;
	leastSignificantBits =   ( (int) bootIndex[14] )        & 0x000000ff;
	numReservedSectors = mostSignificantBits | leastSignificantBits;
	
	// Read number of FATs
	numFATs = (unsigned int) bootIndex[16];
	
	// Read number of Root Entries
	mostSignificantBits  = ( ( (int) bootIndex[18] ) << 8 ) & 0x0000ff00;
	leastSignificantBits =   ( (int) bootIndex[17] )        & 0x000000ff;
	numRootEntries = mostSignificantBits | leastSignificantBits;
	
	// Read Total Sector Count
	mostSignificantBits  = ( ( (int) bootIndex[20] ) << 8 ) & 0x0000ff00;
	leastSignificantBits =   ( (int) bootIndex[19] )        & 0x000000ff;
	totalSectorCount = mostSignificantBits | leastSignificantBits;
	
	// Read Sectors per FAT
	mostSignificantBits  = ( ( (int) bootIndex[23] ) << 8 ) & 0x0000ff00;
	leastSignificantBits =   ( (int) bootIndex[22] )        & 0x000000ff;
	sectorsPerFAT = mostSignificantBits | leastSignificantBits;
	
	// Read Sectors per Track
	mostSignificantBits  = ( ( (int) bootIndex[25] ) << 8 ) & 0x0000ff00;
	leastSignificantBits =   ( (int) bootIndex[24] )        & 0x000000ff;
	sectorsPerTrack = mostSignificantBits | leastSignificantBits;
	
	// Read Number of Heads
	mostSignificantBits  = ( ( (int) bootIndex[27] ) << 8 ) & 0x0000ff00;
	leastSignificantBits =   ( (int) bootIndex[26] )        & 0x000000ff;
	numHeads = mostSignificantBits | leastSignificantBits;
	
	// Read Boot Signature
	bootSignature = (int)bootIndex[38];
	
	int one, two, three, four;
	// Read Volume Label
	one =   ( ( (int) bootIndex[42] ) << 24 ) & 0xff000000;
	two =   ( ( (int) bootIndex[41] ) << 16 ) & 0x00ff0000;
	three = ( ( (int) bootIndex[40] ) << 8  ) & 0x0000ff00;
	four =  (   (int) bootIndex[39] )         & 0x000000ff;
	volumeID = one | two | three | four;

	// Set Volume Label
	int i;
	for(i = 0; i < 11 && bootIndex[43+i] != '\0'; i++){
		volumeLabel[i] = bootIndex[43+i];
	}

	volumeLabel[i] = '\0';

	for(i = 0; i < 8 && bootIndex[43+i]; i++){
		fileSystemType[i] = bootIndex[54+i];
	}
	fileSystemType[i] = '\0';


	printf("Bytes per sector = %d\n"
            "Sectors per cluster = %d\n"
            "Number of FATs = %d\n"
            "Number of reserved sectors = %d\n"
            "Number of root entries = %d\n"
            "Total sector count = %d\n"
            "Sectors per FAT = %d\n"
            "Sectors per track = %d\n"
            "Number of heads = %d\n"
            "Boot signature (in hex) = 0x%x\n"
            "Volume ID (in hex) = 0x%8x\n"
            "Volume label = %s\n"
            "File system type = %s\n",
            bytesPerSector,
            sectorsPerCluster,
            numFATs,
            numReservedSectors,
            numRootEntries,
            totalSectorCount,
            sectorsPerFAT,
            sectorsPerTrack,
            numHeads,
            bootSignature,
            volumeID,
            volumeLabel,
            fileSystemType);
}

int pbs_help() {
	printf("Help for pbs command will go here.\n");
	return(0);
}