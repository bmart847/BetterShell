/*
	Author: Bryan Martin and Joseph Listro
	Class:  CSI 385 <Section 02>
	Assignment: Semester Project
	Date Assigned: 6 September 2016
	Due Date: 6 December 2016
	
	Description:  A shell.
	
	Certification of Authenticity:
	I certify that this assignment is entirely my own work.
*/

#include "pfe.h"

/* PFE Command Functions */

int checkRange(int x, int y) {	/* Verifies that the provided integers are acceptable */

	/* Conditions */
	if(x>y){	/* Starting Entry MUST be less than Ending Entry */
		printf("Error: x > y\n");
		return 1;
	} else if(x<2){	/* Starting entry must be at least 2 */
		printf("Error: x < 2\n");
		return 1;
	} else { 	/* Parameters are OK */
		return 0;
	}

}

unsigned char* readFAT12Table(int fatTable) {	/* Reads FAT12 Table and returns either Table 1 or Table 2 */
	/* Declare Variables */
	unsigned char* fat;
	int i, br=0;

	/* Allocate Memory */
	fat = (unsigned char*) malloc(9 * (BYTES_PER_SECTOR * sizeof(unsigned char)));

	/* Conditions */
	if(fatTable == 1) { /* Return 1st FAT */
		for(i=1; i<10; i++){
			br = br + read_sector(i, &fat[(i-1)*BYTES_PER_SECTOR]);
		}
		return fat;
	} else if(fatTable == 2) { /* Return 2nd FAT */
		for(i=10; i<19; i++){
			br = br + read_sector(i, &fat[(i-10)*BYTES_PER_SECTOR]);
                }
		return fat;
	} else { /* Invalid input */
		free(fat);
		return NULL;
	}
}

/* Prints FAT12 Table Entries from (arg1+1) to arg2 */
int pfe(int arg1, int arg2){
	/* Declare Variables */
	unsigned char *fat1 = readFAT12Table(1), *fat2 = readFAT12Table(2);
	int i;

	/* Conditions */
	if(checkRange(arg1, arg2) == 1) { /* Utilize checkRange function to verify arguments */
		printf("Invalid parameter values.\n");
	} else { /* If it checks out... */
        	for(i=(arg1+1); i <= arg2; i++) {
                	printf("Fat Entry %i: %x\n", i, get_fat_entry(i, fat1));
        	}	
	}

	return(0);
}

int pfe_help() {
	printf("Help for pfe command will go here.\n");
	return(0);
}
