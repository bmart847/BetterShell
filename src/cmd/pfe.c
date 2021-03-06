/*
	Author: Bryan Martin and Joseph Listro
	Class:  CSI 385 <Section 02>
	Assignment: Semester Project
	Date Assigned: 6 September 2016
	Due Date: 6 December 2016
	
	Description:  Prints the fat entries of the file in the specified range.
	
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
#include "../helper/shared.h"

FILE* FILE_SYSTEM_ID;
extern const key_t SHM_KEY;

int checkRange(int x, int y);
unsigned char* readFAT12Table(int fatTable);
int pfe_help();

int main(int argc, char *argv[])
{
	shm_id = shmget(SHM_KEY, 250 * sizeof(char*), 0666);
	sharedMemory* share = shmat(shm_id, 0, 0);

	char* filename = filenameGet();
	FILE_SYSTEM_ID = fopen(filename, "r+");
	
	if(argc == 1 || argc > 4)
	{
		pfe_help();
		exit(1);
	}

	int start = atoi(argv[1]);
	int end = atoi(argv[2]);

	unsigned char *fat1, *fat2;
	int i;

	fat1 = readFAT12Table(1);
	fat2 = readFAT12Table(2);

	/* Conditions */
	 	if(checkRange(start, end) == 1)
		{ 
			/* Utilize checkRange function to verify arguments */
			printf("Invalid parameter values.\n");
		}
		else
		{
			/* If it checks out... */
        	for(i=(start+1); i <= end; i++)
			{
               	printf("Fat Entry %i: %x\n", i, get_fat_entry(i, fat1));
        	}	
	}

	
	shmdt(share);
	free(fat1);
	free(fat2);
	return(0);
}

/* Verifies that the provided integers are acceptable */
int checkRange(int x, int y)
{	
	/* Conditions */
	if(x>y)
	{	
		/* Starting Entry MUST be less than Ending Entry */
		printf("Error: x > y\n");
		return 1;
	}
	else if(x<2)
	{
		/* Starting entry must be at least 2 */
		printf("Error: x < 2\n");
		return 1;
	}
	else
	{
		/* Parameters are OK */
		return 0;
	}

}

unsigned char* readFAT12Table(int fatTable)
{
	/* Reads FAT12 Table and returns either Table 1 or Table 2 */
	/* Declare Variables */
	unsigned char* fat;
	int i, br=0;

	/* Allocate Memory */
	fat = (unsigned char*) malloc(9 * (62 * sizeof(unsigned char*)));

	/* Conditions */
	if(fatTable == 1)
	{
		/* Return 1st FAT */
		for(i=1; i<10; i++){
			br = br + read_sector(i, &fat[(i-1) * 62]);
		}
		return fat;
	}
	else if(fatTable == 2)
	{
		/* Return 2nd FAT */
		for(i=10; i<19; i++)
		{
			br = br + read_sector(i, &fat[(i-10)*62]);
        }
		return fat;
	}
	else
	{ 
		/* Invalid input */
		free(fat);
		return NULL;
	}
}

int pfe_help()
{
	printf("Help for pfe command will go here.\n");
	return(0);
}
