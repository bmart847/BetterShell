#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#ifndef PFE_H
#define PFE_H

extern int BYTES_PER_SECTOR;

int checkRange(int x, int y); /* Verifies that the provided integers are acceptable. */
unsigned char* readFAT12Table(int fatTable); /* Reads FAT12 Table and returns either Table 1 or Table 2 */
int pfe(int arg1, int arg2); /* Prints FAT12 Table Entries from (arg1+1) to arg2 */
int pfe_help(); /* Handles Printing Help for pfe */

#endif