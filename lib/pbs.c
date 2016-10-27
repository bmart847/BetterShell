#include "pbs.h"

/* PBS Command Functions */

/* Prints the FAT12 Boot Sector Information from file, arg1 */
int pbs() {
	printf("pbs() called.\n");
	if(readBootSector() == 0) {
		printBootSector();
	} else {
		printf("Error: Unable to read boot sector.\n");
	}
}

/* Read the data in the boot sector to the bootSectorData struct */
int readBootSector() {
	printf("readBootSector() called.\n");
	unsigned char* bootIndex;
	unsigned int volumeID;
	
	int mostSignificantBits, leastSignificantBits;
	int one,two,three,four;
	
	bootSectorData.bytesPerSector = BYTES_PER_SECTOR; // Set to default
	
	// Then reset it to the value in the boot sector

	bootIndex = (unsigned char*) malloc(bootSectorData.bytesPerSector * sizeof(unsigned char));
	
	if (read_sector(0, bootIndex) == -1)
		printf("Error: Boot Sector could not be read.\n");
	
	// Little endian
	//Read Bytes per Sector
	mostSignificantBits  = ( ( (int) bootIndex[12] ) << 8 ) & 0x0000ff00;
	leastSignificantBits =   ( (int) bootIndex[11] )        & 0x000000ff;
	bootSectorData.bytesPerSector = mostSignificantBits | leastSignificantBits;
	
	// Read Sectors per Cluster
	bootSectorData.sectorsPerCluster = (unsigned int) bootIndex[13];
	
	// Read Number of reserved sectors
	mostSignificantBits  = ( ( (int) bootIndex[15] ) << 8 ) & 0x0000ff00;
	leastSignificantBits =   ( (int) bootIndex[14] )        & 0x000000ff;
	bootSectorData.numReservedSectors = mostSignificantBits | leastSignificantBits;
	
	// Read number of FATs
	bootSectorData.numFATs = (unsigned int) bootIndex[16];
	
	// Read number of Root Entries
	mostSignificantBits  = ( ( (int) bootIndex[18] ) << 8 ) & 0x0000ff00;
	leastSignificantBits =   ( (int) bootIndex[17] )        & 0x000000ff;
	bootSectorData.numRootEntries = mostSignificantBits | leastSignificantBits;
	
	// Read Total Sector Count
	mostSignificantBits  = ( ( (int) bootIndex[20] ) << 8 ) & 0x0000ff00;
	leastSignificantBits =   ( (int) bootIndex[19] )        & 0x000000ff;
	bootSectorData.totalSectorCount = mostSignificantBits | leastSignificantBits;
	
	// Read Sectors per FAT
	mostSignificantBits  = ( ( (int) bootIndex[23] ) << 8 ) & 0x0000ff00;
	leastSignificantBits =   ( (int) bootIndex[22] )        & 0x000000ff;
	bootSectorData.sectorsPerFAT = mostSignificantBits | leastSignificantBits;
	
	// Read Sectors per Track
	mostSignificantBits  = ( ( (int) bootIndex[25] ) << 8 ) & 0x0000ff00;
	leastSignificantBits =   ( (int) bootIndex[24] )        & 0x000000ff;
	bootSectorData.sectorsPerTrack = mostSignificantBits | leastSignificantBits;
	
	// Read Number of Heads
	mostSignificantBits  = ( ( (int) bootIndex[27] ) << 8 ) & 0x0000ff00;
	leastSignificantBits =   ( (int) bootIndex[26] )        & 0x000000ff;
	bootSectorData.numHeads = mostSignificantBits | leastSignificantBits;
	
	// Read Boot Signature
	bootSectorData.bootSignature = (int)bootIndex[38];
	
	// Read Volume Label
	one =   ( ( (int) bootIndex[42] ) << 24 ) & 0xff000000;
	two =   ( ( (int) bootIndex[41] ) << 16 ) & 0x00ff0000;
	three = ( ( (int) bootIndex[40] ) << 8  ) & 0x0000ff00;
	four =  (   (int) bootIndex[39] )         & 0x000000ff;
	volumeID = one | two | three | four;

	// Set Volume Label
	int i;
	for(i = 0; i < 11 && bootIndex[43+i] != '\0'; i++){
		bootSectorData.volumeLabel[i] = bootIndex[43+i];
	}

	bootSectorData.volumeLabel[i] = '\0';

	for(i = 0; i < 8 && bootIndex[43+i]; i++){
		bootSectorData.fileSystemType[i] = bootIndex[54+i];
	}
	bootSectorData.fileSystemType[i] = '\0';
		
	return(0);
}

/* Print the data in bootSectorData struct */
int printBootSector() {
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
            bootSectorData.bytesPerSector,
            bootSectorData.sectorsPerCluster,
            bootSectorData.numFATs,
            bootSectorData.numReservedSectors,
            bootSectorData.numRootEntries,
            bootSectorData.totalSectorCount,
            bootSectorData.sectorsPerFAT,
            bootSectorData.sectorsPerTrack,
            bootSectorData.numHeads,
            bootSectorData.bootSignature,
            bootSectorData.volumeID,
            bootSectorData.volumeLabel,
            bootSectorData.fileSystemType);
}

/* Print help for Print Boot Sector */
int pbs_help() {
	printf("Help for the PBS command will go here.\n");
	return(0);
}
